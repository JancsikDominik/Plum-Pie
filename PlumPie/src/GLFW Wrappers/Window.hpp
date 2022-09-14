#ifndef GLFW_WINDOW_WRAPPER_HPP
#define GLFW_WINDOW_WRAPPER_HPP

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

namespace Plum::GLFW
{
		class Window
		{
		public:
			Window(const int width, const int height, const char* title);
			Window(Window& other) = delete;
			Window(Window&& other) noexcept;
			~Window();

			Window& operator=(Window& other) = delete;
			Window& operator=(Window&& other) noexcept;

			[[nodiscard]] const char** GetRequiredExtensions() const;
			[[nodiscard]] bool ShouldClose() const;
			void SetFullscreen();
			void MakeContextCurrent() const;
			void SwapBuffers() const;

		private:
			// methods
			void InitGLFW() const;
			void CreateWindow();

			void SetWindowSizeCallback() const;
			void WindowSizeCallback(int width, int height) const;
			static void StaticWindowSizeCallback(GLFWwindow* window, const int width, const int height);

			void SetKeyCallback() const;
			static void StaticKeyCallback(GLFWwindow* window, const int key, const int scancode, const int action, const int mods);
			void KeyCallback(const int key, const int scancode, const int action, const int mods);

			// data
			GLFWwindow* mWindow = nullptr;
			GLFWmonitor* mMonitor = nullptr;
			const char* mTitle;
			int mWidth;
			int mHeight;
			glm::vec2 mPos = glm::vec2(1280, 960);
			bool mFullscreen = false;
		};
}

#endif