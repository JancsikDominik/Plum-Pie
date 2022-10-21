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

        GLuint m_Indicies[3];
    };

    void App::Render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        GLfloat attrib[] = { (float)sin(glfwGetTime()) * 0.5f,
                             (float)cos(glfwGetTime()) * 0.6f,
                             0.0f, 0.0f };

        glVertexAttrib4fv(1, attrib);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    }

    void App::StartUp()
    {
        for (int i = 0; i < 3; i++)
        {
            m_Indicies[i] = i;
        }

        GLfloat const vertices[] = { 0.0f,  0.5f,
                                     0.5f, -0.5f,
                                    -0.5f, -0.5f };

        Plum::GL::Shader vertexShader("D:/projects/Plum-Pie/PlumPie/src/vertex_shader.glsl", GL_VERTEX_SHADER);
        Plum::GL::Shader fragmentShader("D:/projects/Plum-Pie/PlumPie/src/fragment_shader.glsl", GL_FRAGMENT_SHADER);

        Plum::GL::ShaderProgram shaderProgram;
        shaderProgram.AttachShaders({ vertexShader, fragmentShader });
        shaderProgram.Use();

        GL::VertexArrayObject vao;
        vao.Bind();
        vao.AttachBuffer(GL::ARRAY, sizeof(vertices), vertices, GL::STATIC);
        GLint PositionAttribute = glGetAttribLocation(shaderProgram.GetProgramID(), "position");
        glEnableVertexAttribArray(PositionAttribute);
        glVertexAttribPointer(PositionAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
        vao.AttachBuffer(GL::ELEMENT, sizeof(m_Indicies), m_Indicies, GL::STATIC);

        /*GLuint VAO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        GLuint VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        GLuint EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_Indicies), m_Indicies, GL_STATIC_DRAW);*/

        /*GLint PositionAttribute = glGetAttribLocation(shaderProgram.GetProgramID(), "position");
        glEnableVertexAttribArray(PositionAttribute);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(PositionAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);*/
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