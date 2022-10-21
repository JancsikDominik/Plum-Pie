#ifndef PLUM_GL_BUFFER_HPP
#define PLUM_GL_BUFFER_HPP

#include <GL/glew.h>

namespace Plum::GL
{
	enum BufferType : int
	{
		ARRAY = GL_ARRAY_BUFFER,
		ELEMENT = GL_ELEMENT_ARRAY_BUFFER,
		INVALID = 0
	};

	enum DrawType : int 
	{
		DYNAMIC = GL_DYNAMIC_DRAW,
		STATIC = GL_STATIC_DRAW,
		STREAM = GL_STREAM_DRAW
	};

	class VertexArrayObject
	{
	public:
		VertexArrayObject();
		~VertexArrayObject();

		void Bind();
		void AttachBuffer(const BufferType type, const size_t size, const void* data, const DrawType mode);
		void EnableAttribute(unsigned int index, int size, unsigned int offset, const void* data);

	private:
		GLuint m_vaoID;
	};
}

#endif