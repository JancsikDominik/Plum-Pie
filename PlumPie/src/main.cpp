#include <iostream>

#include "AppBase/AppBase.hpp"
#include "Renderer/Renderer.hpp"
#include "GLFWWrappers/Window.hpp"

namespace Plum
{
    Mesh MakeTriangle()
    {
        std::vector<Vertex> vertecies;
        vertecies.emplace_back(glm::vec3(-0.5f, -0.5f, 0), Color(1, 1, 1));
        vertecies.emplace_back(glm::vec3(0.0f, 0.5f, 0), Color(1, 1, 1));
        vertecies.emplace_back(glm::vec3(0.5f, -0.5f, 0), Color(1, 1, 1));

        Mesh triangle;
        triangle.AddVertecies(vertecies);

        return triangle;
    }

    class App final : public Plum::AppBase
    {
    public:
        virtual void Render() override;
        virtual void Run() override;
    };

    void App::Render()
    {
        Renderer renderer;
        const Mesh& triangle = MakeTriangle();

        const std::string vertexShaderSourcePath = "D:\\projects\\Plum-Pie\\AppBase\\src\\vertex_shader.glsl";
        auto* vertexShader = new Shader(vertexShaderSourcePath, GL_VERTEX_SHADER);

        Program program;
        program.AttachShader(vertexShader);

        delete vertexShader;

        renderer.UseProgram(program);
    }

    void App::Run()
    {
        using namespace GLFW;
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

        while (!window->ShouldClose())
        {
            Render();
        }

        glfwTerminate();
    }
}


int main()
{
    Plum::App app;
    app.Run();
    return 0;
}