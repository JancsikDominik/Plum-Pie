#include "OpenGLRenderer.hpp"

#include <Debugging/Debug.hpp>
#include <glew.h>

namespace Plum::GL
{
	OpenGLRenderer::OpenGLRenderer()
	{
		m_IsCullfaceEnabled = true;
		m_IsDepthTestEnabled = true;

		OpenGLRenderer::SetCullFace(m_IsCullfaceEnabled);
		OpenGLRenderer::SetDepthTest(m_IsDepthTestEnabled);
	}

	void OpenGLRenderer::SetClearColor(Color clearColor)
	{
		m_ClearColor = clearColor;
		GL_CALL(glClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a));
	}

	void OpenGLRenderer::SetCullFace(bool enable)
	{
		m_IsCullfaceEnabled = enable;
		m_IsCullfaceEnabled ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
	}

	void OpenGLRenderer::SetDepthTest(bool enable)
	{
		m_IsDepthTestEnabled = enable;
		m_IsDepthTestEnabled ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
	}

	void OpenGLRenderer::SetProgram(ShaderProgram& program)
	{
		m_Program = dynamic_cast<GLShaderProgram*>(&program);
		m_Program->Use();
	}

	void OpenGLRenderer::StopUsingCurrentProgram()
	{
		if(m_Program != nullptr)
		{
			m_Program->StopUsing();
			m_Program = nullptr;
		}
	}

	void OpenGLRenderer::SetViewport(int x, int y, int width, int height)
	{
		GL_CALL(glViewport(x, y, width, height));
	}

	void OpenGLRenderer::SetUniformData(const std::string& name, const std::any& value)
	{
		m_UniformData[name] = value;
	}

	void OpenGLRenderer::Clear()
	{
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

	void OpenGLRenderer::Render()
	{
		GL_CALL(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0));
	}
}
