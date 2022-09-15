#include "VBO.hpp"
#include <GL/glew.h>

namespace Plum
{

	VBO::VBO()
	{
		// when we create a VBO we create an id for it
		glGenVertexArrays(1, &mVBOId);
	}

	VBO::~VBO()
	{
		// cleaning up unused VBO
		glDeleteBuffers(1, &mVBOId);
	}

	void VBO::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, mVBOId);
	}

	void VBO::Release() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
