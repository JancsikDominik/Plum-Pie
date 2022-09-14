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

	private:
		std::vector<Vertex> mVertecies;
	};
}

#endif