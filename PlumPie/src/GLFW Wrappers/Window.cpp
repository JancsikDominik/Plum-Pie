#include "Window.hpp"
#include <stdexcept>
#include <string>

namespace Plum::GLFW
{
		Window::Window(const int width, const int height, const char* title)
			: mTitle(title)
			, mWidth(width)
			, mHeight(height)
		{
				InitGLFW();
				mMonitor = glfwGetPrimaryMonitor();
				CreateWindow();
				SetWindowSizeCallback();
				SetKeyCallback();
		}

		Window::~Window()
		{
			glfwDestroyWindow(mWindow);
			glfwTerminate();
		}

		Window::Window(Window&& other) noexcept
		{
			this->mWindow = other.mWindow;
			this->mMonitor = other.mMonitor;
			this->mTitle = other.mTitle;
			this->mWidth = other.mWidth;
			this->mHeight = other.mHeight;
			this->mPos = other.mPos;
			this->mFullscreen = other.mFullscreen;

			other.mWindow = nullptr;
			other.mMonitor = nullptr;
			other.mTitle = nullptr;
			other.mWidth = 0;
			other.mHeight = 0;
			other.mPos = glm::vec2(0);
		}

		Window& Window::operator=(Window&& other) noexcept
		{
			this->mWindow = other.mWindow;
			this->mMonitor = other.mMonitor;
			this->mTitle = other.mTitle;
			this->mWidth = other.mWidth;
			this->mHeight = other.mHeight;
			this->mPos = other.mPos;
			this->mFullscreen = other.mFullscreen;

			other.mWindow = nullptr;
			other.mMonitor = nullptr;
			other.mTitle = nullptr;
			other.mWidth = 0;
			other.mHeight = 0;
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
				glfwGetWindowPos(mWindow, &x, &y);

				mPos.x = static_cast<float>(x);
				mPos.y = static_cast<float>(y);

				glfwGetWindowSize(mWindow, &mWidth, &mHeight);
				glfwSetWindowMonitor(mWindow, mMonitor, 0, 0, vidMode->width, vidMode->height, vidMode->refreshRate);
				glfwSetWindowSize(mWindow, vidMode->width, vidMode->height);
				mFullscreen = !mFullscreen;
			}
			else 
			{
				glfwSetWindowMonitor(mWindow, nullptr, static_cast<int>(mPos.x), static_cast<int>(mPos.y), mWidth, mHeight, 0);
				glfwSetWindowSize(mWindow, mWidth, mHeight);
				mFullscreen = !mFullscreen;
			}
		}

		void Window::MakeContextCurrent() const
		{
			glfwMakeContextCurrent(mWindow);
		}

		bool Window::ShouldClose() const
		{
			return glfwWindowShouldClose(mWindow);
		}

		void Window::SwapBuffers() const
		{
			glfwSwapBuffers(mWindow);
		}

		void Window::InitGLFW() const
		{
			if (!glfwInit()) 
			{
				throw std::runtime_error("Failed to initialize GLFW!");
			}
		}

		void Window::CreateWindow()
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			mWindow = glfwCreateWindow(mWidth, mHeight, mTitle, nullptr, nullptr);

			if (!mWindow) 
				throw std::runtime_error("Could not create GLFW window!");

			glfwSetWindowUserPointer(mWindow, this);
		}

		void Window::SetWindowSizeCallback() const
		{
			glfwSetWindowSizeCallback(mWindow, StaticWindowSizeCallback);
		}

		void Window::StaticWindowSizeCallback(GLFWwindow* window, const int width, const int height)
		{
			const auto actualWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
			actualWindow->WindowSizeCallback(width, height);
		}

		void Window::WindowSizeCallback(int width, int height) const
		{
			glfwSetWindowSize(mWindow, width, height);
		}

		void Window::SetKeyCallback() const
		{
			glfwSetKeyCallback(mWindow, StaticKeyCallback);
		}

		void Window::StaticKeyCallback(GLFWwindow* window, const int key, const int scancode, const int action, const int mods)
		{
			const auto actualWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
			actualWindow->KeyCallback(key, scancode, action, mods);
		}

		void Window::KeyCallback(const int key, const int scancode, const int action, const int mods)
		{
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
				glfwSetWindowShouldClose(mWindow, true);
			if (key == GLFW_KEY_F11 && action == GLFW_RELEASE)
				SetFullscreen();
		}
}
