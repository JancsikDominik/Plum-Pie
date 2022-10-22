#ifndef PLUM_PROGRAM_OBJECT_HPP
#define PLUM_PROGRAM_OBJECT_HPP

#include <unordered_map>
#include <vector>
#include "Core/Shader.hpp"

namespace Plum::GL
{

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	void AttachShader(const Shader& shader) const;
	void AttachShaders(const std::vector<Shader>& shaders) const;

	void Use() const;
	void StopUsing() const;

	GLint GetAttributeLocation(const std::string& attributeName);

private:
	std::unordered_map<std::string, GLint>	m_UniformLocations;
	GLuint									m_ProgramID = 0;
};
	
}


#endif