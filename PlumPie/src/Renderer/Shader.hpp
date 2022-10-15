#ifndef PLUM_SHADER_HPP
#define PLUM_SHADER_HPP

#include <string>
#include <glm/vec4.hpp>

#include "Types.hpp"

namespace Plum
{
	class Shader
	{
	public:
		Shader(const std::string& filePath, plumenum shaderType);
		~Shader();
		Shader(Shader& other) = delete;
		Shader& operator=(Shader& other) = delete;
		Shader(Shader&& other) noexcept { mShaderId = other.mShaderId; other.mShaderId = 0; mShaderType = other.mShaderType; }
		Shader& operator=(Shader&& other) noexcept { mShaderId = other.mShaderId; other.mShaderId = 0; mShaderType = other.mShaderType; return *this; }

		void Attach(uint programId) const;
		void Detach(uint programId) const;


		void SetUnifrom4f(const std::string& name, glm::vec4 vec) const;

		static constexpr GLuint invalidShaderId = 0;

	private:
		void CompileShader(const std::string& source) const;
		void CreateShader(const std::string& path);
		GLint GetUniformLocation(const std::string& name) const;
		std::string LoadShaderSource(const std::string& path) const;

		std::string mFilePath;
		plumenum mShaderType;
		uint mShaderId;
	};
}

#endif