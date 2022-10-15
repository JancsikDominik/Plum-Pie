#ifndef PLUMPIE_HPP
#define PLUMPIE_HPP

namespace Plum
{

class AppBase
{
public:
	virtual ~AppBase() = default;
	virtual void Render() = 0;
	virtual void Run() = 0;
};
	
}


#endif