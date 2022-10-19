#ifndef PLUM_PROGRAM_OBJECT_HPP
#define PLUM_PROGRAM_OBJECT_HPP

#include <unordered_map>
#include <vector>

#include "Types.hpp"
#include "Shader.hpp"

namespace Plum
{

class Program
{
public:
	Program();
	~Program();

	void AttachShader(const Shader& shader) const;
	void AttachShaders(const std::vector<Shader>& shaders) const;

	void Use() const;
	void StopUsing() const;

	// TODO: find a better way to make a ShaderProgram
	uint GetProgramID() const { return m_ProgramID; }

private:
	std::unordered_map<std::string, GLint>	m_UniformLocations;
	uint									m_ProgramID = 0;
};
	
}


#endif