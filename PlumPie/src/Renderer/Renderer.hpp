#ifndef PLUMPIE_RENDERE
#define PLUMPIE_RENDERE

#include "3DObjects/Vertex.hpp"
#include "3DObjects/Mesh.hpp"
#include "Program.hpp"


namespace Plum
{
	class Renderer
	{
	public:
		Renderer();
		void SetClearColor(Color clearColor);
		void SetCullFace(bool enable);
		void SetDepthTest(bool enable);
		void UseProgram(Program& program);
		void StopUsingCurrentProgram();
		void Render(const Mesh& meshToRender);

	private:
		Program* m_Program = nullptr;
		Color m_ClearColor;
		bool m_IsCullfaceEnabled;
		bool m_IsDepthTestEnabled;
	};
	
}

#endif