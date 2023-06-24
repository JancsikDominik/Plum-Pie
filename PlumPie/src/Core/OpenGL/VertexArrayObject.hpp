#ifndef PLUM_GL_BUFFER_HPP
#define PLUM_GL_BUFFER_HPP

#include <glew.h>
#include <vector>
#include <Debugging/Debug.hpp>

#include "Formats.hpp"

namespace Plum::GL
{
	enum class BufferType : int
	{
		Array = GL_ARRAY_BUFFER,
		Element = GL_ELEMENT_ARRAY_BUFFER
	};

	enum class DrawType : int 
	{
		Dynamic = GL_DYNAMIC_DRAW,
		Static = GL_STATIC_DRAW,
		Stream = GL_STREAM_DRAW
	};

	template <typename T>
	struct AttributeLayout
	{
		int count = 1;
		uint64_t offset = 0;
		bool normalized = false;
		GLTypes type;
	};

	// raii class for opengl vao
	class VertexArrayObject
	{
	public:
		VertexArrayObject();
		~VertexArrayObject();
		VertexArrayObject(const VertexArrayObject&) = delete;
		VertexArrayObject& operator=(const VertexArrayObject&) = delete;

		VertexArrayObject(VertexArrayObject&& other) noexcept
			: m_vaoID{ other.m_vaoID }
		{
			other.m_vaoID = 0;
		}

		VertexArrayObject& operator=(VertexArrayObject&& other) noexcept;

		void Bind();

		template <typename T>
		void EnableAttribute(uint32_t index, const AttributeLayout<T>& layout) const
		{
			GL_CALL(glEnableVertexAttribArray(index));
			GL_CALL(glVertexAttribPointer(index, layout.count, (int)layout.type, layout.normalized, sizeof(T), reinterpret_cast<const void*>(layout.offset)));
		}

		template <typename T>
		void AttachBuffer(BufferType type, size_t elemCount, const void* data, DrawType mode) const
		{
			GLuint buffer;
			GL_CALL(glGenBuffers(1, &buffer));
			GL_CALL(glBindBuffer((int)type, buffer));
			GL_CALL(glBufferData((int)type, elemCount * sizeof(T), data, (int)mode));
		}

	private:
		void Release();

		GLuint m_vaoID = 0;
	};
}

#endif