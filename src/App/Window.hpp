#ifndef PLUMPIE_WINDOW_HPP
#define PLUMPIE_WINDOW_HPP

#include <vector>
#include <string>
#include <vulkan/vulkan.hpp>

namespace Plum::App
{
	class Window
	{
	public:
		struct Size
		{
			int32_t width, height;
		};

		virtual ~Window() {};

		virtual void SetFullscreen() = 0;
		virtual void SetVsync(const bool isEnabled) = 0;
		virtual void Resize(int newWidth, int newHeight) = 0;

		virtual void PollEvents() const = 0;

		[[nodiscard]] virtual Size GetSize() const = 0;
		[[nodiscard]] virtual std::vector<const char*> GetRequiredExtensions() const = 0;
		[[nodiscard]] virtual bool ShouldClose() const = 0;
		[[nodiscard]] virtual bool IsVsync() const = 0;
		[[nodiscard]] virtual double GetTime() const = 0;
		[[nodiscard]] virtual const std::string& GetWindowTitle() const = 0;
		[[nodiscard]] virtual vk::SurfaceKHR CreateWindowSurface(const vk::Instance& instance) const = 0;
	};
}

#endif