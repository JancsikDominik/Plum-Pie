#ifndef PLUM_SHADER_HPP
#define PLUM_SHADER_HPP

#include "GL/glew.h"
#include "glm/vec4.hpp"
#include <string>

namespace Plum
{

	class Shader
	{
	public:
		Shader(const char* const path, GLenum type);
		~Shader();

		GLuint GetShaderID() const;
		GLint GetUniformLocation(const std::string& name) const;
		void SetUnifrom4f(const std::string& name, glm::vec4 vec) const;

	private:
		std::string LoadSourceFromFile(const char* const path);
		void CreateShader(GLenum type);
		void CompileShader(const char* const sourceCode);

		GLuint m_ShaderID = 0;
	};

}

#endif