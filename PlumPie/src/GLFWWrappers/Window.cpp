#include "Window.hpp"
#include <stdexcept>
#include <string>

namespace Plum::GLFW
{
		Window::Window(unsigned sizeX, unsigned sizeY)
		{
			InitGLFW();
			CreateWindow(sizeX, sizeY);
			SetVsync(true);
			glfwMakeContextCurrent(m_glfwWindowPtr);
		}

		Window::~Window()
		{
			glfwDestroyWindow(m_glfwWindowPtr);
			glfwTerminate();
		}

		Window::Window(Window&& other) noexcept
		{
			this->m_glfwWindowPtr = other.m_glfwWindowPtr;
			this->m_Monitor = other.m_Monitor;
			this->m_IsFullscreen = other.m_IsFullscreen;

			other.m_glfwWindowPtr = nullptr;
			other.m_Monitor = nullptr;
		}

		Window& Window::operator=(Window&& other) noexcept
		{
			this->m_glfwWindowPtr = other.m_glfwWindowPtr;
			this->m_Monitor = other.m_Monitor;
			this->m_IsFullscreen = other.m_IsFullscreen;

			other.m_glfwWindowPtr = nullptr;
			other.m_Monitor = nullptr;
			return *this;
		}

		const char** Window::GetRequiredExtensions() const
		{
			uint32_t count;
			const char** extensions = glfwGetRequiredInstanceExtensions(&count);
			return extensions;
		}

		void Window::SetFullscreen()
		{
			if (!m_IsFullscreen) 
			{
				const GLFWvidmode* vidMode = glfwGetVideoMode(m_Monitor);
				int x, y;
				glfwGetWindowPos(m_glfwWindowPtr, &x, &y);

				glfwSetWindowMonitor(m_glfwWindowPtr, m_Monitor, 0, 0, vidMode->width, vidMode->height, vidMode->refreshRate);
				glfwSetWindowSize(m_glfwWindowPtr, vidMode->width, vidMode->height);
				m_IsFullscreen = !m_IsFullscreen;
			}
			else 
			{
				//glfwSetWindowMonitor(m_glfwWindowPtr, nullptr, static_cast<int>(mPos.x), static_cast<int>(mPos.y), 640, 480, 0);
				glfwSetWindowSize(m_glfwWindowPtr, 640, 480);
				m_IsFullscreen = !m_IsFullscreen;
			}
		}

		void Window::MakeContextCurrent() const
		{
			glfwMakeContextCurrent(m_glfwWindowPtr);
		}

		bool Window::ShouldClose() const
		{
			return glfwWindowShouldClose(m_glfwWindowPtr);
		}

		void Window::SwapBuffers() const
		{
			glfwSwapBuffers(m_glfwWindowPtr);
		}

		void Window::SetVsync(const bool isEnabled)
		{
			m_IsVsyncOn = isEnabled;
			glfwSwapInterval(isEnabled ? 1 : 0);
		}

		void Window::Resize(int newWidth, int newHeight)
		{
			glViewport(0, 0, newWidth, newHeight);
		}

		void Window::InitGLFW() const
		{
			if (!glfwInit()) 
			{
				throw std::runtime_error("Failed to initialize GLFW!");
			}
		}

		void Window::CreateWindow(unsigned sizeX, unsigned sizeY)
		{
			m_glfwWindowPtr = glfwCreateWindow(sizeX, sizeY, "Hello World", NULL, NULL);

			if (!m_glfwWindowPtr)
			{
				glfwTerminate();
				abort();
			}
		}

		void Window::SetWindowSizeCallback() const
		{
			glfwSetWindowSizeCallback(m_glfwWindowPtr, StaticWindowSizeCallback);
		}

		void Window::StaticWindowSizeCallback(GLFWwindow* window, const int width, const int height)
		{
			const auto actualWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
			actualWindow->WindowSizeCallback(width, height);
		}

		void Window::WindowSizeCallback(int width, int height) const
		{
			glfwSetWindowSize(m_glfwWindowPtr, width, height);
		}

		void Window::SetKeyCallback() const
		{
			glfwSetKeyCallback(m_glfwWindowPtr, StaticKeyCallback);
		}

		void Window::StaticKeyCallback(GLFWwindow* window, const int key, const int scancode, const int action, const int mods)
		{
			const auto actualWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
			actualWindow->KeyCallback(key, scancode, action, mods);
		}

		void Window::KeyCallback(const int key, const int scancode, const int action, const int mods)
		{
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
				glfwSetWindowShouldClose(m_glfwWindowPtr, true);
			if (key == GLFW_KEY_F11 && action == GLFW_RELEASE)
				SetFullscreen();
		}
}
