#include "ShaderProgram.hpp"

#include <Debugging/Debug.hpp>

#include "Debugging/Console.hpp"

namespace Plum::GL
{
	ShaderProgram::ShaderProgram()
	{
		m_ProgramID = glCreateProgram();
	}

	ShaderProgram::~ShaderProgram()
	{
		Release();
	}

	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept
	{
		if (this != &other)
		{
			Release();
			std::swap(m_ProgramID, other.m_ProgramID);
			std::swap(m_UniformLocations, other.m_UniformLocations);
		}

		return *this;
	}

	void ShaderProgram::AttachShader(const Shader& shader) const
	{
		GL_CALL(glAttachShader(m_ProgramID, shader.GetShaderID()));

		LinkProgram();
	}

	void ShaderProgram::AttachShaders(const std::vector<Shader*>& shaders) const
	{
		for(const auto& shader : shaders)
		{
			GL_CALL(glAttachShader(m_ProgramID, shader->GetShaderID()));
		}

		LinkProgram();
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
		GLint ret;
		GL_CALL(ret = glGetAttribLocation(m_ProgramID, attributeName.c_str()));
		return ret;
	}

	GLint ShaderProgram::GetUniformLocation(const std::string& uniformName)
	{
		return glGetUniformLocation(m_ProgramID, uniformName.c_str());
	}

	void ShaderProgram::Release()
	{
		GL_CALL(glDeleteProgram(m_ProgramID));
	}

	void ShaderProgram::LinkProgram() const
	{
		GL_CALL(glLinkProgram(m_ProgramID));

		GLint status;
		GL_CALL(glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &status));
		if (status == GL_FALSE)
		{
			GLint infoLogLength;
			GL_CALL(glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &infoLogLength));

			GLchar* strInfoLog = new GLchar[infoLogLength + 1];
			GL_CALL(glGetProgramInfoLog(m_ProgramID, infoLogLength, NULL, strInfoLog));
			Debug::Console::LogError("linker failure : % s\n", strInfoLog);
			delete[] strInfoLog;
		}
	}
}
