#ifndef PLUM_PROGRAM_OBJECT_HPP
#define PLUM_PROGRAM_OBJECT_HPP

#include <unordered_map>
#include <vector>
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLShader.hpp"
#include "Core/ShaderProgram.hpp"
#include "Debugging/Console.hpp"
#include "Debugging/Debug.hpp"


namespace Plum::GL
{

// raii class for opengl shaderprogram
class GLShaderProgram : public ShaderProgram
{
public:
	GLShaderProgram();
	~GLShaderProgram() override;

	GLShaderProgram(const GLShaderProgram&) = delete;
	GLShaderProgram& operator=(const GLShaderProgram&) = delete;

	GLShaderProgram(GLShaderProgram&& other) noexcept
		: m_ProgramID{ other.m_ProgramID }
	{
		other.m_ProgramID = 0;
	}

	GLShaderProgram& operator=(GLShaderProgram&& other) noexcept;

	void AttachShader(const Shader* shader) const override;
	void AttachShaders(const std::vector<Shader*>& shaders) const override;

	void Use() const override;
	void StopUsing() const override;

	GLint GetAttributeLocation(const std::string& attributeName);
	GLint GetUniformLocation(const std::string& uniformName);

	template <typename T>
	void SetUniform(int location, const T& value);

	template <typename T>
	void SetUniform(const std::string& name, const T& value);

	template <typename T>
	void SetUniformMatrix(int location, const T& value, bool transpose);

	template <typename T>
	void SetUniformMatrix(const std::string& name, const T& value, bool transpose);

private:
	void Release();
	void LinkProgram() const;

	std::unordered_map<std::string, GLint>	m_UniformLocations;
	GLuint									m_ProgramID = 0;
};

template<typename T>
inline void GLShaderProgram::SetUniform(int location, const T& value)
{
	Debug::Console::LogError("unsupported uniform type");
}

template<typename T>
inline void GLShaderProgram::SetUniform(const std::string& name, const T& value)
{
	const auto& location = GetUniformLocation(name);
	SetUniform(location, value);
}

template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value>::type
SetUniform(int location, const T& value)
{
	if (std::is_same<T, int>::value || std::is_same<T, unsigned int>::value)
	{
		GL_CALL(glUniform1i(location, value));
	}
	else
	{
		GL_CALL(glUniform1f(location, value));
	}
}

template<>
inline void GLShaderProgram::SetUniform(int location, const glm::vec2& value)
{
	GL_CALL(glUniform2fv(location, 1, glm::value_ptr(value)));
}

template<>
inline void GLShaderProgram::SetUniform(int location, const glm::vec3& value)
{
	GL_CALL(glUniform3fv(location, 1, glm::value_ptr(value)));
}

template<>
inline void GLShaderProgram::SetUniform(int location, const glm::vec4& value)
{
	GL_CALL(glUniform4fv(location, 1, glm::value_ptr(value)));
}

template<>
inline void GLShaderProgram::SetUniform(int location, const glm::ivec2& value)
{
	GL_CALL(glUniform2iv(location, 1, glm::value_ptr(value)));
}

template<>
inline void GLShaderProgram::SetUniform(int location, const glm::ivec3& value)
{
	GL_CALL(glUniform3iv(location, 1, glm::value_ptr(value)));
}

template<>
inline void GLShaderProgram::SetUniform(int location, const glm::ivec4& value)
{
	GL_CALL(glUniform4iv(location, 1, glm::value_ptr(value)));
}

template<>
inline void GLShaderProgram::SetUniform(int location, const glm::uvec2& value)
{
	GL_CALL(glUniform2uiv(location, 1, glm::value_ptr(value)));
}

template<>
inline void GLShaderProgram::SetUniform(int location, const glm::uvec3& value)
{
	GL_CALL(glUniform3uiv(location, 1, glm::value_ptr(value)));
}

template<>
inline void GLShaderProgram::SetUniform(int location, const glm::uvec4& value)
{
	GL_CALL(glUniform4uiv(location, 1, glm::value_ptr(value)));
}

template<typename T>
inline void GLShaderProgram::SetUniformMatrix(int location, const T& value, bool transpose)
{
	Debug::Console::LogError("unsupported uniform type");
}

template<typename T>
inline void GLShaderProgram::SetUniformMatrix(const std::string& name, const T& value, bool transpose)
{
	const auto& location = GetUniformLocation(name);
	SetUniformMatrix(location, value, transpose);
}

template<>
inline void GLShaderProgram::SetUniformMatrix(int location, const glm::mat2& value, bool transpose)
{
	GL_CALL(glUniformMatrix2fv(location, 1, transpose, glm::value_ptr(value)));
}

template<>
inline void GLShaderProgram::SetUniformMatrix(int location, const glm::mat3& value, bool transpose)
{
	GL_CALL(glUniformMatrix3fv(location, 1, transpose, glm::value_ptr(value)));
}

template<>
inline void GLShaderProgram::SetUniformMatrix(int location, const glm::mat4& value, bool transpose)
{
	GL_CALL(glUniformMatrix4fv(location, 1, transpose, glm::value_ptr(value)));
}

template<>
inline void GLShaderProgram::SetUniformMatrix(int location, const glm::mat2x3& value, bool transpose)
{
	GL_CALL(glUniformMatrix2x3fv(location, 1, transpose, glm::value_ptr(value)));
}

template<>
inline void GLShaderProgram::SetUniformMatrix(int location, const glm::mat3x2& value, bool transpose)
{
	GL_CALL(glUniformMatrix3x2fv(location, 1, transpose, glm::value_ptr(value)));
}

template<>
inline void GLShaderProgram::SetUniformMatrix(int location, const glm::mat2x4& value, bool transpose)
{
	GL_CALL(glUniformMatrix2x4fv(location, 1, transpose, glm::value_ptr(value)));
}

template<>
inline void GLShaderProgram::SetUniformMatrix(int location, const glm::mat4x2& value, bool transpose)
{
	GL_CALL(glUniformMatrix4x2fv(location, 1, transpose, glm::value_ptr(value)));
}

template<>
inline void GLShaderProgram::SetUniformMatrix(int location, const glm::mat3x4& value, bool transpose)
{
	GL_CALL(glUniformMatrix3x4fv(location, 1, transpose, glm::value_ptr(value)));
}

template<>
inline void GLShaderProgram::SetUniformMatrix(int location, const glm::mat4x3& value, bool transpose)
{
	GL_CALL(glUniformMatrix4x3fv(location, 1, transpose, glm::value_ptr(value)));
}

}


#endif