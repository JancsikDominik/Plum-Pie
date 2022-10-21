#include "Shader.hpp"

#include <fstream>
#include <string>
#include <iostream>

namespace Plum
{

Shader::Shader(const char* const path, GLenum type)
{
	const std::string& source = LoadSourceFromFile(path);
	const char* const sourceAsCStr = source.c_str(); // doing this in two step to avoid dangling pointers

	CreateShader(type);
	CompileShader(sourceAsCStr);
}

Shader::~Shader()
{
	glDeleteShader(m_ShaderID);
}

GLuint Shader::GetShaderID() const
{
	if(m_ShaderID != 0)
		return m_ShaderID;
	else
		throw std::invalid_argument("shader id can't be 0");
}

GLint Shader::GetUniformLocation(const std::string& name) const
{
	return glGetUniformLocation(m_ShaderID, name.c_str());
}

void Shader::SetUnifrom4f(const std::string& name, glm::vec4 vec) const
{
	const auto& location = GetUniformLocation(name);
	glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
}

std::string Shader::LoadSourceFromFile(const char* const path)
{
	std::ifstream fstream(path);

	if (!fstream.is_open())
		return "";

	std::string source;

	std::string line;
	while (std::getline(fstream, line))
		source += line + "\n";

	fstream.close();

	return source;
}

void Shader::CreateShader(GLenum type)
{
	m_ShaderID = glCreateShader(type);
}

void Shader::CompileShader(const char* const sourceCode)
{
	glShaderSource(m_ShaderID, 1, &sourceCode, 0);
	glCompileShader(m_ShaderID);

	GLint result = GL_FALSE;
	int infoLogLength;

	glGetShaderiv(m_ShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(m_ShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (GL_FALSE == result)
	{
		auto* error = new char[infoLogLength];
		glGetShaderInfoLog(m_ShaderID, infoLogLength, nullptr, error);

		std::cerr << "Error: " << error << std::endl;

		delete[] error;

	}
}

}
