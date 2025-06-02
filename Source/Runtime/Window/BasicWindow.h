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
#include <Runtime/Input/InputQueue.h>

namespace Flax
{
    enum class WindowMode
    {
        Windowed,
        Fullscreen,
        Borderless
    };

    struct WindowProps final
    {
        String windowName = "Flax";
        Math::Vec2u windowSize = { 1920, 1080 };
        WindowMode windowMode = WindowMode::Windowed;

        WindowProps& setWindowName(const String& name) { windowName = name; return *this; }
        WindowProps& setWindowSize(const Math::Vec2u& size) { windowSize = size; return *this; }
        WindowProps& setWindowMode(WindowMode mode) { windowMode = mode; return *this; }
    };

    class BasicWindow : public IObject
    {
    public:
        BasicWindow(const WindowProps& desc);
        ~BasicWindow();

        void Show();
        void Hide();
        void ProcessEvents();

        void SetTitle(const String& title);
        void SetSize(const Math::Vec2u& size);
        
        void SetWindowMode(WindowMode mode);

        const String& GetTitle() const { return m_props.windowName; }
        const Math::Vec2u& GetSize() const { return m_props.windowSize; }
        WindowMode GetWindowMode() const { return m_props.windowMode; }

        b8 IsHidden() const { return m_hidden; }
        b8 IsActive() const;

        void* GetHandle() const { return m_windowHandle; }
        void* GetInstance() const { return m_windowInstance; }

    private:
        WindowProps m_props;

        void* m_windowHandle = nullptr;
        void* m_windowInstance = nullptr;

        b8 m_hidden = true;

        InputEventQueue m_eventQueue;
    };
}
