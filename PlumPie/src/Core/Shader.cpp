#include "Shader.hpp"

#include <fstream>
#include <string>
#include <iostream>
#include "Debugging/Debug.hpp"
#include "Debugging/Console.hpp"

namespace Plum::GL
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
	Release();
}

Shader& Shader::operator=(Shader&& other) noexcept
{
	if (this != &other)
	{
		Release();
		std::swap(m_ShaderID, other.m_ShaderID);
	}
	return *this;
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
	GL_CALL(glUniform4f(location, vec.x, vec.y, vec.z, vec.w));
}

std::string Shader::LoadSourceFromFile(const char* const path)
{
	std::ifstream fstream(path);

	if (!fstream.is_open())
	{
		Debug::Console::LogError("failed to open file %s", path);
		return "";
	}

	std::string source;

	std::string line;
	while (std::getline(fstream, line))
		source += line + "\n";

	fstream.close();

	return source;
}

void Shader::CreateShader(GLenum type)
{
	GL_CALL(m_ShaderID = glCreateShader(type));
}

void Shader::CompileShader(const char* const sourceCode)
{
	GL_CALL(glShaderSource(m_ShaderID, 1, &sourceCode, 0));
	GL_CALL(glCompileShader(m_ShaderID));

	GLint result = GL_FALSE;
	int infoLogLength;

	// geting error message
	GL_CALL(glGetShaderiv(m_ShaderID, GL_COMPILE_STATUS, &result));
	GL_CALL(glGetShaderiv(m_ShaderID, GL_INFO_LOG_LENGTH, &infoLogLength));

	if (GL_FALSE == result)
	{
		// using raw pointer so we can pass it as an argument
		char* error = new char[infoLogLength];
		GL_CALL(glGetShaderInfoLog(m_ShaderID, infoLogLength, nullptr, error));

		std::cerr << "Error: " << error << std::endl;

		delete[] error;

	}
}

void Shader::Release()
{
	GL_CALL(glDeleteShader(m_ShaderID));
}
}
