/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

#include <GLFW/glfw3.h>

namespace Flax
{
    class BasicWindow
    {
    public:
        BasicWindow();
        ~BasicWindow();

        void ProcessEvents();

        void Show();
        void Hide();
        
        Math::Vec2u GetSize() const { return m_windowSize; }
        Math::Vec2u GetPos() const { return m_windowPos; }

        b8 IsActive() const { return m_active; }
        b8 IsVisible() const { return m_visible; }

        void* GetNativeWindow() const;

    private:
        GLFWwindow* m_handle;

        Math::Vec2u m_windowSize;
        Math::Vec2u m_windowPos;

        b8 m_active;
        b8 m_visible;
    };
}

