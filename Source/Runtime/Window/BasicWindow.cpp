#include "BasicWindow.h"

#include <GLFW/glfw3native.h>

namespace Flax
{
    BasicWindow::BasicWindow() : m_handle(nullptr), m_windowSize(1600, 900), m_windowPos(0, 0),
        m_active(true), m_visible(false)
    {
        if (!glfwInit())
        {
            LoggerWorker::Get().LogError(LogType::Window, "Failed to initialize GLFW");
            return;
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        m_handle = glfwCreateWindow(m_windowSize.x, m_windowSize.y, "Flax", nullptr, nullptr);
        if (!m_handle)
        {
            LoggerWorker::Get().LogError(LogType::Window, "Failed to create GLFW window");
            glfwTerminate();
            return;
        }

        glfwHideWindow(m_handle);
    }

    BasicWindow::~BasicWindow()
    {
        if (m_handle)
        {
            glfwDestroyWindow(m_handle);
            glfwTerminate();
        }
    }

    void BasicWindow::ProcessEvents()
    {
        if (m_handle)
        {
            glfwPollEvents();
            m_active = glfwWindowShouldClose(m_handle) == GLFW_FALSE;
            m_visible = glfwGetWindowAttrib(m_handle, GLFW_VISIBLE) == GLFW_TRUE;
        }
    }

    void BasicWindow::Show()
    {
        if (m_handle)
        {
            glfwShowWindow(m_handle);
            m_visible = true;
        }
    }

    void BasicWindow::Hide()
    {
        if (m_handle)
        {
            glfwHideWindow(m_handle);
            m_visible = false;
        }
    }

    void* BasicWindow::GetNativeWindow() const
    {
        return (void*)glfwGetWin32Window(m_handle);
    }
}