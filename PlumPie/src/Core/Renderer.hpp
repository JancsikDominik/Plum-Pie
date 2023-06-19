#pragma once
#include "Graphics/Vertex.hpp"

namespace Plum
{
	class Renderer
	{
	public:
		virtual ~Renderer() = default;

		virtual void SetClearColor(Color clearColor) = 0;
		virtual void SetCullFace(bool enable) = 0;
		virtual void SetDepthTest(bool enable) = 0;
		virtual void UseProgram(/*ShaderProgram& program*/) = 0;
		virtual void StopUsingCurrentProgram() = 0;
		virtual void Render() = 0;

	private:
		// GL::ShaderProgram* m_Program = nullptr;
		Color m_ClearColor;
		bool m_IsCullfaceEnabled;
		bool m_IsDepthTestEnabled;
	};
}
