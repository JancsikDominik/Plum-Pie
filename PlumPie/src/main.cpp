#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Debugging/Debug.hpp"
#include "AppBase/AppBase.hpp"
#include "Core/OpenGL/OpenGLRenderer.hpp"
#include "Core/OpenGL/VertexArrayObject.hpp"
#include "Core/OpenGL/GLShaderProgram.hpp"

namespace Plum
{
	class App final : public AppBase
	{
	public:
	private:
		void StartUp() override;
		void Update(double currTimeStamp) override;

		GL::GLShaderProgram shaderProgram;
		GL::VertexArrayObject vao;
	};

	void App::StartUp()
	{
		SetBackendApi(BackendApi::OpenGL);

		auto model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		auto view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		glm::mat4 projection = glm::perspective(glm::radians(60.0f), 1280.f / 960.f, 0.1f, 100.0f);

		const std::vector<int> indices{0, 1, 2};

		const std::vector<float> vertices = {
			 0.0f,  0.5f,
			 0.5f, -0.5f,
			-0.5f, -0.5f
		};

		vao.Bind();
		vao.AttachBuffer<float>(GL::ARRAY, vertices.size(), vertices.data(), GL::STATIC);
		vao.AttachBuffer<int>(GL::ELEMENT, indices.size(), indices.data(), GL::STATIC);

		GL::GLShader vertexShader("./Shaders/vertex_shader.glsl", Shader::Type::Vertex);
		GL::GLShader fragmentShader("./Shaders/fragment_shader.glsl", Shader::Type::Fragment);

		shaderProgram.AttachShaders({&vertexShader, &fragmentShader});

		m_renderer->UseProgram(shaderProgram);

		vao.EnableAttribute(shaderProgram.GetAttributeLocation("position"), 2, 0, 0);

		const auto modelLoc = shaderProgram.GetUniformLocation("model");
		const auto viewLoc = shaderProgram.GetUniformLocation("view");
		const auto projectionLoc = shaderProgram.GetUniformLocation("projection");

		GL_CALL(glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)));
		GL_CALL(glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view)));
		GL_CALL(glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection)));

		m_renderer->SetClearColor({ 0.1f, 0.3f, 0.4f, 1.f });
	}

	void App::Update(double currTimeStamp)
	{
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		const std::vector<float> attrib = {
			static_cast<float>(sin(currTimeStamp) * 0.5f),
			static_cast<float>(cos(currTimeStamp) * 0.5f),
			0.0f,
			0.0f
		};

		GL_CALL(glVertexAttrib4fv(1, attrib.data()));
	}
}


int main()
{
	Plum::App app;
	app.Run();
	return 0;
}
