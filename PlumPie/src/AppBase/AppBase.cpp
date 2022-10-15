#include <GL/glew.h>
#include <iostream>

#include "AppBase.hpp"
#include "GLFWWrappers/Window.hpp"

Plum::AppBase::AppBase()
{
    try
    {
        m_Window = new GLFW::Window();
    }
    catch (...)
    {
        glfwTerminate();
        return;
    }

    m_Window->glfwWindowPtr = glfwCreateWindow(640, 480, "asd", nullptr, nullptr);
}

Plum::AppBase::~AppBase()
{
	delete m_Window;
    glfwTerminate();
}

void Plum::AppBase::InitGlew() const
{
    if (glewInit() != GLEW_OK)
        std::cout << "Error" << std::endl;
}
