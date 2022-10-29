#include "ShaderProgram.hpp"

#include <Debugging/Debug.hpp>

namespace Plum::GL
{
	ShaderProgram::ShaderProgram()
	{
		GL_CALL(m_ProgramID = glCreateProgram());
	}

	ShaderProgram::~ShaderProgram()
	{
		if (m_ProgramID != 0)
			GL_CALL(glDeleteProgram(m_ProgramID));
	}

	void ShaderProgram::AttachShader(const Shader& shader) const
	{
		GL_CALL(glAttachShader(m_ProgramID, shader.GetShaderID()));
		GL_CALL(glLinkProgram(m_ProgramID));
	}

	void ShaderProgram::AttachShaders(const std::vector<Shader*>& shaders) const
	{
		for(const auto& shader : shaders)
		{
			GL_CALL(glAttachShader(m_ProgramID, shader->GetShaderID()));
		}

		GL_CALL(glLinkProgram(m_ProgramID));
	}

	void ShaderProgram::Use() const
	{
		GL_CALL(glUseProgram(m_ProgramID));
	}

	void ShaderProgram::StopUsing() const
	{
		GL_CALL(glUseProgram(0));
	}

	GLint ShaderProgram::GetAttributeLocation(const std::string& attributeName)
	{
		return glGetAttribLocation(m_ProgramID, attributeName.c_str());
	}

	GLint ShaderProgram::GetUniformLocation(const std::string& uniformName)
	{
		return glGetUniformLocation(m_ProgramID, uniformName.c_str());
	}
}
