#ifndef GLFW_WINDOW_WRAPPER_HPP
#define GLFW_WINDOW_WRAPPER_HPP

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <string>

namespace Plum::GLFW
{
		// raii class for glfw window
		class Window
		{
		public:
			Window(const std::string& name, unsigned sizeX = 1280, unsigned sizeY = 960);
			Window(Window& other) = delete;
			Window(Window&& other) noexcept;
			~Window();

			Window& operator=(Window& other) = delete;
			Window& operator=(Window&& other) noexcept;

			[[nodiscard]] const char** GetRequiredExtensions() const;
			[[nodiscard]] bool ShouldClose() const;
			void SetFullscreen();
			void SwapBuffers() const;

			void SetVsync(const bool isEnabled);
			[[nodiscard]] bool IsVsync() const { return m_isVsyncOn; }

			void Resize(int newWidth, int newHeight);

			void SetCurrentContext(bool thisThread) const;

			void PollEvents() const;
			[[nodiscard]] double GetTime() const;

		private:
			void InitGLFW() const;
			void CreateWindow(unsigned sizeX, unsigned sizeY, const std::string& name);

			void SetWindowSizeCallback() const;
			void WindowSizeCallback(int width, int height) const;
			static void StaticWindowSizeCallback(GLFWwindow* window, const int width, const int height);

			void SetKeyCallback() const;
			static void StaticKeyCallback(GLFWwindow* window, const int key, const int scancode, const int action, const int mods);
			void KeyCallback(const int key, const int scancode, const int action, const int mods);

			// data
			GLFWwindow* m_glfwWindowPtr = nullptr;
			GLFWmonitor* m_monitor = nullptr;
			bool m_isFullscreen = false;
			bool m_isVsyncOn = true;
		};
}

#endif