#include "VertexArrayObject.hpp"
#include <GL/glew.h>

namespace Plum
{

	VertexArrayObject::VertexArrayObject()
	{
		// when we create a VertexArrayObject we create an id for it
		glGenVertexArrays(1, &mVBOId);
	}

	VertexArrayObject::~VertexArrayObject()
	{
		// cleaning up unused VertexArrayObject
		glDeleteBuffers(1, &mVBOId);
	}

	void VertexArrayObject::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, mVBOId);
	}

	void VertexArrayObject::Release() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
