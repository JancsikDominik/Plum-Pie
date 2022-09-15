#ifndef PLUM_VAO_HPP
#define PLUM_VAO_HPP

#include "Types.hpp"

namespace Plum
{
	class VAO
	{
	public:
		VAO();
		VAO(VAO& other) = delete;
		VAO& operator=(VAO& other) = delete;
		inline VAO(VAO&& other) noexcept { mVAOId = other.mVAOId; other.mVAOId = 0; }
		inline VAO& operator=(VAO&& other) noexcept { mVAOId = other.mVAOId; other.mVAOId = 0; return *this; }

		void Bind() const;
		void Release() const;

	private:
		ushort mVAOId = 0;
	};
}

#endif