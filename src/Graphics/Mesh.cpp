#include "Mesh.hpp"

const std::vector<Plum::Vertex>& Plum::Mesh::GetVertecies() const
{
	return m_vertecies;
}

const std::vector<int>& Plum::Mesh::GetIndices() const
{
	return m_indices;
}

void Plum::Mesh::AddIndex(int index)
{
	m_indices.push_back(index);
}

void Plum::Mesh::AddIndices(const std::vector<int>& indices)
{
	m_indices.insert(m_indices.end(), indices.begin(), indices.end());
}

void Plum::Mesh::ClearIndices()
{
	m_indices.clear();
}

void Plum::Mesh::AddVertex(const Vertex& newVert)
{
	m_vertecies.push_back(newVert);
}

void Plum::Mesh::AddVertecies(const std::vector<Vertex>& vertecies)
{
	m_vertecies.insert(m_vertecies.end(), vertecies.begin(), vertecies.end());
}

void Plum::Mesh::ClearVertices()
{
	m_vertecies.clear();
}
