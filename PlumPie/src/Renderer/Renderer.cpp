#include "Renderer.hpp"

namespace Plum
{
	Renderer::Renderer()
	{
		mIsCullfaceEnabled = true;
		mIsDepthTestEnabled = true;

		SetCullFace(mIsCullfaceEnabled);
		SetDepthTest(mIsDepthTestEnabled);
	}

	void Renderer::SetClearColor(Color clearColor)
	{
		mClearColor = clearColor;
		glClearColor(mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a);
	}

	void Renderer::SetCullFace(bool enable)
	{
		mIsCullfaceEnabled = enable;
		mIsCullfaceEnabled ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
	}

	void Renderer::SetDepthTest(bool enable)
	{
		mIsDepthTestEnabled = enable;
		mIsDepthTestEnabled ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
	}

	void Renderer::UseProgram(Program& program)
	{

		mProgram = &program;
		mProgram->Use();
	}

	void Renderer::StopUsingCurrentProgram()
	{
		if(mProgram != nullptr)
		{
			mProgram->StopUsing();
			mProgram = nullptr;
		}
	}

	void Renderer::Render(const Mesh& meshToRender)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	}
}
