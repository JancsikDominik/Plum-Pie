#include <iostream>
#include <thread>

#include "AppBase.hpp"
#include "GLFWWindow.hpp"

#include "Debugging/Debug.hpp"
#include "Debugging/Console.hpp"
#include "Core/Vulkan/VKRenderer.hpp"

namespace Plum
{

    AppBase::AppBase(const std::string& appName)
        : KeyEventObserver()
        , ResizeEventObserver()
        , MouseEventObserver()
        , m_renderer{ nullptr }
    {
        InitGLFW();
        m_window = new GLFW::Window(appName);
        m_renderer = new VK::Renderer(m_window);
    }

    AppBase::~AppBase()
    {
        CleanUpGLFW();
        delete m_renderer;
        delete m_window;
    }

    void AppBase::Run()
    {
        // starting rendering thread
        std::thread renderingThread([&]() {

            StartUp();

            while (!m_window->ShouldClose())
            {
                Update(m_window->GetTime());
                // m_renderer->Render();
                //m_renderer->SwapBuffers();
            }

            Debug::Console::LogInfo("rendering stopped");
        });

        // we are seperating the rendering to a different thread, so we can keep drawing when for e.g we resize the window
        while (!m_window->ShouldClose())
        {
            m_window->PollEvents();
        }

        renderingThread.join();
    }

    void AppBase::InitGLFW() const
    {
        if (!glfwInit())
        {
            Debug::Console::LogError("failed to initialize GLFW");
            abort();
        }

        Debug::Console::LogSuccess("Initialized glfw");
    }

    void AppBase::CleanUpGLFW() const
    {
        glfwTerminate();
        glfwSetErrorCallback(nullptr);
        Debug::Console::LogSuccess("GLFW terminated");
    }
}
