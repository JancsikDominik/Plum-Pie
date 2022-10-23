#ifndef PLUM_MESH_HPP
#define PLUM_MESH_HPP

#include "Vertex.hpp"

#include <vector>

namespace Plum
{
	class Mesh
	{
	public:
		const std::vector<Vertex>& GetVertecies() const;
		void AddVertex(const Vertex& newVert);
		void AddVertecies(const std::vector<Vertex>& vertecies);

	private:
		std::vector<Vertex> m_Vertecies;
		std::vector<glm::vec3> m_Normals;
	};
}

#endif