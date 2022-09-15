#include "GLFWWrappers/Window.hpp"
#include "plumpie.hpp"

namespace Plum
{
	void PlumPie::Run()
	{
		auto window{ Plum::GLFW::Window(1280, 960, "My Window") };
		window.MakeContextCurrent();

		while (!window.ShouldClose())
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);

			/* Swap front and back buffers */
			window.SwapBuffers();

			/* Poll for and process events */
			glfwPollEvents();
		}
	}

}