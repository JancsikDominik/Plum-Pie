#ifndef PLUM_SHADER_HPP
#define PLUM_SHADER_HPP

#include "GL/glew.h"
#include <string>

#include "Core/Shader.hpp"

namespace Plum::GL
{
	// raii class for opengl shader
	class GLShader : public Shader
	{
	public:
		GLShader(const char* const path, Type type);
		~GLShader();
		GLShader(const GLShader&) = delete;
		GLShader& operator=(const GLShader&) = delete;

		GLShader(GLShader&& other) noexcept
			: m_ShaderID{ other.m_ShaderID }
		{
			other.m_ShaderID = 0;
		}
		GLShader& operator=(GLShader&& other) noexcept;

		GLuint GetShaderID() const;

	private:
		std::string LoadSourceFromFile(const char* const path) override;
		void CreateShader(Type type) override;
		void CompileShader(const char* const sourceCode) override;
		void Release() override;

		static int GetOpenGLShaderType(Type t);

		GLuint m_ShaderID = 0;
	};

}

#endif