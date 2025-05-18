/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Data/Containers/IObject.h>

#include <vulkan/vulkan.h>

namespace Flax
{
    struct InstanceProps final
    {
        String appName;
        String engineName;
        Math::Vec3u appVersion;
        Math::Vec3u engineVersion;
    };

    class VInstance : public IObject
    {
    public:
        VInstance(const InstanceProps& desc);
        ~VInstance() override final;

        inline VkInstance GetVkInstance() const { return m_instance; }
        inline VkPhysicalDevice GetVkAdapter() const { return m_physicalDevice; }

    private:
        InstanceProps m_props;

        VkInstance m_instance;
        VkPhysicalDevice m_physicalDevice;

#if defined(FLAX_DEBUG)
        VkDebugUtilsMessengerEXT m_debugMessenger;
#endif
    };
}