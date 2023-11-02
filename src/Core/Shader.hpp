#pragma once

#include <string>

namespace Plum
{
	class Shader
	{
	public:
		enum class Type
		{
			Vertex,
			Fragment,
			Geometry,
			Compute,
			Tessellation
		};

		virtual ~Shader() = default;

	protected:
		virtual std::string LoadSourceFromFile(const char* const path) = 0;
		virtual void CreateShader(Type type) = 0;
		virtual void CompileShader(const char* const sourceCode) = 0;
		virtual void Release() = 0;
	};
}
