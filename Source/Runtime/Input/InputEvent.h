/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Window/WindowPollEvent.h>
#include <Runtime/Input/MouseButton.h>

namespace Flax
{
    struct EventPayload
    {
        i32 keyCode;
        i8 inputChar;

        i32 mouseX, mouseY;
        MouseButton mouseButton;
        f32 scrollDelta = 0;

        i32 gamepadButton;
        i32 gamepadAxis; f32 axisValue;

        i32 windowWidth, windowHeight;
        i32 windowX, windowY;
        b8 hasFocus;
        b8 sendQuitRequest;

        const i8* droppedFilePath;

        i32 monitorID;
    };

    struct InputEvent final
    {
        InputEvent(WindowPollEvent type = WindowPollEvent::None) : eventType(type), payload({}) {}
        ~InputEvent() = default;

        EventPayload payload;
        WindowPollEvent eventType;
    };
}