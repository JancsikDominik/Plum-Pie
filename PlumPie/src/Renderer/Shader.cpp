#include "Shader.hpp"

#include <sstream>
#include <iostream>
#include <fstream>

namespace Plum
{
	Shader::Shader(const std::string& filePath, const plumenum shaderType)
		: mFilePath{ filePath }, mShaderType{ shaderType }, mShaderId{ 0 }
	{
		const std::string& path = std::move(LoadShaderSource(filePath));
		CreateShader(path);
	}

	Shader::~Shader()
	{
		glDeleteShader(mShaderId);
	}

	void Shader::Attach(uint programId) const
	{
		glAttachShader(programId, mShaderId);
	}

	void Shader::Detach(uint programId) const
	{
		glDetachShader(programId, mShaderId);
	}

	void Shader::SetUnifrom4f(const std::string& name, glm::vec4 vec) const
	{
		const auto& location = GetUniformLocation(name);
		glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
	}

	void Shader::CompileShader(const std::string& source) const
	{
		const char* sourcePointer = source.c_str();
		glShaderSource(mShaderId, 1, &sourcePointer, nullptr);
		glCompileShader(mShaderId);

		GLint result = GL_FALSE;
		int infoLogLength;

		glGetShaderiv(mShaderId, GL_COMPILE_STATUS, &result);
		glGetShaderiv(mShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

		if (GL_FALSE == result)
		{
			auto* error = new char[infoLogLength];
			glGetShaderInfoLog(mShaderId, infoLogLength, nullptr, error);

			std::cerr << "Error: " << error << std::endl;

			delete[] error;

		}
	}

	void Shader::CreateShader(const std::string& path)
	{
		mShaderId = glCreateShader(mShaderType);
		const auto& shaderSource = std::move(LoadShaderSource(path));
		CompileShader(shaderSource);
	}

	GLint Shader::GetUniformLocation(const std::string& name) const
	{
		return glGetUniformLocation(mShaderId, name.c_str());
	}

	std::string Shader::LoadShaderSource(const std::string& path) const
	{
		std::ifstream fstream(path);

		if (!fstream.is_open())
			return "";

		std::string shaderCode;

		std::string line;
		while (std::getline(fstream, line))
			shaderCode += line + "\n";

		fstream.close();

		return shaderCode;
	}
}
