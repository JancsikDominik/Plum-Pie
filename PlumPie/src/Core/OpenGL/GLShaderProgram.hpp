#ifndef PLUM_PROGRAM_OBJECT_HPP
#define PLUM_PROGRAM_OBJECT_HPP

#include <unordered_map>
#include <vector>
#include <glm/fwd.hpp>

#include "GLShader.hpp"
#include "Core/ShaderProgram.hpp"

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