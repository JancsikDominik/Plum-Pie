#include "ShaderProgram.hpp"

#include <Debugging/Debug.hpp>
#include <glm/gtc/type_ptr.hpp>

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
		if (m_UniformLocations.contains(uniformName))
			return m_UniformLocations[uniformName];

		const GLint newLocation = glGetUniformLocation(m_ProgramID, uniformName.c_str());
		m_UniformLocations[uniformName] = newLocation;
		return newLocation;
	}

	void ShaderProgram::SetUnifrom4f(const std::string& name, const glm::vec4& vec)
	{
		const auto& location = GetUniformLocation(name);
		GL_CALL(glUniform4f(location, vec.x, vec.y, vec.z, vec.w));
	}

	void ShaderProgram::SetUnifrom4x4Matrix(const std::string& name, const glm::mat4& matrix)
	{
		const auto& location = GetUniformLocation(name);
		GL_CALL(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix)));
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
