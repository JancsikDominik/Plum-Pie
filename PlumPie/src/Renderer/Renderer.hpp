#ifndef PLUMPIE_RENDERE
#define PLUMPIE_RENDERE

#include <GL/glew.h>
#include "../GLFWWrappers/Window.hpp"
#include "../3DObjects/Vertex.hpp"
#include "../3DObjects/Mesh.hpp"
#include "../Types.hpp"
#include <memory>
#include <vector>


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
		Color mClearColor;
		bool mIsCullfaceEnabled;
		bool mIsDepthTestEnabled;
		ushort mVAOId = 0;
		ushort mVBOId = 0;
		ushort mProgramId = 0;
		static constexpr ushort mPosId = 0;
		static constexpr ushort mColorId = 1;
		static constexpr ushort mComponentCnt = 3;
	};
	
}

#endif