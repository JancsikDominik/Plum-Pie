#include "Renderer.hpp"

#include <Debugging/Debug.hpp>

namespace Plum
{
	Renderer::Renderer()
	{
		m_IsCullfaceEnabled = true;
		m_IsDepthTestEnabled = true;

		SetCullFace(m_IsCullfaceEnabled);
		SetDepthTest(m_IsDepthTestEnabled);
	}

	void Renderer::SetClearColor(Color clearColor)
	{
		m_ClearColor = clearColor;
		GL_CALL(glClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a));
	}

	void Renderer::SetCullFace(bool enable)
	{
		m_IsCullfaceEnabled = enable;
		m_IsCullfaceEnabled ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
	}

	void Renderer::SetDepthTest(bool enable)
	{
		m_IsDepthTestEnabled = enable;
		m_IsDepthTestEnabled ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
	}

	void Renderer::UseProgram(GL::ShaderProgram& program)
	{

		m_Program = &program;
		m_Program->Use();
	}

	void Renderer::StopUsingCurrentProgram()
	{
		if(m_Program != nullptr)
		{
			m_Program->StopUsing();
			m_Program = nullptr;
		}
	}

	void Renderer::Render()
	{
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		GL_CALL(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0));
	}
}
