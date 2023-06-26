#ifndef PLUM_MESH_HPP
#define PLUM_MESH_HPP

#include <vector>

#include "Vertex.hpp"

namespace Plum
{
	class Mesh
	{
	public:
		[[nodiscard]] const std::vector<Vertex>& GetVertecies() const;
		[[nodiscard]] const std::vector<int>& GetIndices() const;
		void AddVertex(const Vertex& newVert);
		void AddVertecies(const std::vector<Vertex>& vertecies);

		void AddIndex(int index);
		void AddIndices(const std::vector<int>& indices);

		void ClearVertices();
		void ClearIndices();

		// TODO: LoadFromFile(std::filesystem::path) -- support only .obj for now

	private:
		std::vector<Vertex> m_vertecies;
		std::vector<int>	m_indices;
	};
}

#endif