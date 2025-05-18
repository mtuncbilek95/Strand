#include "VDescriptorLayout.h"

#include <Runtime/Vulkan/Debug/VDebug.h>
#include <Runtime/Vulkan/Device/VDevice.h>

namespace Flax
{
	VDescLayout::VDescLayout(const DescLayoutProps& desc, VDevice* pDevice) : VObject(pDevice), m_props(desc)
	{
		Vector<VkDescriptorSetLayoutBinding> bindings(desc.bindings.size());

		for (u32 i = 0; i < desc.bindings.size(); i++)
		{
			bindings[i].binding = desc.bindings[i].binding;
			bindings[i].descriptorType = desc.bindings[i].type;
			bindings[i].descriptorCount = desc.bindings[i].count;
			bindings[i].stageFlags = desc.bindings[i].stageFlags;
			bindings[i].pImmutableSamplers = nullptr;
		}

		VkDescriptorSetLayoutCreateInfo createInfo = { VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO };
		createInfo.bindingCount = static_cast<u32>(bindings.size());
		createInfo.pBindings = bindings.data();
		createInfo.flags = desc.createFlags;

		VDebug::VkAssert(vkCreateDescriptorSetLayout(GetRoot()->GetVkDevice(), &createInfo, nullptr, &m_layout), "VDescLayout");
	}

	VDescLayout::~VDescLayout()
	{
        if (m_layout != VK_NULL_HANDLE)
        {
            vkDestroyDescriptorSetLayout(GetRoot()->GetVkDevice(), m_layout, nullptr);
            m_layout = VK_NULL_HANDLE;
        }
	}

}