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

		mProgramId = glCreateProgram();
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

	void Renderer::Render(const Mesh& meshesToRender)
	{
		// reserving a VAO
		glGenVertexArrays(1, &mVAOId);
		// binding VAO
		glBindVertexArray(mVAOId);
		// reserving a VBO
		glGenBuffers(1, &mVBOId);
		glBindBuffer(GL_ARRAY_BUFFER, mVBOId);

		const std::vector<Vertex>& vertecies = meshesToRender.GetVertecies();
		if (vertecies.empty()) // invalid state
			return;

		// loading buffer with data
		glBufferData(GL_ARRAY_BUFFER, vertecies.size() * sizeof(Vertex), vertecies.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(mPosId); // position
		glVertexAttribPointer(mPosId, mComponentCnt, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
		glEnableVertexAttribArray(mColorId); // color
		glVertexAttribPointer(mColorId, mComponentCnt, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>((sizeof(glm::vec3))));

		// unbinding loaded VAO
		glBindVertexArray(0);
		// unbinding loaded VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// TODO: Load shaders (shader class, shared_ptr<Shader> fragmentShader, vertexShader)

		// TODO: Make the shader class take care of most of these things (eg. fragmentShader->AttachTo(mProgramId), or fragmantShader->LinkWithProgram(m_programID);)
		// glAttachShader(mProgramId, fragmentShaderId)
		// glAttachShader(mProgramId, vertexShaderId)
		// glBindAttribLocation(mProgramId, mPosId, "vs_in_pos");
		// glBindAttribLocation(mProgramId, mColorId, "vs_in_col");
		// glLinkProgram(mProgramId);
		// glDeleteShader(fragmentShaderId); // mark them for deletion after load (they will only be deleted when we detach the shaders from the program)
		// glDeleteShader(vertexShaderId);

		// TODO: The actual rendering
		// glUseProgram(mProgramId);
		// glBindVertexArray(mVAOId);
		// glDrawArrays(GL_TRIANGLE_FAN, 0, vertecies.size());
		// glBindVertexArray(0);
		// glUseProgram(0);
	}
}
