#include <GL/glew.h>
#include <iostream>

#include "AppBase/AppBase.hpp"
#include "Core/Renderer.hpp"
#include "GLFWWrappers/Window.hpp"
#include "Core/VertexArrayObject.hpp"

namespace Plum
{
    class App final : public AppBase
    {
    private:
        virtual void Render() override;
        virtual void StartUp() override;
        virtual void Update() override;

        GL::ShaderProgram shaderProgram;
        GL::VertexArrayObject vao;
    };

    void App::Render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        std::vector<float> attrib = { static_cast<float>(sin(glfwGetTime()) * 0.5f),
                                      static_cast<float>(cos(glfwGetTime()) * 0.6f),
                                      0.0f, 
                                      0.0f };

        glVertexAttrib4fv(1, attrib.data());
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    }

    void App::StartUp()
    {
        glClearColor(0, 0.4, 0, 1);
        std::vector<int> indices{ 0, 1, 2 };
        
        std::vector<float> vertices = { 0.0f,  0.5f,
                                        0.5f, -0.5f,
                                       -0.5f, -0.5f };

        GL::Shader vertexShader("D:/projects/Plum-Pie/PlumPie/src/vertex_shader.glsl", GL_VERTEX_SHADER);
        GL::Shader fragmentShader("D:/projects/Plum-Pie/PlumPie/src/fragment_shader.glsl", GL_FRAGMENT_SHADER);

        shaderProgram.AttachShaders({ vertexShader, fragmentShader });
        shaderProgram.Use();

        vao.Bind();
        vao.AttachBuffer<float>(GL::ARRAY, vertices.size(), vertices.data(), GL::STATIC);
        vao.AttachBuffer<int>(GL::ELEMENT, indices.size(), indices.data(), GL::STATIC);
        vao.EnableAttribute(shaderProgram.GetAttributeLocation("position"), 2, 0, 0);
    }

    void App::Update()
    {

    }

}


int main()
{
    Plum::App app;
    app.Run();
    return 0;
}