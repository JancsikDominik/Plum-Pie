#ifndef PLUMPIE_RENDERE
#define PLUMPIE_RENDERE

#include "3DObjects/Vertex.hpp"
#include "3DObjects/Mesh.hpp"
#include "ShaderProgram.hpp"


namespace Plum
{
	class Renderer
	{
	public:
		Renderer();
		void SetClearColor(Color clearColor);
		void SetCullFace(bool enable);
		void SetDepthTest(bool enable);
		void UseProgram(GL::ShaderProgram& program);
		void StopUsingCurrentProgram();
		void Render();

	private:
		GL::ShaderProgram* m_Program = nullptr;
		Color m_ClearColor;
		bool m_IsCullfaceEnabled;
		bool m_IsDepthTestEnabled;
	};
	
}

#endif