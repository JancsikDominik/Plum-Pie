#ifndef PLUMPIE_VKSWAPCHAIN_HPP
#define PLUMPIE_VKSWAPCHAIN_HPP

#include <vulkan/vulkan.hpp>

#include "App/Window.hpp"

namespace Plum::VK
{
	class Device;

	class Swapchain
	{
	public:
		Swapchain(const Device& device, const vk::SurfaceKHR& surface, const App::Window& window);

		const std::vector<vk::Image>& GetSwapchainImages() const;
		const vk::Format& GetSwapchainImageFormat() const;
		const vk::Extent2D& GetExtent() const;

		void CleanUp(const Device& device);

	private:
		vk::SurfaceFormatKHR ChooseSwapchainSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& availableFormats) const;
		vk::PresentModeKHR ChooseSwapchainPresentMode(const std::vector<vk::PresentModeKHR>& availablePresentModes) const;
		vk::Extent2D ChooseSwapchainExtent(const vk::SurfaceCapabilitiesKHR& capabilities, const App::Window* window) const;

		vk::SwapchainKHR m_swapchain = nullptr;
		std::vector<vk::Image> m_swapchainImages;
		vk::Format m_swapchainImageFormat;
		vk::Extent2D m_swapchainExtent;
	};
}

#endif