#include "Program.hpp"

namespace Plum
{
	Program::Program()
	{
		mProgramId = glCreateProgram();
	}

	Program::~Program()
	{
		if (mProgramId != 0)
			glDeleteProgram(mProgramId);
	}

	void Program::AttachShader(Shader* shader) const
	{
		shader->Attach(mProgramId);
		glLinkProgram(mProgramId);
	}

	void Program::AttachShaders(const std::vector<Shader*>& shaders) const
	{
		for(const auto& shader : shaders)
		{
			shader->Attach(mProgramId);
		}

		glLinkProgram(mProgramId);

		glBindFragDataLocation(mProgramId, 0, "outColor");
	}

	void Program::Use() const
	{
		glUseProgram(mProgramId);
	}

	void Program::StopUsing() const
	{
		glUseProgram(0);
	}
}
