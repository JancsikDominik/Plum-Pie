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

	void AttachShader(Shader* shader) const;
	void AttachShaders(const std::vector<Shader*>& shaders) const;

	void Use() const;
	void StopUsing() const;

private:
	std::unordered_map<std::string, GLint>	mUniformLocations;
	uint									mProgramId = 0;
};
	
}


#endif