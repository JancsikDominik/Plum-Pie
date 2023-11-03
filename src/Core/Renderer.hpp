#ifndef PLUMPIE_RENDERER_HPP
#define PLUMPIE_RENDERER_HPP

#include <any>
#include <unordered_map>

#include "ShaderProgram.hpp"
#include "Graphics/Vertex.hpp"

namespace Plum
{
	class Renderer
	{
	public:
		virtual ~Renderer() = default;

		virtual void SetViewport(int x, int y, int width, int height) = 0;
		virtual void SetClearColor(Color clearColor) = 0;
		virtual void SetCullFace(bool enable) = 0;
		virtual void SetDepthTest(bool enable) = 0;
		virtual void SetProgram(ShaderProgram& program) = 0;
		virtual void SetUniformData(const std::string& name, const std::any& value) = 0;

		// TODO: Textures
		// virtual void SetTexture(Texture& texture) = 0;

		virtual void Clear() = 0;
		virtual void Render() = 0;

	protected:
		std::unordered_map<std::string, std::any> m_uniformData;
	};
}

#endif