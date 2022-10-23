#include "Mesh.hpp"

const std::vector<Plum::Vertex>& Plum::Mesh::GetVertecies() const
{
	return m_Vertecies;
}

void Plum::Mesh::AddVertex(const Vertex& newVert)
{
	m_Vertecies.push_back(newVert);
}

void Plum::Mesh::AddVertecies(const std::vector<Vertex>& vertecies)
{
	m_Vertecies = vertecies;
}
