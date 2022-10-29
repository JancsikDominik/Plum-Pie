#ifndef PLUM_SHADER_HPP
#define PLUM_SHADER_HPP

#include "GL/glew.h"
#include "glm/vec4.hpp"
#include <string>

namespace Plum::GL
{
	// raii class for opengl shader
	class Shader
	{
	public:
		Shader(const char* const path, GLenum type);
		~Shader();
		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;

		Shader(Shader&& other) noexcept
			: m_ShaderID{ other.m_ShaderID }
		{
			other.m_ShaderID = 0;
		}

		Shader& operator=(Shader&& other) noexcept;

		[[nodiscard]] GLuint GetShaderID() const;
		[[nodiscard]] int GetUniformLocation(const std::string& name) const;
		void SetUnifrom4f(const std::string& name, glm::vec4 vec) const;

	private:
		std::string LoadSourceFromFile(const char* const path);
		void CreateShader(GLenum type);
		void CompileShader(const char* const sourceCode);
		void Release();

		GLuint m_ShaderID = 0;
	};

}

#endif