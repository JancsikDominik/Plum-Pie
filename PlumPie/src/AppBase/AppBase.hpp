#ifndef PLUMPIE_HPP
#define PLUMPIE_HPP

#include "Debugging/Console.hpp"

namespace Plum::GLFW { class Window; }
namespace Plum { class Renderer; }

namespace Plum
{

class AppBase
{
public:
	enum class BackendApi
	{
		OpenGL,
		Vulkan // MAYBE? or DirectX12
	};

	AppBase();
	virtual ~AppBase();

	/**
	 * \brief Runs the application
	 */
	void Run();

protected:

	/**
	 * \brief Have to call this to specify which backend api should be used, if we don't specify the renderer will be a nullptr
	 * \param api The backend api to be used
	 */
	void SetBackendApi(BackendApi api);

	/**
	 * \brief Will be called before the main loop, used to set things up
	 */
	virtual void StartUp() = 0;

	/**
	 * \brief Will be called before every frame render, should be used to, well, update things
	 * \param currTimeStamp current time stamp in seconds
	 */
	virtual void Update(double currTimeStamp) = 0;

	Renderer* m_renderer;
	GLFW::Window* m_window;

private:
	void InitGlew() const;

	Debug::Console m_console;
};
	
}


#endif