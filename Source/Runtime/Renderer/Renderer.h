/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Data/Containers/Singleton.h>
#include <Runtime/Vulkan/Instance/VInstance.h>
#include <Runtime/Vulkan/Device/VDevice.h>
#include <Runtime/Vulkan/Swapchain/VSwapchain.h>

namespace Flax
{
    class Renderer : public Singleton<Renderer>
    {
    public:
        Renderer() = default;
        ~Renderer() = default;

        // Initializes necessary renderer elements
        void StartRenderer();
        // Destroys necessary renderer elements
        void StopRenderer();

        void BeginFrame();
        void SubmitFrame(f64 deltaTime);
        void EndFrame();

    private:
        Ref<VInstance> m_instance;
        Ref<VDevice> m_device;
        Ref<VSwapchain> m_swapchain;
    };
}