#include "VRenderPass.h"

#include <Runtime/Vulkan/Device/VDevice.h>
#include <Runtime/Vulkan/Debug/VDebug.h>

namespace Flax
{
    VRenderPass::VRenderPass(const RenderPassProps& desc, VDevice* pDevice) : VObject(pDevice), m_props(desc)
    {
        Vector<VkAttachmentDescription> attachmentDescs;
        for (const auto& att : desc.attachments)
        {
            VkAttachmentDescription vkAtt{};
            vkAtt.format = att.format;
            vkAtt.samples = VK_SAMPLE_COUNT_1_BIT;
            vkAtt.loadOp = att.loadOp;
            vkAtt.storeOp = att.storeOp;
            vkAtt.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
            vkAtt.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
            vkAtt.initialLayout = att.initialLayout;
            vkAtt.finalLayout = att.finalLayout;
            attachmentDescs.push_back(vkAtt);
        }

        Vector<VkSubpassDescription> vkSubpasses;
        Vector<VkAttachmentReference> colorRefs;
        Vector<VkAttachmentReference> depthRefs;
        Vector<VkAttachmentReference> inputRefs;

        for (const auto& subpass : desc.subpasses)
        {
            VkSubpassDescription sp{};
            sp.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

            const usize colorOffset = colorRefs.size();
            for (u32 index : subpass.colorAttachmentIndices)
                colorRefs.push_back({ index, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL });
            sp.colorAttachmentCount = static_cast<u32>(subpass.colorAttachmentIndices.size());
            sp.pColorAttachments = sp.colorAttachmentCount ? &colorRefs[colorOffset] : nullptr;

            if (subpass.depthAttachmentIndex != u32_max)
            {
                depthRefs.push_back({ subpass.depthAttachmentIndex, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL });
                sp.pDepthStencilAttachment = &depthRefs.back();
            }

            const usize inputOffset = inputRefs.size();
            for (u32 index : subpass.inputAttachmentIndices)
                inputRefs.push_back({ index, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL });
            sp.inputAttachmentCount = static_cast<u32>(subpass.inputAttachmentIndices.size());
            sp.pInputAttachments = sp.inputAttachmentCount ? &inputRefs[inputOffset] : nullptr;

            vkSubpasses.push_back(sp);
        }

        VkRenderPassCreateInfo info{ VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO };
        info.attachmentCount = static_cast<u32>(attachmentDescs.size());
        info.pAttachments = attachmentDescs.data();
        info.subpassCount = static_cast<u32>(vkSubpasses.size());
        info.pSubpasses = vkSubpasses.data();

        VDebug::VkAssert(vkCreateRenderPass(m_rootDevice->GetVkDevice(), &info, nullptr, &m_renderPass), "VRenderPass");
    }

    VRenderPass::~VRenderPass()
    {
        if (m_renderPass)
        {
            vkDestroyRenderPass(m_rootDevice->GetVkDevice(), m_renderPass, nullptr);
            m_renderPass = VK_NULL_HANDLE;
        }
    }
}