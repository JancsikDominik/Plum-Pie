#include <glew.h>
#include <iostream>
#include <thread>

#include "AppBase.hpp"
#include "GLFWWrappers/Window.hpp"
#include "Core/OpenGL/OpenGLRenderer.hpp"

Plum::AppBase::AppBase()
    : KeyEventObserver()
    , ResizeEventObserver()
    , MouseEventObserver()
    , m_renderer{ nullptr }
{
    try
    {
        m_window = new GLFW::Window("sandbox");
        InitGlew();
    }
    catch (...)
    {
        glfwTerminate();
        return;
    }
}

Plum::AppBase::~AppBase()
{
    delete m_renderer;
    delete m_window;
    glfwTerminate();
    glfwSetErrorCallback(nullptr);
}

void Plum::AppBase::Run()
{
    // SetCurrentContext is called in the constructor of the GLFW window, but 
    // when moving a context between threads, we must make it non-current on the old thread before making it current on the new one.
    // so by setting SetCurrentContext to false on this thread, we can set the context to true on the other thread
    m_window->SetCurrentContext(false);

    // starting rendering thread
    std::thread renderingThread([&]() {

        m_window->SetCurrentContext(true);

        StartUp();

        // call it after start up, so we don't get Unknown (hopefully)
        PrintRenderingAPIVersion();

        while (!m_window->ShouldClose())
        {
            Update(m_window->GetTime());
            m_renderer->Render();
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

void Plum::AppBase::SetBackendApi(BackendApi api)
{
	switch (api)
	{
	case BackendApi::OpenGL:
        m_renderer = new GL::OpenGLRenderer();
        m_renderingAPI = BackendApi::OpenGL;
        break;
	// case BackendApi::Vulkan:
        //m_renderer = new Vulkan::VKRenderer();
        //break;
	default:
        m_renderer = nullptr;
        m_renderingAPI = BackendApi::Unknown;
        Debug::Console::LogError("unknown backend api");
        abort();
        break;
	}
}

void Plum::AppBase::InitGlew() const
{
	const GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        Debug::Console::LogError("glew error: %s", glewGetErrorString(err));
        glfwTerminate();
        throw std::runtime_error("failed to initialize glew");
    }
}

void Plum::AppBase::PrintRenderingAPIVersion() const
{
    switch (m_renderingAPI)
    {
    case BackendApi::OpenGL:
        Debug::Console::LogInfo("OpenGL version: %s", glGetString(GL_VERSION));
        break;
    // case BackendApi::Vulkan:
    case BackendApi::Unknown:
    default:
        Debug::Console::LogError("Please set the rendering api in the program's StartUp() method");
        break;
    }
}
