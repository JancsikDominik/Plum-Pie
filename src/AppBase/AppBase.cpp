#include <iostream>
#include <thread>

#include "AppBase.hpp"
#include "Debugging/Debug.hpp"
#include "Debugging/Console.hpp"
#include "GLFWWrappers/Window.hpp"
#include "Core/Vulkan/VKRenderer.hpp"

namespace Plum
{

    AppBase::AppBase(const std::string& appName)
        : KeyEventObserver()
        , ResizeEventObserver()
        , MouseEventObserver()
        , m_renderer{ nullptr }
    {
        try
        {
            m_window = new GLFW::Window(appName);
            m_renderer = new VK::Renderer(m_window);
        }
        catch (...)
        {
            glfwTerminate();
            return;
        }
    }

    AppBase::~AppBase()
    {
        // TODO: uncomment when got vulkan renderer
        delete m_renderer;
        delete m_window;
        glfwTerminate();
        glfwSetErrorCallback(nullptr);
    }

    void AppBase::Run()
    {
        // SetCurrentContext is called in the constructor of the GLFW window, but 
        // when moving a context between threads, we must make it non-current on the old thread before making it current on the new one.
        // so by setting SetCurrentContext to false on this thread, we can set the context to true on the other thread
        m_window->SetCurrentContext(false);

        // starting rendering thread
        std::thread renderingThread([&]() {

            m_window->SetCurrentContext(true);

            StartUp();

            while (!m_window->ShouldClose())
            {
                Update(m_window->GetTime());
                //m_renderer->Render();
                m_window->SwapBuffers();
            }

            m_window->SetCurrentContext(false);
            Debug::Console::LogInfo("rendering stopped");
        });

        // we are seperating the rendering to a different thread, so we can keep drawing when for e.g we resize the window
        while (!m_window->ShouldClose())
        {
            m_window->PollEvents();
        }

        renderingThread.join();

        // ugly, but have to get context back, so we can clean things up in the destructor
        m_window->SetCurrentContext(true);
    }
}
