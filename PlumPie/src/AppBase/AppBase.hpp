#ifndef PLUMPIE_HPP
#define PLUMPIE_HPP

namespace Plum::GLFW { class Window; }

namespace Plum
{

class AppBase
{
public:
	AppBase();
	virtual ~AppBase();
	virtual void Render() = 0;
	virtual void Run() = 0;
	virtual void StartUp() = 0;
	virtual void Update() = 0;

protected:
	void InitGlew() const;

	GLFW::Window* m_Window;
};
	
}


#endif