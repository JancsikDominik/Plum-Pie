#ifndef PLUM_VBO_HPP
#define PLUM_VBO_HPP

#include "Types.hpp"
#include <vector>

namespace Plum
{
	enum DrawType
	{
		STREAM = GL_STREAM_DRAW,
		STATIC = GL_STATIC_DRAW,
		DYNAMIC = GL_DYNAMIC_DRAW
	};

	enum BindingTarget
	{
		ARRAY_BUFFER = GL_ARRAY_BUFFER,
		ATOMIC_COUNTER_BUFFER = GL_ATOMIC_COUNTER_BUFFER,
		COPY_AND_READ_BUFFER = GL_COPY_READ_BUFFER,
		COPY_AND_WRITE_BUFFER = GL_COPY_WRITE_BUFFER,
		DISPACH_INDIRECT_BUFFER = GL_DISPATCH_INDIRECT_BUFFER,
		DRAW_INDIRECT_BUFFER = GL_DRAW_INDIRECT_BUFFER,
		ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER,
		PIXEL_PACK_BUFFER = GL_PIXEL_PACK_BUFFER,
		PIXEL_UNPACK_BUFFER = GL_PIXEL_UNPACK_BUFFER,
		QUEARY_BUFFER = GL_QUERY_BUFFER,
		SHADER_STORAGE_BUFFER = GL_SHADER_STORAGE_BUFFER,
		TEXTURE_BUFFER = GL_TEXTURE_BUFFER,
		TRANSFORM_FEEDBACK_BUFFER = GL_TRANSFORM_FEEDBACK_BUFFER,
		UNIFORM_BUFFER = GL_UNIFORM_BUFFER
	};

	class VBO
	{
	public:
		VBO();
		~VBO();
		VBO(VBO& other) = delete;
		VBO& operator=(VBO& other) = delete;
		inline VBO(VBO&& other) noexcept { mVBOId = other.mVBOId; other.mVBOId = 0; }
		inline VBO& operator=(VBO&& other) noexcept { mVBOId = other.mVBOId; other.mVBOId = 0; return *this; }

		void Bind() const;
		void Release() const;

		template <class T>
		void SetUpAttributeAtIndex(ushort i, ushort componentCount, GLenum type, bool normalized, std::vector<T> vec, int index);

		template<class T>
		void LoadBufferData(BindingTarget target, std::vector<T> vertecies, DrawType type) const;

	private:
		ushort mVBOId = 0;
	};

	template <class T>
	void VBO::LoadBufferData(BindingTarget target, std::vector<T> vertecies, DrawType type) const
	{
		glBufferData(target, vertecies.size() * sizeof(Vertex), vertecies.data(), type);
	}

	template <class T>
	void VBO::SetUpAttributeAtIndex(ushort i, ushort componentCount, GLenum type, bool normalized, std::vector<T> vec, int index)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, componentCount, type, normalized, sizeof(T), &vec[index]);
	}
}


#endif
