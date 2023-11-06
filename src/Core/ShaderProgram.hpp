#ifndef PLUMPIE_SHADER_PROGRAM_HPP
#define PLUMPIE_SHADER_PROGRAM_HPP

#include <vector>

#include "Shader.hpp"

namespace Plum
{
	class ShaderProgram
	{
	public:
		virtual ~ShaderProgram() = default;

		virtual void AttachShader(const Shader* shader) const = 0;
		virtual void AttachShaders(const std::vector<Shader*>& shaders) const = 0;

		virtual void Use() const = 0;
		virtual void StopUsing() const = 0;
	};
}

#endif