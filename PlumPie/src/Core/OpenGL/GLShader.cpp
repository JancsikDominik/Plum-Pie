#include "GLShader.hpp"

#include <fstream>
#include <string>
#include <iostream>
#include "Debugging/Debug.hpp"
#include "Debugging/Console.hpp"

namespace Plum::GL
{

GLShader::GLShader(const char* const path, Type type)
{
	const std::string& source = GLShader::LoadSourceFromFile(path);
	const char* const sourceAsCStr = source.c_str(); // doing this in two step to avoid dangling pointers

	GLShader::CreateShader(type);
	GLShader::CompileShader(sourceAsCStr);
}

GLShader::~GLShader()
{
	GLShader::Release();
}

GLShader& GLShader::operator=(GLShader&& other) noexcept
{
	if (this != &other)
	{
		Release();
		std::swap(m_ShaderID, other.m_ShaderID);
	}
	return *this;
}

GLuint GLShader::GetShaderID() const
{
	if(m_ShaderID != 0)
		return m_ShaderID;
	
	throw std::invalid_argument("shader id can't be 0");
}


std::string GLShader::LoadSourceFromFile(const char* const path)
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

void GLShader::CreateShader(Type type)
{
	GL_CALL(m_ShaderID = glCreateShader(GetOpenGLShaderType(type)));
}

void GLShader::CompileShader(const char* const sourceCode)
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

		Debug::Console::LogError("failed to compile shader: %s", error);

		delete[] error;
	}
}

void GLShader::Release()
{
	GL_CALL(glDeleteShader(m_ShaderID));
}
int GLShader::GetOpenGLShaderType(Type t)
{
	switch(t)
	{
	case Type::Fragment:
		return GL_FRAGMENT_SHADER;
	case Type::Vertex:
		return GL_VERTEX_SHADER;
	case Type::Compute:
		return GL_COMPUTE_SHADER;
	case Type::Geometry:
		return GL_GEOMETRY_SHADER;
	default:
		Debug::Console::LogGLError("unknown shader type");
		return -1;
	}
}

}
