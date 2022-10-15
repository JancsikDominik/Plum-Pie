#ifndef PLUMPIE_RENDERE
#define PLUMPIE_RENDERE

#include <GL/glew.h>
#include <memory>

#include "GLFWWrappers/Window.hpp"
#include "3DObjects/Vertex.hpp"
#include "3DObjects/Mesh.hpp"

#include "Types.hpp"
#include "VertexBufferObjectManager.hpp"
#include "VertexArrayObject.hpp"
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
		void Render(const Mesh& meshToRender, const Program& program);

	private:
		Color mClearColor;
		bool mIsCullfaceEnabled;
		bool mIsDepthTestEnabled;
		static constexpr uint mPosId = 0;
		static constexpr uint mColorId = 1;
		static constexpr uint mComponentCnt = 3;
	};
	
}

#endif