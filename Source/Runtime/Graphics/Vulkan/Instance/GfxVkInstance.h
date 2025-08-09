/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Graphics/RHI/Instance/GfxInstance.h>

#include <vulkan/vulkan.h>

namespace Strand
{
    class GfxVkInstance final : public GfxInstance
    {
    public:
        GfxVkInstance(const GfxInstanceDesc& desc);
        ~GfxVkInstance() override final;

        Ref<GfxDevice> CreateDevice(const GfxDeviceDesc& desc) override final;
        void* Instance() const override final;
        void* Adapter() const override final;
        
    private:
        VkInstance m_instance;
        VkPhysicalDevice m_physicalDevice;

#if defined(STRAND_DEBUG)
        VkDebugUtilsMessengerEXT m_debugMessenger;
#endif
    };
}