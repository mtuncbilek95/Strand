/*
 * Licensed under the terms specified in the LICENSE.md file 
 * located in the root directory of this source tree.
 *
 * Copyright (c) 2024 Metehan Tuncbilek
 */
#pragma once

#include <Runtime/Core/CoreMinimal.h>
#include <Runtime/Input/InputEvent.h>

namespace Strand
{
    class InputEventQueue final
    {
    public:
        void PushEvent(const InputEvent& event) { m_queue.push(event); }
        b8 PopEvent(InputEvent& event)
        {
            if (!m_queue.empty())
            {
                event = m_queue.front();
                m_queue.pop();
                return true;
            }

            return false;
        }

        void Clear() { while (!m_queue.empty()) m_queue.pop(); }
        b8 IsEmpty() const { return m_queue.empty(); }

    private:
        Queue<InputEvent> m_queue;
    };
}