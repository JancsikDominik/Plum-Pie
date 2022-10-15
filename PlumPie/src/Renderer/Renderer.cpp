#include "Renderer.hpp"

namespace Plum
{
	Renderer::Renderer()
	{
		SetClearColor(Color(0, 0.4f, 0));

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

	void Renderer::Render(const Mesh& meshToRender, const Program& program)
	{
		glClear(GL_COLOR_BUFFER_BIT);


		const std::vector<Vertex>& vertecies = meshToRender.GetVertecies();
		if (vertecies.empty()) // invalid state
			return;

		program.Use();

		// loading buffer with data
		//mVAO->LoadBufferData(BindingTarget::ARRAY_BUFFER, vertecies, DrawType::STATIC);
		//mVAO->SetUpAttributeAtIndex(mPosId, mComponentCnt, GL_FLOAT, GL_FALSE, vertecies, 0);
		//mVAO->SetUpAttributeAtIndex(mColorId, mComponentCnt, GL_FLOAT, GL_FALSE, vertecies, sizeof(glm::vec3));

		// releasing after setup

		//mVAO->Release();
		//mVBO->Release();


		// TODO: The actual rendering
		// glUseProgram(mProgramId);
		// glBindVertexArray(mVAOId);
		// glDrawArrays(GL_TRIANGLE_FAN, 0, vertecies.size());
		// glBindVertexArray(0);
		// glUseProgram(0);

		program.StopUsing();
	}
}
