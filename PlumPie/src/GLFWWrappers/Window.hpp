#ifndef GLFW_WINDOW_WRAPPER_HPP
#define GLFW_WINDOW_WRAPPER_HPP

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

namespace Plum::GLFW
{
		class Window
		{
		public:
			Window(unsigned sizeX = 1280, unsigned sizeY = 960);
			Window(Window& other) = delete;
			Window(Window&& other) noexcept;
			~Window();

			Window& operator=(Window& other) = delete;
			Window& operator=(Window&& other) noexcept;

			const char** GetRequiredExtensions() const;
			bool ShouldClose() const;
			void SetFullscreen();
			void MakeContextCurrent() const;
			void SwapBuffers() const;

			void SetVsync(const bool isEnabled);
			bool IsVsync() const { return m_IsVsyncOn; }

			void Resize(int newWidth, int newHeight);

		private:
			void InitGLFW() const;
			void CreateWindow(unsigned sizeX, unsigned sizeY);

			void SetWindowSizeCallback() const;
			void WindowSizeCallback(int width, int height) const;
			static void StaticWindowSizeCallback(GLFWwindow* window, const int width, const int height);

			void SetKeyCallback() const;
			static void StaticKeyCallback(GLFWwindow* window, const int key, const int scancode, const int action, const int mods);
			void KeyCallback(const int key, const int scancode, const int action, const int mods);

			// data
			GLFWwindow* m_glfwWindowPtr = nullptr;
			GLFWmonitor* m_Monitor = nullptr;
			bool m_IsFullscreen = false;
			bool m_IsVsyncOn = true;
		};
}

#endif