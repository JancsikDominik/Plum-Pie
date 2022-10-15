#include <GL/glew.h>

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
        virtual void StartUp() override;
    private:
        Renderer renderer;
        Mesh triangle;
    };

    void App::Render()
    {
        renderer.Render(triangle);
    }

    void App::Run()
    {
        glfwMakeContextCurrent(m_Window->glfwWindowPtr);

        InitGlew();
        StartUp();

        while (!m_Window->ShouldClose())
        {
            renderer.Render(triangle);
            m_Window->SwapBuffers();
            glfwWaitEvents();
        }
    }

    void App::StartUp()
    {
        const std::string vertexShaderSourcePath = "D:\\projects\\Plum-Pie\\AppBase\\src\\vertex_shader.glsl";
        auto* vertexShader = new Shader(vertexShaderSourcePath, GL_VERTEX_SHADER);

        Program program;
        program.AttachShader(vertexShader);
        delete vertexShader;

        renderer.UseProgram(program);

        triangle = MakeTriangle();

        VertexArrayObject vao;
        vao.LoadBufferData(ARRAY_BUFFER, triangle.GetVertecies(), STATIC);
        vao.Bind();

        renderer.SetClearColor(Color(0, 0.4f, 0));
    }

}


int main()
{
    Plum::App app;
    app.Run();
    return 0;
}