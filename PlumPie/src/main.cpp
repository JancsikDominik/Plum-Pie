/****************************************************************************
		THIS FILE IS USED FOR TESTING PURPOSES THE ENGINE IS NOT FINISHED,
					THERE IS NO PROPER "ENTRY POINT" YET
*****************************************************************************/

#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "AppBase/AppBase.hpp"
#include "Core/OpenGL/OpenGLRenderer.hpp"
#include "Core/OpenGL/VertexArrayObject.hpp"
#include "Core/OpenGL/GLShaderProgram.hpp"
#include "Graphics/Camera.hpp"

namespace Plum
{
	class App final : public AppBase
	{
	public:
		void StartUp() override;
		void Update(double currTimeStamp) override;

		void OnKeyEvent(const KeyEvent& keyevent) override {}
		void OnMouseEvent(const MouseEvent& mouseEvent) override
		{
			switch (mouseEvent.type)
			{
			case Mouse::EventType::Move:
				Debug::Console::Log("new mouse pos: %f %f", mouseEvent.pos.x, mouseEvent.pos.y);
				break;
			case Mouse::EventType::ButtonPress:
				Debug::Console::Log("mouse btn pressed: %d", mouseEvent.button);
				Debug::Console::Log("mouse btn action: %d", mouseEvent.action);
				Debug::Console::Log("mouse btn modifiers: %d", mouseEvent.modifiers);
				break;
			case Mouse::EventType::Scroll:
				Debug::Console::Log("offset: %f %f", mouseEvent.scrollOffset.x, mouseEvent.scrollOffset.y);
			}
		}
		void OnResize(uint32_t width, uint32_t height) override {}

	private:
		GL::GLShaderProgram shaderProgram;
		GL::VertexArrayObject vao;
		Camera camera{ 1280, 960 };
	};

	void App::StartUp()
	{
		SetBackendApi(BackendApi::OpenGL);

		auto model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		camera.SetPosition({0, 0, -3});

		const std::vector<int> indices{ 0, 1, 2 };

		const std::vector<glm::vec2> vertices = {
			 glm::vec2( 0.5f, -0.5f),
			 glm::vec2( 0.0f,  0.5f),
			 glm::vec2(-0.5f, -0.5f)
		};

		vao.Bind();
		vao.AttachBuffer<glm::vec2>(GL::BufferType::Array, vertices.size(), vertices.data(), GL::DrawType::Static);
		vao.AttachBuffer<int>(GL::BufferType::Element, indices.size(), indices.data(), GL::DrawType::Static);

		GL::GLShader vertexShader("./Shaders/vertex_shader.glsl", Shader::Type::Vertex);
		GL::GLShader fragmentShader("./Shaders/fragment_shader.glsl", Shader::Type::Fragment);

		shaderProgram.AttachShaders({&vertexShader, &fragmentShader});
		shaderProgram.Use();

		constexpr auto attrLayout = GL::AttributeLayout<glm::vec2>(2, 0, false, GL::GLTypes::Float);
		vao.EnableAttribute(shaderProgram.GetAttributeLocation("position"), attrLayout);

		shaderProgram.SetUniformMatrix("model", model, false);
		shaderProgram.SetUniformMatrix("viewProj", camera.GetViewProjection(), false);

		m_renderer->SetClearColor({ 0.1f, 0.3f, 0.4f, 1.f });
	}

	void App::Update(double currTimeStamp)
	{
		camera.Update();
		m_renderer->Clear();

		const glm::vec4 offset = {
			static_cast<float>(sin(currTimeStamp) * 0.5f),
			static_cast<float>(cos(currTimeStamp) * 0.5f),
			0.0f,
			0.0f
		};

		shaderProgram.SetUniform("offset", offset);
	}
}


int main()
{
	Plum::App app;
	app.Run();
	return 0;
}
