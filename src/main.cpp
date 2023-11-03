/****************************************************************************
		THIS FILE IS USED FOR TESTING PURPOSES THE FRAMEWORK IS NOT FINISHED,
			  SO I COMPILE IT AS AN EXE FOR NOW, FOR EASIER TESTING
*****************************************************************************/

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "AppBase/AppBase.hpp"
#include "Graphics/Camera.hpp"

namespace Plum
{
	class App final : public AppBase
	{
	public:
		App() 
			: AppBase("Test")
		{
		}

		void StartUp() override;
		void Update(double currTimeStamp) override;

		void OnKeyEvent(const KeyEvent& keyevent) override {}
		void OnMouseEvent(const MouseEvent& mouseEvent) override {}
		void OnResize(uint32_t width, uint32_t height) override {}

	private:
		//GL::GLShaderProgram shaderProgram;
		//GL::VertexArrayObject vao;
		//GLTexture::Ref texture;
		Camera camera{ 1280, 960 };
	};

	void App::StartUp()
	{
		//SetBackendApi(BackendApi::OpenGL);

		//auto model = glm::mat4(1.0f);
		//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		//camera.SetPosition({0, 0, -3});

		//const std::vector<int> indices{ 0, 1, 2 };

		//const std::vector<glm::vec2> vertices = {
		//	 glm::vec2( 0.5f, -0.5f), glm::vec2(1.f,  0.f),
		//	 glm::vec2( 0.0f,  0.5f), glm::vec2(0.5f, 1.f),
		//	 glm::vec2(-0.5f, -0.5f), glm::vec2(0.f,  0.f)
		//};

		//vao.Bind();
		//vao.AttachBuffer<glm::vec2>(GL::BufferType::Array, vertices.size(), vertices.data(), GL::DrawType::Static);
		//vao.AttachBuffer<int>(GL::BufferType::Element, indices.size(), indices.data(), GL::DrawType::Static);

		//GL::GLShader vertexShader("./Shaders/vertex_shader.glsl", Shader::Type::Vertex);
		//GL::GLShader fragmentShader("./Shaders/fragment_shader.glsl", Shader::Type::Fragment);

		//shaderProgram.AttachShaders({&vertexShader, &fragmentShader});
		//m_renderer->SetProgram(shaderProgram);

		//// TODO: is there a better way to do this?
		//constexpr auto posLayout = GL::AttributeLayout<glm::vec2>(2, 0, 2, false, GL::GLTypes::Float);
		//vao.EnableAttribute(shaderProgram.GetAttributeLocation("position"), posLayout);

		//constexpr auto uvLayout = GL::AttributeLayout<glm::vec2>(2, sizeof(glm::vec2), 2, false, GL::GLTypes::Float);
		//vao.EnableAttribute(shaderProgram.GetAttributeLocation("in_uv"), uvLayout);

		//shaderProgram.SetUniformMatrix("model", model, false);
		//shaderProgram.SetUniformMatrix("viewProj", camera.GetViewProjection(), false);

		//texture = std::make_shared<GLTexture>("./texture.png", TextureTarget::Tex2D, TextureFormat::RGBA);
		//texture->Bind();
		//texture->GenerateMipMaps();
		//texture->SetMinFilter(TextureFilter::Linear);
		//texture->SetMagFilter(TextureFilter::Nearest);
		//texture->SetWrapS(TextureWrapping::Repeat);
		//texture->SetWrapT(TextureWrapping::Repeat);

		//// TODO: shaderprogram.AttachTexture(name, slot);
		//shaderProgram.SetUniform<int>("tex", 0);

		//m_renderer->SetClearColor({ 0.1f, 0.3f, 0.4f, 1.f });
	}

	void App::Update(double currTimeStamp)
	{
		//camera.Update();
		//m_renderer->Clear();

		//const glm::vec4 offset = {
		//	static_cast<float>(sin(currTimeStamp) * 0.5f),
		//	static_cast<float>(cos(currTimeStamp) * 0.5f),
		//	0.0f,
		//	0.0f
		//};

		//shaderProgram.SetUniform("offset", offset);
	}
}


int main()
{
	Plum::App app;
	app.Run();
	return 0;
}
