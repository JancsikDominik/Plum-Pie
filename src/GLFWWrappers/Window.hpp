#ifndef GLFW_WINDOW_WRAPPER_HPP
#define GLFW_WINDOW_WRAPPER_HPP

#include <string>
#include <vector>

#define GLFW_INCLUDE_VULKAN
#include <glfw/glfw3.h>
#include <glm/vec2.hpp>
#include <vulkan/vulkan.hpp>

#include "Keyboard.hpp"

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

			void SetFullscreen();
			void SetCurrentContext(bool thisThread) const;
			void SwapBuffers() const;
			void SetVsync(const bool isEnabled);
			void Resize(int newWidth, int newHeight);

			void PollEvents() const;

			[[nodiscard]] std::vector<const char*> GetRequiredExtensions() const;
			[[nodiscard]] bool ShouldClose() const;
			[[nodiscard]] bool IsVsync() const;
			[[nodiscard]] double GetTime() const;
			[[nodiscard]] const std::string& GetWindowTitle() const;
			[[nodiscard]] vk::SurfaceKHR CreateWindowSurface(const vk::Instance& instance) const;

		private:
			void SetCallbacks();

			void InitGLFW() const;
			void CreateWindow(unsigned sizeX, unsigned sizeY, const std::string& name);

			void SetWindowSizeCallback() const;
			void WindowSizeCallback(int width, int height) const;
			static void StaticWindowSizeCallback(GLFWwindow* window, int width, int height);

			void SetKeyCallback() const;
			static void StaticKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
			void KeyCallback(Keyboard::Key key, int scancode, Keyboard::Action action, uint32_t mods);

			void SetCursorPosCallback() const;
			void CursorPosCallback(double xpos, double ypos) const;
			static void StaticCursorPosCallback(GLFWwindow* window, double xpos, double ypos);

			void SetMouseButtonCallback() const;
			void MouseButtonCallback(int button, int action, int mods) const;
			static void StaticMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

			void SetMouseScrollCallback() const;
			void MouseScrollCallback(double xoffset, double yoffset) const;
			static void StaticMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

			// data
			GLFWwindow* m_glfwWindowPtr = nullptr;
			GLFWmonitor* m_monitor = nullptr;
			bool m_isFullscreen = false;
			bool m_isVsyncOn = true;
			std::string m_windowTitle;
		};
}

#endif