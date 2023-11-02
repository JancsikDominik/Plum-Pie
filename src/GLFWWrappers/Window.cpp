#include <stdexcept>
#include <string>

#include "Window.hpp"
#include "Debugging/Console.hpp"
#include "KeyEvent.hpp"
#include "ResizeEvent.hpp"
#include "MouseEvent.hpp"

namespace Plum::GLFW
{
		Window::Window(const std::string& name, unsigned sizeX, unsigned sizeY)
		{
			InitGLFW();
			CreateWindow(sizeX, sizeY, name);
			SetVsync(false);
			SetCurrentContext(true);
			SetCallbacks();
		}

		Window::~Window()
		{
			glfwDestroyWindow(m_glfwWindowPtr);
			glfwTerminate();
		}

		Window::Window(Window&& other) noexcept
		{
			this->m_glfwWindowPtr = other.m_glfwWindowPtr;
			this->m_monitor = other.m_monitor;
			this->m_isFullscreen = other.m_isFullscreen;

			other.m_glfwWindowPtr = nullptr;
			other.m_monitor = nullptr;
		}

		Window& Window::operator=(Window&& other) noexcept
		{
			this->m_glfwWindowPtr = other.m_glfwWindowPtr;
			this->m_monitor = other.m_monitor;
			this->m_isFullscreen = other.m_isFullscreen;

			other.m_glfwWindowPtr = nullptr;
			other.m_monitor = nullptr;
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
			if (!m_isFullscreen) 
			{
				const GLFWvidmode* vidMode = glfwGetVideoMode(m_monitor);
				int x, y;
				glfwGetWindowPos(m_glfwWindowPtr, &x, &y);

				glfwSetWindowMonitor(m_glfwWindowPtr, m_monitor, 0, 0, vidMode->width, vidMode->height, vidMode->refreshRate);
				glfwSetWindowSize(m_glfwWindowPtr, vidMode->width, vidMode->height);
				m_isFullscreen = !m_isFullscreen;
			}
			else 
			{
				//glfwSetWindowMonitor(m_glfwWindowPtr, nullptr, static_cast<int>(mPos.x), static_cast<int>(mPos.y), 640, 480, 0);
				glfwSetWindowSize(m_glfwWindowPtr, 640, 480);
				m_isFullscreen = !m_isFullscreen;
			}
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
			m_isVsyncOn = isEnabled;
			glfwSwapInterval(isEnabled ? 1 : 0);
		}

		void Window::Resize(int newWidth, int newHeight)
		{
			// TODO: Vulkan resize
			//glViewport(0, 0, newWidth, newHeight);
		}

		void Window::SetCurrentContext(bool thisThread) const
		{
			if (thisThread)
				glfwMakeContextCurrent(m_glfwWindowPtr);
			else
				glfwMakeContextCurrent(nullptr);
		}

		void Window::PollEvents() const
		{
			glfwPollEvents();
		}

		double Window::GetTime() const
		{
			return glfwGetTime();
		}

		void Window::SetCallbacks()
		{
			SetWindowSizeCallback();
			SetKeyCallback();
			SetCursorPosCallback();
			SetMouseButtonCallback();
			SetMouseScrollCallback();
		}

		void Window::InitGLFW() const
		{
			if (!glfwInit()) 
			{
				Debug::Console::LogError("failed to initialize GLFW");
				throw std::runtime_error("Failed to initialize GLFW!");
			}
		}

		void Window::CreateWindow(unsigned sizeX, unsigned sizeY, const std::string& name)
		{
			m_glfwWindowPtr = glfwCreateWindow(sizeX, sizeY, name.c_str(), NULL, NULL);

			if (!m_glfwWindowPtr)
			{
				Debug::Console::LogError("failed to create window");
				glfwTerminate();
				abort();
			}
		}

		void Window::SetWindowSizeCallback() const
		{
			glfwSetWindowSizeCallback(m_glfwWindowPtr, StaticWindowSizeCallback);
		}

		void Window::StaticWindowSizeCallback(GLFWwindow* window, int width, int height)
		{
			const auto actualWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
			actualWindow->WindowSizeCallback(width, height);
		}

		void Window::WindowSizeCallback(int width, int height) const
		{
			ResizeEvent resizeEvent(width, height);
			resizeEvent.NotifyObservers();
		}

		void Window::SetKeyCallback() const
		{
			glfwSetKeyCallback(m_glfwWindowPtr, StaticKeyCallback);
		}

		void Window::StaticKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			const auto actualWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
			actualWindow->KeyCallback((Keyboard::Key)key, scancode, (Keyboard::Action)action, mods);
		}

		void Window::KeyCallback(Keyboard::Key key, int scancode, Keyboard::Action action, uint32_t mods)
		{
			if (key == Keyboard::Key::Escape && action == Keyboard::Action::Press)
				glfwSetWindowShouldClose(m_glfwWindowPtr, true);
			if (key == Keyboard::Key::F11 && action == Keyboard::Action::Press)
				SetFullscreen();

			KeyEvent keyEvent(key, action, mods);
			keyEvent.NotifyObservers();
		}

		void Window::SetCursorPosCallback() const
		{
			glfwSetCursorPosCallback(m_glfwWindowPtr, StaticCursorPosCallback);
		}

		void Window::CursorPosCallback(double xpos, double ypos) const
		{
			MouseEvent mouseEvent(Mouse::EventType::Move, glm::vec2(xpos, ypos));
			mouseEvent.NotifyObservers();
		}

		void Window::StaticCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
		{
			const auto actualWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
			actualWindow->CursorPosCallback(xpos, ypos);
		}

		void Window::SetMouseButtonCallback() const
		{
			glfwSetMouseButtonCallback(m_glfwWindowPtr, StaticMouseButtonCallback);
		}

		void Window::MouseButtonCallback(int button, int action, int mods) const
		{
			MouseEvent mouseEvent(Mouse::EventType::ButtonPress, (Mouse::ButtonAction)action, (Mouse::Button)button, mods);
			mouseEvent.NotifyObservers();
		}

		void Window::StaticMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
		{
			const auto actualWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
			actualWindow->MouseButtonCallback(button, action, mods);
		}

		void Window::SetMouseScrollCallback() const
		{
			glfwSetScrollCallback(m_glfwWindowPtr, StaticMouseScrollCallback);
		}
		
		void Window::MouseScrollCallback(double xoffset, double yoffset) const
		{
			MouseEvent mouseEvent(Mouse::EventType::Scroll, {-1, -1}, Mouse::ButtonAction::Invalid, Mouse::Button::Unknown, 0, glm::vec2{xoffset, yoffset});
			mouseEvent.NotifyObservers();
		}
		
		void Window::StaticMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
		{
			const auto actualWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
			actualWindow->MouseScrollCallback(xoffset, yoffset);
		}
}
