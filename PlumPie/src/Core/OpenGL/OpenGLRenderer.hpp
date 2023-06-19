#ifndef PLUMPIE_RENDERE
#define PLUMPIE_RENDERE

#include "Graphics/Vertex.hpp"
#include "GLShaderProgram.hpp"


namespace Plum
{
	class OpenGLRenderer
	{
	public:
		OpenGLRenderer();
		void SetClearColor(Color clearColor);
		void SetCullFace(bool enable);
		void SetDepthTest(bool enable);
		void UseProgram(GL::GLShaderProgram& program);
		void StopUsingCurrentProgram();
		void Render();

	private:
		GL::GLShaderProgram* m_Program = nullptr;
		Color m_ClearColor;
		bool m_IsCullfaceEnabled;
		bool m_IsDepthTestEnabled;
	};
}

#endif