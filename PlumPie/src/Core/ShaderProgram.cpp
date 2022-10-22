#include "ShaderProgram.hpp"

namespace Plum::GL
{
	ShaderProgram::ShaderProgram()
	{
		m_ProgramID = glCreateProgram();
	}

	ShaderProgram::~ShaderProgram()
	{
		if (m_ProgramID != 0)
			glDeleteProgram(m_ProgramID);
	}

	void ShaderProgram::AttachShader(const Shader& shader) const
	{
		glAttachShader(m_ProgramID, shader.GetShaderID());
		glLinkProgram(m_ProgramID);
	}

	void ShaderProgram::AttachShaders(const std::vector<Shader>& shaders) const
	{
		for(const auto& shader : shaders)
		{
			glAttachShader(m_ProgramID, shader.GetShaderID());
		}

		glLinkProgram(m_ProgramID);
	}

	void ShaderProgram::Use() const
	{
		glUseProgram(m_ProgramID);
	}

	void ShaderProgram::StopUsing() const
	{
		glUseProgram(0);
	}
	GLint ShaderProgram::GetAttributeLocation(const std::string& attributeName)
	{
		return glGetAttribLocation(m_ProgramID, attributeName.c_str());
	}
}
