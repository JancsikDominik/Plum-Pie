#ifndef PLUMPIE_RENDERE
#define PLUMPIE_RENDERE

#include <GL/glew.h>
#include <memory>

#include "GLFWWrappers/Window.hpp"
#include "3DObjects/Vertex.hpp"
#include "3DObjects/Mesh.hpp"

#include "Types.hpp"
#include "VAO.hpp"
#include "VBO.hpp"


namespace Plum
{
	class Renderer
	{
	public:
		Renderer();
		void SetClearColor(Color clearColor);
		void SetCullFace(bool enable);
		void SetDepthTest(bool enable);
		void Render(const Mesh& meshToRender);

	private:
		std::unique_ptr<GLFW::Window> mWindow;
		std::unique_ptr<VAO> mVAO;
		std::unique_ptr<VBO> mVBO;
		Color mClearColor;
		bool mIsCullfaceEnabled;
		bool mIsDepthTestEnabled;
		ushort mProgramId = 0;
		static constexpr ushort mPosId = 0;
		static constexpr ushort mColorId = 1;
		static constexpr ushort mComponentCnt = 3;
	};
	
}

#endif