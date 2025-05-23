#include "InputDispatcher.h"

namespace Flax
{
    void InputDispatcher::RegisterListener(WindowPollEvent type, EventCallback callback)
    {
        m_listeners[type].push_back(callback);
    }

    void InputDispatcher::DispatchEvent(const InputEvent& event)
    {
        if (m_listeners.find(event.eventType) != m_listeners.end())
        {
            for (auto& callback : m_listeners[event.eventType])
                callback(event);
        }
    }

    namespace
    {
        struct InputDispactherRegistry
        {
            InputDispactherRegistry()
            {
                ServiceLocator::Register<InputDispatcher>(NewRef<InputDispatcher>());
            }
        };

        static InputDispactherRegistry inputRegistry;
    }
}