#ifndef PLUM_VERTEX_HPP
#define PLUM_VERTEX_HPP

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace Plum
{
	// rgba: 0-1
	struct Color
	{
		Color(float r = 0, float g = 0, float b = 0, float a = 1.f)
			: r{ r }, g{ g }, b{ b }, a{ a }
		{
		}

		// TODO: to HSL
		// TODO: to rgba (0-255)

		float r, g, b, a;
	};

	struct Vertex
	{
		Vertex(glm::vec3 pos, glm::vec3 normal = {0, 1, 0}, glm::vec2 uv = {0, 0})
			: pos {pos}, normal {normal}, uv {uv}
		{
		}

		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 uv;
	};
	
}


#endif
