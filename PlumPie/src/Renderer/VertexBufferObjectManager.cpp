#include "VertexBufferObjectManager.hpp"
#include <GL/glew.h>

namespace Plum
{

	VertexBufferObjectManager::VertexBufferObjectManager()
	{
		mVAOId = 0;
		glGenVertexArrays(1, &mVAOId);
	}

	void VertexBufferObjectManager::Bind() const
	{
		glBindVertexArray(mVAOId);
	}

	void VertexBufferObjectManager::Release() const
	{
		glBindVertexArray(0);
	}
}
