#include "VFramebuffer.h"

#include <Runtime/Vulkan/Device/VDevice.h>
#include <Runtime/Vulkan/Debug/VDebug.h>
#include <Runtime/Vulkan/RenderPass/VRenderPass.h>
#include <Runtime/Vulkan/Image/VImageView.h>

namespace Flax
{
    VFramebuffer::VFramebuffer(const FramebufferProps& desc, VDevice* pDevice) : VObject(pDevice), m_props(desc)
    {
        Resize(desc.fbSize);
    }

    VFramebuffer::~VFramebuffer()
    {
        for (auto& fb : m_framebuffers)
            vkDestroyFramebuffer(GetRoot()->GetVkDevice(), fb, nullptr);

        m_framebuffers.clear();
    }

    void VFramebuffer::Resize(const Math::Vec3u& size)
    {
        for (auto& fb : m_framebuffers)
            vkDestroyFramebuffer(GetRoot()->GetVkDevice(), fb, nullptr);
        m_framebuffers.clear();

        m_framebuffers.resize(m_props.imageViewsPerFB.size());
        for (usize i = 0; i < m_props.imageViewsPerFB.size(); ++i)
        {
            Vector<VkImageView> attachments;

            for (usize imgIndex = 0; imgIndex < m_props.imageViewsPerFB[i].size(); imgIndex++)
                attachments.push_back(m_props.imageViewsPerFB[i][imgIndex]->GetVkView());

            VkFramebufferCreateInfo fbInfo{ VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO };
            fbInfo.renderPass = m_props.passRef->GetVkRenderPass();
            fbInfo.attachmentCount = static_cast<u32>(attachments.size());
            fbInfo.pAttachments = attachments.data();
            fbInfo.width = size.x;
            fbInfo.height = size.y;
            fbInfo.layers = size.z;

            VDebug::VkAssert(vkCreateFramebuffer(GetRoot()->GetVkDevice(), &fbInfo, nullptr, &m_framebuffers[i]), "VFramebuffer");
        }
    }
}