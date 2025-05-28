/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Vulkan/Object/VObject.h>

namespace Flax
{
    class VRenderPass;
    class VImageView;

    struct FramebufferProps final
    {
        VRenderPass* passRef;
        Vector<Vector<VImageView*>> imageViewsPerFB;
        Math::Vec3u fbSize;
    };

    class VFramebuffer final : public VObject
    {
    public:
        VFramebuffer(const FramebufferProps& props, VDevice* pDevice);
        ~VFramebuffer() override final;

        void Resize(const Math::Vec3u& size);

        inline VkFramebuffer GetVkFramebuffer(usize index = 0) const { return index > m_framebuffers.size() ? nullptr : m_framebuffers[index]; }
        inline const Math::Vec3u& GetSize() const { return m_props.fbSize; }
    private:
        FramebufferProps m_props;

        Vector<VkFramebuffer> m_framebuffers;
    };
}