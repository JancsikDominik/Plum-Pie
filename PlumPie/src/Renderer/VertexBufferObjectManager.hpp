#ifndef PLUM_VAO_HPP
#define PLUM_VAO_HPP

#include "Types.hpp"

namespace Plum
{

	class VertexBufferObjectManager
	{
	public:
		VertexBufferObjectManager();
		VertexBufferObjectManager(VertexBufferObjectManager& other) = delete;
		VertexBufferObjectManager& operator=(VertexBufferObjectManager& other) = delete;
		inline VertexBufferObjectManager(VertexBufferObjectManager&& other) noexcept { mVAOId = other.mVAOId; other.mVAOId = 0; }
		inline VertexBufferObjectManager& operator=(VertexBufferObjectManager&& other) noexcept { mVAOId = other.mVAOId; other.mVAOId = 0; return *this; }

		void Bind() const;
		void Release() const;

	private:
		uint mVAOId;
	};

}

#endif