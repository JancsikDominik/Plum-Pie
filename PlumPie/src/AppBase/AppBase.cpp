#include <GL/glew.h>
#include <iostream>

#include "AppBase.hpp"
#include "GLFWWrappers/Window.hpp"

Plum::AppBase::AppBase()
{
    try
    {
        m_Window = new GLFW::Window("sandbox");
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
	delete m_Window;
    glfwTerminate();
}

void Plum::AppBase::Run()
{
    StartUp();

    while (!m_Window->ShouldClose())
    {
        Update();
        Render();
        m_Window->SwapBuffers();
        glfwPollEvents();
    }
}

void Plum::AppBase::InitGlew() const
{
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
        glfwTerminate();
    }
}
