#include <GL/glew.h>
#include <iostream>

#include "AppBase.hpp"
#include "GLFWWrappers/Window.hpp"
#include "Core/OpenGL/OpenGLRenderer.hpp"

Plum::AppBase::AppBase()
    : m_renderer{ nullptr }
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
	delete m_window;
    delete m_renderer;
    glfwTerminate();
}

void Plum::AppBase::Run()
{
    // TODO: print correct version with multiple apis
    Debug::Console::LogInfo("OpenGL version: %s", glGetString(GL_VERSION));

    StartUp();
    while (!m_window->ShouldClose())
    {
        Update(m_window->GetTime());
        m_renderer->Render();
        m_window->SwapBuffers();
        m_window->PollEvents();
    }
}

void Plum::AppBase::SetBackendApi(BackendApi api)
{
	switch (api)
	{
	case BackendApi::OpenGL:
        m_renderer = new GL::OpenGLRenderer();
        break;
	case BackendApi::Vulkan:
        //m_renderer = new Vulkan::VKRenderer();
        //break;
	default:
        m_renderer = nullptr;
        Debug::Console::LogError("unknown backend api");
        break;
	}
}

void Plum::AppBase::InitGlew() const
{
	const GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        Debug::Console::LogError("failed to initialize glew");
        glfwTerminate();
    }
}
