#include "VInstance.h"

#include <Runtime/Vulkan/Debug/VDebug.h>

#include <Volk/volk.h>

namespace Flax
{
	static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData)
	{
        switch (messageSeverity)
        {
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
            Log::Info(LogType::GraphicsAPI, "{}", pCallbackData->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
            Log::Debug(LogType::GraphicsAPI, "{}", pCallbackData->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
            Log::Warn(LogType::GraphicsAPI, "{}", pCallbackData->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
            Log::Error(LogType::GraphicsAPI, "{}", pCallbackData->pMessage);
            break;
        default:
            break;
        }

        return false;
	}

	VInstance::VInstance(const InstanceProps& desc) : m_props(desc), m_instance(VK_NULL_HANDLE), 
        m_physicalDevice(VK_NULL_HANDLE)
	{
        VDebug::VkAssert(volkInitialize(), "VInstance");

#if defined(FLAX_DEBUG)
        m_debugMessenger = VK_NULL_HANDLE;
#endif

        struct ExtensionEntry
        {
            const char* name;
            b8 supported;
        };

        Vector<ExtensionEntry> extensions;
        Vector<const char*> workingExtensions;
        extensions.push_back({ VK_KHR_SURFACE_EXTENSION_NAME, false });
        extensions.push_back({ VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME, false });
        extensions.push_back({ VK_KHR_GET_SURFACE_CAPABILITIES_2_EXTENSION_NAME, false });

#if defined(FLAX_WINDOWS)
        extensions.push_back({ VK_KHR_WIN32_SURFACE_EXTENSION_NAME, false });
#endif

#if defined(FLAX_DEBUG)
        extensions.push_back({ VK_EXT_DEBUG_UTILS_EXTENSION_NAME, false });
        extensions.push_back({ VK_EXT_DEBUG_REPORT_EXTENSION_NAME, false });
#endif

        u32 extensionCount = 0;
        VDebug::VkAssert(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr), "VInstance");

        Vector<VkExtensionProperties> allExtensions(extensionCount);
        VDebug::VkAssert(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, allExtensions.data()), "VInstance");

        for (usize i = 0; i < extensions.size(); ++i) 
        {
            for (auto& extension : allExtensions) 
            {
                if (strcmp(extensions[i].name, extension.extensionName) == 0) 
                {
                    extensions[i].supported = true;
                    workingExtensions.push_back(extensions[i].name);
                    break;
                }
            }
        }

        // Print unsupported extensions
        for (auto& extension : extensions) 
        {
            if (!extension.supported)
                Log::Warn(LogType::Render, "Extension not supported: {}", extension.name);
        }

        u32 layerCount = 0;
        VDebug::VkAssert(vkEnumerateInstanceLayerProperties(&layerCount, nullptr), "VInstance");
        Vector<VkLayerProperties> allLayers(layerCount);
        VDebug::VkAssert(vkEnumerateInstanceLayerProperties(&layerCount, allLayers.data()), "VInstance");

        Vector<ExtensionEntry> wantedLayers;
        Vector<const char*> workingLayers;
#if defined(FLAX_DEBUG)
        wantedLayers.push_back({ "VK_LAYER_KHRONOS_validation", false });
        wantedLayers.push_back({ "VK_LAYER_LUNARG_screenshot" , false });
        wantedLayers.push_back({ "VK_LAYER_LUNARG_monitor", false });
#endif

        for (usize i = 0; i < wantedLayers.size(); ++i)
        {
            for (auto& layer : allLayers)
            {
                if (strcmp(wantedLayers[i].name, layer.layerName) == 0)
                {
                    wantedLayers[i].supported = true;
                    workingLayers.push_back(wantedLayers[i].name);
                    break;
                }
            }
        }

        // Print unsupported layers
        for (auto& layer : wantedLayers)
        {
            if (!layer.supported)
                Log::Warn(LogType::Render, "Layer not supported: {}", layer.name);
        }

        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = desc.appName.c_str();
        appInfo.applicationVersion = VK_MAKE_VERSION(desc.appVersion.x, desc.appVersion.y, desc.appVersion.z);
        appInfo.pEngineName = desc.engineName.c_str();
        appInfo.engineVersion = VK_MAKE_VERSION(desc.engineVersion.x, desc.engineVersion.y, desc.engineVersion.z);
        appInfo.apiVersion = VK_API_VERSION_1_3;

        VkInstanceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = static_cast<u32>(workingExtensions.size());
        createInfo.ppEnabledExtensionNames = workingExtensions.data();
        createInfo.enabledLayerCount = static_cast<u32>(workingLayers.size());
        createInfo.ppEnabledLayerNames = workingLayers.data();

        VDebug::VkAssert(vkCreateInstance(&createInfo, nullptr, &m_instance), "VInstance");
        
        volkLoadInstance(m_instance);

#if defined(FLAX_DEBUG)
        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};
        debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | 
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        debugCreateInfo.pfnUserCallback = DebugCallback;
        debugCreateInfo.pUserData = nullptr;

        VDebug::VkAssert(vkCreateDebugUtilsMessengerEXT(m_instance, &debugCreateInfo, nullptr, &m_debugMessenger), "VInstance");
#endif

        u32 deviceCount = 0;
        VDebug::VkAssert(vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr), "VInstance");

        // Temporary struct to hold the device and its score
        HashMap<String, Pair<VkPhysicalDevice, u32>> allDevices;

        // Get the physical devices
        Vector<VkPhysicalDevice> devices(deviceCount);
        VDebug::VkAssert(vkEnumeratePhysicalDevices(m_instance, &deviceCount, devices.data()), "VInstance");

        for (auto& device : devices)
        {
            // Get the device properties
            VkPhysicalDeviceProperties deviceProperties = {};
            vkGetPhysicalDeviceProperties(device, &deviceProperties);

            // Get the device features
            VkPhysicalDeviceFeatures deviceFeatures = {};
            vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

            // Get the device memory properties
            VkPhysicalDeviceMemoryProperties deviceMemoryProperties = {};
            vkGetPhysicalDeviceMemoryProperties(device, &deviceMemoryProperties);

            // Get the device queue family properties
            u32 queueFamilyCount = 0;
            vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

            Vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
            vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilyProperties.data());

            // Hold device on allDevices
            allDevices[deviceProperties.deviceName] = { device, 0 };

            for (auto& queueFamily : queueFamilyProperties)
                allDevices[deviceProperties.deviceName].second += queueFamily.queueCount;

            // Check if the device is discrete
            if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
                allDevices[deviceProperties.deviceName].second += 1000;
            else
                allDevices[deviceProperties.deviceName].second += 100;

            // Check if the device supports geometry shaders
            if (deviceFeatures.geometryShader)
                allDevices[deviceProperties.deviceName].second += 10;
        }

        // Get the best device
        auto bestDevice = std::max_element(allDevices.begin(), allDevices.end(),
            [](const Pair<String, Pair<VkPhysicalDevice, u32>>& a, const Pair<String, Pair<VkPhysicalDevice, u32>>& b)
            {
                return a.second.second < b.second.second;
            });

        Log::Debug(LogType::Render, "Best device found: {}", bestDevice->first.c_str());
        m_physicalDevice = bestDevice->second.first;
	}

	VInstance::~VInstance()
	{
#if defined(FLAX_DEBUG)
        if (m_debugMessenger != VK_NULL_HANDLE)
        {
            vkDestroyDebugUtilsMessengerEXT(m_instance, m_debugMessenger, nullptr);
            m_debugMessenger = VK_NULL_HANDLE;
        }
#endif

        if (m_instance)
        {
            vkDestroyInstance(m_instance, nullptr);
            m_instance = VK_NULL_HANDLE;
        }
	}
}
