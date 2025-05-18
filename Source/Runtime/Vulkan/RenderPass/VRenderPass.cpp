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
            VkSubpassDescription vkSubpass{};
            vkSubpass.pipelineBindPoint = subpass.bindPoint;
            if (subpass.colorAttachmentIndices.size() > 0)
            {
                colorRefs.resize(subpass.colorAttachmentIndices.size());
                for (u32 i = 0; i < subpass.colorAttachmentIndices.size(); i++)
                {
                    colorRefs[i].attachment = subpass.colorAttachmentIndices[i];
                    colorRefs[i].layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
                }
                vkSubpass.colorAttachmentCount = static_cast<u32>(colorRefs.size());
                vkSubpass.pColorAttachments = colorRefs.data();
            }
            if (subpass.depthAttachmentIndex != u32_max)
            {
                depthRefs.resize(1);
                depthRefs[0].attachment = subpass.depthAttachmentIndex;
                depthRefs[0].layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
                vkSubpass.pDepthStencilAttachment = &depthRefs[0];
            }
            if (subpass.inputAttachmentIndices.size() > 0)
            {
                inputRefs.resize(subpass.inputAttachmentIndices.size());
                for (u32 i = 0; i < subpass.inputAttachmentIndices.size(); i++)
                {
                    inputRefs[i].attachment = subpass.inputAttachmentIndices[i];
                    inputRefs[i].layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
                }
                vkSubpass.inputAttachmentCount = static_cast<u32>(inputRefs.size());
                vkSubpass.pInputAttachments = inputRefs.data();
            }
            vkSubpasses.push_back(vkSubpass);
        }

        VkSubpassDependency dependency{};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;
        dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.dstStageMask = dependency.srcStageMask;
        dependency.srcAccessMask = 0;
        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        dependency.dependencyFlags = 0;

        VkRenderPassCreateInfo info{ VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO };
        info.attachmentCount = static_cast<u32>(attachmentDescs.size());
        info.pAttachments = attachmentDescs.data();
        info.subpassCount = static_cast<u32>(vkSubpasses.size());
        info.pSubpasses = vkSubpasses.data();
        info.dependencyCount = 1;
        info.pDependencies = &dependency;

        VDebug::VkAssert(vkCreateRenderPass(GetRoot()->GetVkDevice(), &info, nullptr, &m_renderPass), "VRenderPass");
    }

    VRenderPass::~VRenderPass()
    {
        if (m_renderPass)
        {
            vkDestroyRenderPass(GetRoot()->GetVkDevice(), m_renderPass, nullptr);
            m_renderPass = VK_NULL_HANDLE;
        }
    }
}