#ifndef GLFW_WINDOW_WRAPPER_HPP
#define GLFW_WINDOW_WRAPPER_HPP

#include <string>
#include <vector>

#define GLFW_INCLUDE_VULKAN
#include <glfw/glfw3.h>
#include <glm/vec2.hpp>
#include <vulkan/vulkan.hpp>

#include "Keyboard.hpp"
#include "Window.hpp"

namespace Plum::GLFW
{
		// raii class for glfw window
		class Window : public App::Window
		{
		public:
			Window(const std::string& name, unsigned sizeX = 1280, unsigned sizeY = 960);
			Window(Window& other) = delete;
			Window(Window&& other) noexcept;
			virtual ~Window() override;

			Window& operator=(Window& other) = delete;
			Window& operator=(Window&& other) noexcept;

			virtual void SetFullscreen() override;
			virtual void SetVsync(const bool isEnabled) override;
			virtual void Resize(int newWidth, int newHeight) override;

			void PollEvents() const;

			[[nodiscard]] virtual std::vector<const char*> GetRequiredExtensions() const override;
			[[nodiscard]] virtual bool ShouldClose() const override;
			[[nodiscard]] virtual bool IsVsync() const override;
			[[nodiscard]] virtual double GetTime() const override;
			[[nodiscard]] virtual const std::string& GetWindowTitle() const override;
			[[nodiscard]] virtual vk::SurfaceKHR CreateWindowSurface(const vk::Instance& instance) const override;
			[[nodiscard]] virtual Size GetSize() const override;

		private:
			void SetCallbacks();
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