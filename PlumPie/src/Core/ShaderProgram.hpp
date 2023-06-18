#ifndef PLUM_PROGRAM_OBJECT_HPP
#define PLUM_PROGRAM_OBJECT_HPP

#include <unordered_map>
#include <vector>
#include <glm/fwd.hpp>

#include "Core/Shader.hpp"

namespace Plum::GL
{

// raii class for opengl shaderprogram
class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();
	ShaderProgram(const ShaderProgram&) = delete;
	ShaderProgram& operator=(const ShaderProgram&) = delete;

	ShaderProgram(ShaderProgram&& other) noexcept
		: m_ProgramID{ other.m_ProgramID }
	{
		other.m_ProgramID = 0;
	}

	ShaderProgram& operator=(ShaderProgram&& other) noexcept;

	void AttachShader(const Shader& shader) const;
	void AttachShaders(const std::vector<Shader*>& shaders) const;

	void Use() const;
	void StopUsing() const;

	GLint GetAttributeLocation(const std::string& attributeName);
	GLint GetUniformLocation(const std::string& uniformName);
	void SetUnifrom4f(const std::string& name, const glm::vec4& vec);
	void SetUnifrom4x4Matrix(const std::string& name, const glm::mat4& matrix);

private:
	void Release();
	void LinkProgram() const;

	std::unordered_map<std::string, GLint>	m_UniformLocations;
	GLuint									m_ProgramID = 0;
};

}


#endif