#include "VAO.hpp"
#include <GL/glew.h>

namespace Plum
{

	VAO::VAO()
	{
		glGenVertexArrays(1, &mVAOId);
	}

	void VAO::Bind() const
	{
		glBindVertexArray(mVAOId);
	}

	void VAO::Release() const
	{
		glBindVertexArray(0);
	}
}
