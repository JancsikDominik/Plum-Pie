#pragma once
#include <vector>

#include "Shader.hpp"

namespace Plum
{
	class ShaderProgram
	{
	public:
		virtual ~ShaderProgram() = default;

		virtual void AttachShader(const Shader* shader) const;
		virtual void AttachShaders(const std::vector<Shader*>& shaders) const;

		virtual void Use() const;
		virtual void StopUsing() const;
	};
}

