#include "Mesh.hpp"

const std::vector<Plum::Vertex>& Plum::Mesh::GetVertecies() const
{
	return mVertecies;
}

void Plum::Mesh::AddVertex(const Vertex& newVert)
{
	mVertecies.push_back(newVert);
}

void Plum::Mesh::AddVertecies(const std::vector<Vertex>& vertecies)
{
	mVertecies = vertecies;
}
