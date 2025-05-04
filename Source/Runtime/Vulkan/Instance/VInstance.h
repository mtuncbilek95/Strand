/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <vulkan/vulkan.h>

namespace Flax
{
    struct InstanceProps final
    {
        String appName;
        String engineName;
        Math::Vec3i appVersion;
        Math::Vec3i engineVersion;
    };

    class VInstance final
    {
    public:
        VInstance(const InstanceProps& desc);
        ~VInstance();

        inline VkInstance GetVkInstance() const { return m_instance; }
        inline VkPhysicalDevice GetVkAdapter() const { return m_adapter; }

        const String& GetAppName() const { return m_props.appName; }
        const String& GetEngineName() const { return m_props.engineName; }
        const Math::Vec3i& GetAppVersion() const { return m_props.appVersion; }
        const Math::Vec3i& GetEngineVersion() const { return m_props.engineVersion; }

    private:
        InstanceProps m_props;

        VkInstance m_instance;
        VkPhysicalDevice m_adapter;

#if defined(FLAX_DEBUG)
        VkDebugUtilsMessengerEXT m_debugMessenger;
#endif
    };
}