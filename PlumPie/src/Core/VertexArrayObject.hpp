#ifndef PLUM_GL_BUFFER_HPP
#define PLUM_GL_BUFFER_HPP

#include <GL/glew.h>
#include <vector>
#include <Debugging/Debug.hpp>

namespace Plum::GL
{
	enum BufferType : int
	{
		ARRAY = GL_ARRAY_BUFFER,
		ELEMENT = GL_ELEMENT_ARRAY_BUFFER
	};

	enum DrawType : int 
	{
		DYNAMIC = GL_DYNAMIC_DRAW,
		STATIC = GL_STATIC_DRAW,
		STREAM = GL_STREAM_DRAW
	};

	// raii class for opengl vao
	class VertexArrayObject
	{
	public:
		VertexArrayObject();
		~VertexArrayObject();
		VertexArrayObject(const VertexArrayObject&) = delete;
		VertexArrayObject& operator=(const VertexArrayObject&) = delete;

		VertexArrayObject(VertexArrayObject&& other) noexcept :
			m_vaoID{ other.m_vaoID }
		{
			other.m_vaoID = 0;
		}

		VertexArrayObject& operator=(VertexArrayObject&& other) noexcept;

		void Bind();
		void EnableAttribute(unsigned int index, int size, unsigned int offset, const void* data);


		template <typename T>
		void AttachBuffer(BufferType type, size_t elemCount, const void* data, DrawType mode)
		{
			GLuint buffer;
			GL_CALL(glGenBuffers(1, &buffer));
			GL_CALL(glBindBuffer(type, buffer));
			GL_CALL(glBufferData(type, elemCount * sizeof(T), data, mode));
		}

	private:
		void Release();

		GLuint m_vaoID = 0;
	};
}

#endif