#include "BasicWindow.h"

#include <Runtime/Input/InputDispatcher.h>

#include <GLFW/glfw3.h>
#include <glfw/glfw3native.h>

namespace Flax
{
    GLFWwindow* gWindow = nullptr;
    static InputEvent inputEvent;

    static void MouseMoveCallback(GLFWwindow* window, f64 xpos, f64 ypos)
    {
        InputEventQueue* queue = static_cast<InputEventQueue*>(glfwGetWindowUserPointer(gWindow));

        inputEvent.eventType = WindowPollEvent::MouseMoved;
        inputEvent.payload.mouseX = (int)xpos;
        inputEvent.payload.mouseY = (int)ypos;

        queue->PushEvent(inputEvent);

        InputEvent event;
        while (queue->PopEvent(event))
            ServiceLocator::Get<InputDispatcher>()->DispatchEvent(event);
    }

    static void MouseButtonCallback(GLFWwindow* window, i32 button, i32 action, i32 mods)
    {
        InputEventQueue* queue = static_cast<InputEventQueue*>(glfwGetWindowUserPointer(gWindow));

        if (action == GLFW_PRESS)
        {
            inputEvent.eventType = WindowPollEvent::MousePressed;
            inputEvent.payload.mouseButton |= static_cast<MouseButton>(1 << button);

        }
        else if (action == GLFW_RELEASE)
        {
            inputEvent.eventType = WindowPollEvent::MouseReleased;
            inputEvent.payload.mouseButton &= ~static_cast<MouseButton>(1 << button);
        }

        queue->PushEvent(inputEvent);

        InputEvent event;
        while (queue->PopEvent(event))
            ServiceLocator::Get<InputDispatcher>()->DispatchEvent(event);
    }

    static void ResizeCallback(GLFWwindow* window, i32 width, i32 height)
    {
        InputEventQueue* queue = static_cast<InputEventQueue*>(glfwGetWindowUserPointer(gWindow));

        inputEvent.eventType = WindowPollEvent::WindowResized;
        inputEvent.payload.windowWidth = width;
        inputEvent.payload.windowHeight = height;

        queue->PushEvent(inputEvent);

        InputEvent event;
        while (queue->PopEvent(event))
            ServiceLocator::Get<InputDispatcher>()->DispatchEvent(event);
    }

    static void MouseWheelScrollCallback(GLFWwindow* window, f64 xoffset, f64 yoffset)
    {
        InputEventQueue* queue = static_cast<InputEventQueue*>(glfwGetWindowUserPointer(gWindow));

        inputEvent.eventType = WindowPollEvent::MouseScrolled;
        inputEvent.payload.scrollDelta = static_cast<float>(yoffset);

        queue->PushEvent(inputEvent);

        InputEvent event;
        while (queue->PopEvent(event))
            ServiceLocator::Get<InputDispatcher>()->DispatchEvent(event);
    }

    static void KeyboardCallback(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods)
    {

    }

    static void CharCallback(GLFWwindow* window, u32 codepoint)
    {

    }

    BasicWindow::BasicWindow(const WindowProps &desc) : m_props(desc)
    {
        if (!glfwInit())
        {
            Log::Critical(LogType::Window, "Failed to initialize GLFW");
            exit(-1);
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

        gWindow = glfwCreateWindow(m_props.windowSize.x, m_props.windowSize.y, m_props.windowName.data(), nullptr, nullptr);
        if (!gWindow)
        {
            Log::Critical(LogType::Window, "Failed to create GLFW window");
            glfwTerminate();
            exit(-1);
        }
        glfwSetWindowUserPointer(gWindow, &m_eventQueue);

        m_windowHandle = (void*)glfwGetWin32Window(gWindow);
        m_windowInstance = nullptr;

        glfwSetCursorPosCallback(gWindow, MouseMoveCallback);
        glfwSetMouseButtonCallback(gWindow, MouseButtonCallback);
        glfwSetScrollCallback(gWindow, MouseWheelScrollCallback);
        glfwSetWindowSizeCallback(gWindow, ResizeCallback);
        glfwSetKeyCallback(gWindow, KeyboardCallback);
        glfwSetCharCallback(gWindow, CharCallback);
    }

    BasicWindow::~BasicWindow()
    {
        if (gWindow)
        {
            glfwSetWindowShouldClose(gWindow, GLFW_TRUE);
            glfwDestroyWindow(gWindow);
            glfwTerminate();
            gWindow = nullptr;
        }
    }

    void BasicWindow::Show()
    {
        if (gWindow)
            glfwShowWindow(gWindow);

        m_hidden = false;
    }

    void BasicWindow::Hide()
    {
        if (gWindow)
            glfwHideWindow(gWindow);

        m_hidden = true;
    }

    void BasicWindow::ProcessEvents()
    {
        glfwPollEvents();
    }

    void BasicWindow::SetTitle(const String &title)
    {
        if (gWindow)
            glfwSetWindowTitle(gWindow, title.data());
        m_props.windowName = title;
    }

    void BasicWindow::SetSize(const Math::Vec2u &size)
    {
        if (gWindow)
            glfwSetWindowSize(gWindow, size.x, size.y);

        m_props.windowSize = size;
    }

    void BasicWindow::SetWindowMode(WindowMode mode)
    {
    }

    b8 BasicWindow::IsActive() const
    {
        return !glfwWindowShouldClose(gWindow);
    }
}