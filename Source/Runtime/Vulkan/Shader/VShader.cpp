#include "VShader.h"

#include <Runtime/Vulkan/Debug/VDebug.h>
#include <Runtime/Vulkan/Device/VDevice.h>

#include <Runtime/ShaderCompiler/ShaderCompiler.h>

namespace Flax
{
	VShader::VShader(const ShaderProps& desc, VDevice* pDevice) : VObject(pDevice), m_props(desc), m_shaderModule(VK_NULL_HANDLE)
	{
        ReadArray<u32> data = ShaderCompiler::CompileShader(desc.shaderPath, desc.includePath, desc.entryPoint);
		// Load shader code from file
		VkShaderModuleCreateInfo createInfo{ VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO };
		createInfo.codeSize = data.SizeInBytes();
		createInfo.pCode = reinterpret_cast<const u32*>(data.Data());

		VDebug::VkAssert(vkCreateShaderModule(GetRoot()->GetVkDevice(), &createInfo, nullptr, &m_shaderModule), "VShader");
	}

	VShader::~VShader()
	{
        if (m_shaderModule != VK_NULL_HANDLE)
        {
            vkDestroyShaderModule(GetRoot()->GetVkDevice(), m_shaderModule, nullptr);
            m_shaderModule = VK_NULL_HANDLE;
        }
	}
}