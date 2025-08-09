/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>

namespace Strand
{
    enum class WindowPollEvent
    {
        None,

        KeyPressed,
        KeyReleased,
        KeyChar,

        MousePressed,
        MouseReleased,
        MouseMoved,
        MouseScrolled,
        MouseDoubleClick,

        GamepadButtonPressed,
        GamepadButtonReleased,
        GamepadAxisMoved,

        WindowResized,
        WindowMoved,
        WindowClosed,
        WindowFocused,
        WindowLostFocus,

        RawInputDeviceChanged,

        DragEnter,
        DragLeave,
        DragDrop,

        AppSetFocusAs,
        MonitorChanged,
    };
}