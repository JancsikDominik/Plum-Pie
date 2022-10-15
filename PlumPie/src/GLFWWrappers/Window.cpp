#include "Window.hpp"
#include <stdexcept>
#include <string>

namespace Plum::GLFW
{
		Window::Window()
		{
			InitGLFW();
			SetVsync(true);
		}

		Window::~Window()
		{
			glfwDestroyWindow(glfwWindowPtr);
			glfwTerminate();
		}

		Window::Window(Window&& other) noexcept
		{
			this->glfwWindowPtr = other.glfwWindowPtr;
			this->mMonitor = other.mMonitor;
			this->mPos = other.mPos;
			this->mFullscreen = other.mFullscreen;

			other.glfwWindowPtr = nullptr;
			other.mMonitor = nullptr;
			other.mPos = glm::vec2(0);
		}

		Window& Window::operator=(Window&& other) noexcept
		{
			this->glfwWindowPtr = other.glfwWindowPtr;
			this->mMonitor = other.mMonitor;
			this->mPos = other.mPos;
			this->mFullscreen = other.mFullscreen;

			other.glfwWindowPtr = nullptr;
			other.mMonitor = nullptr;
			other.mPos = glm::vec2(0);
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
			if (!mFullscreen) 
			{
				const GLFWvidmode* vidMode = glfwGetVideoMode(mMonitor);
				int x, y;
				glfwGetWindowPos(glfwWindowPtr, &x, &y);

				mPos.x = static_cast<float>(x);
				mPos.y = static_cast<float>(y);

				glfwSetWindowMonitor(glfwWindowPtr, mMonitor, 0, 0, vidMode->width, vidMode->height, vidMode->refreshRate);
				glfwSetWindowSize(glfwWindowPtr, vidMode->width, vidMode->height);
				mFullscreen = !mFullscreen;
			}
			else 
			{
				glfwSetWindowMonitor(glfwWindowPtr, nullptr, static_cast<int>(mPos.x), static_cast<int>(mPos.y), 640, 480, 0);
				glfwSetWindowSize(glfwWindowPtr, 640, 480);
				mFullscreen = !mFullscreen;
			}
		}

		void Window::MakeContextCurrent() const
		{
			glfwMakeContextCurrent(glfwWindowPtr);
		}

		bool Window::ShouldClose() const
		{
			return glfwWindowShouldClose(glfwWindowPtr);
		}

		void Window::SwapBuffers() const
		{
			glfwSwapBuffers(glfwWindowPtr);
		}

		void Window::SetVsync(const bool isEnabled)
		{
			mIsVsyncOn = isEnabled;
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

		void Window::SetWindowSizeCallback() const
		{
			glfwSetWindowSizeCallback(glfwWindowPtr, StaticWindowSizeCallback);
		}

		void Window::StaticWindowSizeCallback(GLFWwindow* window, const int width, const int height)
		{
			const auto actualWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
			actualWindow->WindowSizeCallback(width, height);
		}

		void Window::WindowSizeCallback(int width, int height) const
		{
			glfwSetWindowSize(glfwWindowPtr, width, height);
		}

		void Window::SetKeyCallback() const
		{
			glfwSetKeyCallback(glfwWindowPtr, StaticKeyCallback);
		}

		void Window::StaticKeyCallback(GLFWwindow* window, const int key, const int scancode, const int action, const int mods)
		{
			const auto actualWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
			actualWindow->KeyCallback(key, scancode, action, mods);
		}

		void Window::KeyCallback(const int key, const int scancode, const int action, const int mods)
		{
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
				glfwSetWindowShouldClose(glfwWindowPtr, true);
			if (key == GLFW_KEY_F11 && action == GLFW_RELEASE)
				SetFullscreen();
		}
}
