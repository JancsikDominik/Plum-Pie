#ifndef PLUM_VERTEX_HPP
#define PLUM_VERTEX_HPP

#include <glm/vec3.hpp>

namespace Plum
{
	struct Color
	{
		Color(float r = 0, float g = 0, float b = 0, float a = 1.f)
			: r{ r }, g{ g }, b{ b }, a{ a }
		{
		}

		float r, g, b, a;
	};

	struct Vertex
	{
		Vertex(glm::vec3 pos, Color color)
			: pos{ pos }, color{ color }
		{
		}

		Vertex(glm::vec3 pos)
			:pos{ pos }, color {}
		{
		}

		Vertex()
			:pos{}, color{}
		{
		}

		glm::vec3 pos;
		Color color;
	};
	
}


#endif
