#include "BasicWindow.h"

#include <GLFW/glfw3.h>
#include <glfw/glfw3native.h>

namespace Flax
{
    GLFWwindow* gWindow = nullptr;

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

        gWindow = glfwCreateWindow(m_props.windowSize.x, m_props.windowSize.y, m_props.windowName.c_str(), nullptr, nullptr);
        if (!gWindow)
        {
            Log::Critical(LogType::Window, "Failed to create GLFW window");
            glfwTerminate();
            exit(-1);
        }
        glfwSetWindowUserPointer(gWindow, this);

        m_windowHandle = (void*)glfwGetWin32Window(gWindow);
        m_windowInstance = nullptr;
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
            glfwSetWindowTitle(gWindow, title.c_str());
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
        if (gWindow)
        {
            switch (mode)
            {
            case WindowMode::Windowed:
                glfwSetWindowMonitor(gWindow, nullptr, 0, 0, m_props.windowSize.x, m_props.windowSize.y, 0);
                break;
            case WindowMode::Fullscreen:
                glfwSetWindowMonitor(gWindow, glfwGetPrimaryMonitor(), 0, 0, m_props.windowSize.x, m_props.windowSize.y, 0);
                break;
            case WindowMode::Borderless:
                glfwSetWindowMonitor(gWindow, nullptr, 0, 0, m_props.windowSize.x, m_props.windowSize.y, 0);
                break;
            }
        }

        m_props.windowMode = mode;
    }

    b8 BasicWindow::IsActive() const
    {
        return !glfwWindowShouldClose(gWindow);
    }
}