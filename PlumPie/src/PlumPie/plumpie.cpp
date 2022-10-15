#include <GL/glew.h>
#include <iostream>

#include "GLFWWrappers/Window.hpp"
#include "3DObjects/Vertex.hpp"
#include "3DObjects/Mesh.hpp"
#include "Renderer/Renderer.hpp"

#include "plumpie.hpp"


using namespace Plum::GLFW;

namespace Plum
{
    Mesh MakeTriangle()
    {
        std::vector<Vertex> vertecies;
        vertecies.push_back({ glm::vec3(-0.5f, -0.5f, 0), Color(1, 1, 1) });
        vertecies.push_back({ glm::vec3(0.0f, 0.5f, 0), Color(1, 1, 1) });
        vertecies.push_back({ glm::vec3(0.5f, -0.5f, 0), Color(1, 1, 1) });

        Mesh triangle;
        triangle.AddVertecies(vertecies);

        return triangle;
    }

    void PlumPie::Run()
    {
        Window* window;
        try
        {
            window = new Window{};
        }
        catch (...)
        {
            glfwTerminate();
            return;
        }

        window->mWindow = glfwCreateWindow(640, 480, "asd", nullptr, nullptr);

        glfwMakeContextCurrent(window->mWindow);


        if (glewInit() != GLEW_OK)
            std::cout << "Error" << std::endl;

        Renderer renderer;
        const Mesh& triangle = MakeTriangle();

        const std::string vertexShaderSourcePath = "D:\\projects\\Plum-Pie\\PlumPie\\src\\vertex_shader.glsl";
        auto* vertexShader = new Shader(vertexShaderSourcePath, GL_VERTEX_SHADER);

        const Program program;
        program.AttachShader(vertexShader);

        delete vertexShader;

        /* Loop until the user closes the window */
        while (!window->ShouldClose())
        {
            renderer.Render(triangle, program);

            /* Swap front and back buffers */
            window->SwapBuffers();
        }

        glfwTerminate();
    }
}