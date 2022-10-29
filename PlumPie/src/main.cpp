#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <Debugging/Debug.hpp>

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
        GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        const std::vector<float> attrib = { static_cast<float>(sin(glfwGetTime())) * 0.5f,
											static_cast<float>(cos(glfwGetTime())) * 0.5f,
											0.0f, 
											0.0f };

        GL_CALL(glVertexAttrib4fv(1, attrib.data()));
        GL_CALL(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0));
    }

    void App::StartUp()
    {
        // going 3D :)
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        glm::mat4 projection = glm::perspective(glm::radians(60.0f), 1280.f / 960.f, 0.1f, 100.0f);

        const std::vector<int> indices{ 0, 1, 2 };

        const std::vector<float> vertices = { 0.0f,  0.5f,
											  0.5f, -0.5f,
        									 -0.5f, -0.5f };

        GL::Shader vertexShader("D:/projects/Plum-Pie/PlumPie/src/vertex_shader.glsl", GL_VERTEX_SHADER);
        GL::Shader fragmentShader("D:/projects/Plum-Pie/PlumPie/src/fragment_shader.glsl", GL_FRAGMENT_SHADER);

        shaderProgram.AttachShaders({ &vertexShader, &fragmentShader });
        shaderProgram.Use();

        const auto modelLoc = shaderProgram.GetUniformLocation("model");
        const auto viewLoc = shaderProgram.GetUniformLocation("view");
        const auto projectionLoc = shaderProgram.GetUniformLocation("projection");

        GL_CALL(glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)));
        GL_CALL(glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view)));
        GL_CALL(glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection)));

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