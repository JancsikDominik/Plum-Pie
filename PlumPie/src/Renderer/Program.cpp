#include "Program.hpp"

namespace Plum
{
	Program::Program()
	{
		m_ProgramID = glCreateProgram();
	}

	Program::~Program()
	{
		if (m_ProgramID != 0)
			glDeleteProgram(m_ProgramID);
	}

	void Program::AttachShader(const Shader& shader) const
	{
		glAttachShader(m_ProgramID, shader.GetShaderID());
		glLinkProgram(m_ProgramID);
	}

	void Program::AttachShaders(const std::vector<Shader>& shaders) const
	{
		for(const auto& shader : shaders)
		{
			glAttachShader(m_ProgramID, shader.GetShaderID());
		}

		glLinkProgram(m_ProgramID);

		glBindFragDataLocation(m_ProgramID, 0, "outColor");
	}

	void Program::Use() const
	{
		glUseProgram(m_ProgramID);
	}

	void Program::StopUsing() const
	{
		glUseProgram(0);
	}
}
