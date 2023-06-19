#ifndef PLUMPIE_RENDERE
#define PLUMPIE_RENDERE

#include "Core/Renderer.hpp"
#include "Graphics/Vertex.hpp"

#include "GLShaderProgram.hpp"


namespace Plum
{
	class OpenGLRenderer : public Renderer
	{
	public:
		OpenGLRenderer();
		void SetClearColor(Color clearColor) override;
		void SetCullFace(bool enable) override;
		void SetDepthTest(bool enable) override;
		void UseProgram(ShaderProgram& program) override;
		void StopUsingCurrentProgram() override;
		void SetViewport(int x, int y, int width, int height) override;
		void SetUniformData(const std::string& name, const std::any& value) override;
		void Clear() override;
		void Render() override;

	private:
		GL::GLShaderProgram* m_Program = nullptr;
		Color m_ClearColor;
		bool m_IsCullfaceEnabled;
		bool m_IsDepthTestEnabled;
	};
}

#endif