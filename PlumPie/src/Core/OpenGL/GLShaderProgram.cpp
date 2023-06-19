#include "GLShaderProgram.hpp"

#include <Debugging/Debug.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Debugging/Console.hpp"

namespace Plum::GL
{
	GLShaderProgram::GLShaderProgram()
	{
		m_ProgramID = glCreateProgram();
	}

	GLShaderProgram::~GLShaderProgram()
	{
		Release();
	}

	GLShaderProgram& GLShaderProgram::operator=(GLShaderProgram&& other) noexcept
	{
		if (this != &other)
		{
			Release();
			std::swap(m_ProgramID, other.m_ProgramID);
			std::swap(m_UniformLocations, other.m_UniformLocations);
		}

		return *this;
	}

	void GLShaderProgram::AttachShader(const Shader* shader) const
	{
		const auto& glShader = dynamic_cast<const GLShader*>(shader);
		if (glShader == nullptr)
		{
			Debug::Console::LogGLError("Can't cast shader to GLShader");
			return;
		}

		GL_CALL(glAttachShader(m_ProgramID, glShader->GetShaderID()));

		LinkProgram();
	}

	void GLShaderProgram::AttachShaders(const std::vector<Shader*>& shaders) const
	{
		for(const auto& shader : shaders)
		{
			const auto& glShader = dynamic_cast<GLShader*>(shader);
			if (glShader == nullptr)
			{
				Debug::Console::LogGLError("Can't cast shader to GLShader");
				break;
			}


			GL_CALL(glAttachShader(m_ProgramID, glShader->GetShaderID()));
		}

		LinkProgram();
	}

	void GLShaderProgram::Use() const
	{
		GL_CALL(glUseProgram(m_ProgramID));
	}

	void GLShaderProgram::StopUsing() const
	{
		GL_CALL(glUseProgram(0));
	}

	GLint GLShaderProgram::GetAttributeLocation(const std::string& attributeName)
	{
		GLint ret;
		GL_CALL(ret = glGetAttribLocation(m_ProgramID, attributeName.c_str()));
		return ret;
	}

	GLint GLShaderProgram::GetUniformLocation(const std::string& uniformName)
	{
		if (m_UniformLocations.contains(uniformName))
			return m_UniformLocations[uniformName];

		const GLint newLocation = glGetUniformLocation(m_ProgramID, uniformName.c_str());
		m_UniformLocations[uniformName] = newLocation;
		return newLocation;
	}

	void GLShaderProgram::SetUnifrom4f(const std::string& name, const glm::vec4& vec)
	{
		const auto& location = GetUniformLocation(name);
		GL_CALL(glUniform4f(location, vec.x, vec.y, vec.z, vec.w));
	}

	void GLShaderProgram::SetUnifrom4x4Matrix(const std::string& name, const glm::mat4& matrix)
	{
		const auto& location = GetUniformLocation(name);
		GL_CALL(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix)));
	}

	void GLShaderProgram::Release()
	{
		GL_CALL(glDeleteProgram(m_ProgramID));
	}

	void GLShaderProgram::LinkProgram() const
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
