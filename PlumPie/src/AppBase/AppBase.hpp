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
	void Run();

protected:
	virtual void Render() = 0;
	virtual void StartUp() = 0;
	virtual void Update() = 0;

	GLFW::Window* m_Window;
private:
	void InitGlew() const;
};
	
}


#endif