/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Instance/GfxInstance.h>

#include <vulkan/vulkan.h>

namespace Flax
{
    class GfxVkInstance : public GfxInstance
    {
    public:
        GfxVkInstance(const GfxInstanceDesc& desc);
        ~GfxVkInstance() override final;

        Ref<GfxDevice> CreateDevice(const GfxDeviceDesc& desc) override final;
        void* Instance() const override final { return static_cast<void*>(m_instance); }
        void* Adapter() const override final { return static_cast<void*>(m_physicalDevice); }
        
    private:
        VkInstance m_instance;
        VkPhysicalDevice m_physicalDevice;

#if defined(FLAX_DEBUG)
        VkDebugUtilsMessengerEXT m_debugMessenger;
#endif
    };
}