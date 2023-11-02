#pragma once

#include "Core/Renderer.hpp"

namespace Plum::VK
{

	class Renderer : public Plum::Renderer
	{
	public:
		virtual ~Renderer() = default;

		virtual void SetViewport(int x, int y, int width, int height) override;
		virtual void SetClearColor(Color clearColor) override;
		virtual void SetCullFace(bool enable) override;
		virtual void SetDepthTest(bool enable) override;
		virtual void SetProgram(ShaderProgram& program) override;
		virtual void SetUniformData(const std::string& name, const std::any& value) override;


		virtual void Clear() override;
		virtual void Render() override;
	};

}