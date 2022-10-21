#include "VertexArrayObject.hpp"

namespace Plum::GL
{
	VertexArrayObject::VertexArrayObject()
	{
		glGenVertexArrays(1, &m_vaoID);
	}

	VertexArrayObject::~VertexArrayObject()
	{
		glDeleteVertexArrays(1, &m_vaoID);
	}

	void VertexArrayObject::Bind()
	{
		glBindVertexArray(m_vaoID);
	}

	void VertexArrayObject::AttachBuffer(const BufferType type, const size_t size, const void* data, const DrawType mode)
	{
		GLuint buffer;
		glGenBuffers(1, &buffer);

		glBindBuffer(type, buffer);
		glBufferData(type, size, data, mode);
	}

	void VertexArrayObject::EnableAttribute(unsigned int index, int size, unsigned int offset, const void* data)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, offset, data);
	}

}

