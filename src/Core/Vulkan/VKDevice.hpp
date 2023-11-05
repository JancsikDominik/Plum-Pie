#ifndef PLUMPIE_VKDEVICE_HPP
#define PLUMPIE_VKDEVICE_HPP

#include <optional>
#include <unordered_map>

#include <vulkan/vulkan.hpp>

#include "App/Window.hpp"

namespace Plum::VK
{

	struct SwapChainSupportDetails
	{
		vk::SurfaceCapabilitiesKHR capabilities;
		std::vector<vk::SurfaceFormatKHR> formats;
		std::vector<vk::PresentModeKHR> presentModes;
	};

	class Device
	{
	public:
		enum class QueueType
		{
			Graphics,
			Compute,
			Transfer,
			Sparse,
			VideoDecode,
			OpticalFlow,
			Present
		};

		using QueueFamilyIndices = std::unordered_map<QueueType, std::optional<uint32_t>>;

		Device(const vk::Instance& instance, const vk::SurfaceKHR& surface = nullptr);
		~Device();

		void CreateSwapchain(const App::Window* window, const vk::SurfaceKHR& surface = nullptr);
		void CreateImageViews();

	private:
		void CreateLogicalDevice();

		// Physical device creation
		void PickGPU(const vk::Instance& instance, const vk::SurfaceKHR& surface);
		QueueFamilyIndices FindQueueFamilies(const vk::PhysicalDevice& device, const vk::SurfaceKHR& surface) const;
		bool CheckDeviceExtensionSupport(const vk::PhysicalDevice& device) const;
		bool CheckDeviceQueueSupport(const vk::PhysicalDevice& device, const vk::SurfaceKHR& surface) const;
		bool IsDeviceSuitable(const vk::PhysicalDevice& device, const vk::SurfaceKHR& surface) const;
		void GetDeviceQueueHandles();

		SwapChainSupportDetails QuerySwapchainSupport(const vk::PhysicalDevice& device, const vk::SurfaceKHR& surface) const;
		vk::SurfaceFormatKHR ChooseSwapchainSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& availableFormats) const;
		vk::PresentModeKHR ChooseSwapchainPresentMode(const std::vector<vk::PresentModeKHR>& availablePresentModes) const;
		vk::Extent2D ChooseSwapchainExtent(const vk::SurfaceCapabilitiesKHR& capabilities, const App::Window* window) const;

		vk::PhysicalDevice m_chosenGPU = nullptr;
		vk::Device m_device = nullptr;
		QueueFamilyIndices m_queueFamilyIndicies;
		std::unordered_map<QueueType, vk::Queue> m_deviceQueues;
		std::vector<const char*> m_deviceExtensions;

		// TODO: swapchain class
		vk::SwapchainKHR m_swapchain = nullptr;
		std::vector<vk::Image> m_swapchainImages;
		vk::Format m_swapchainImageFormat;
		vk::Extent2D m_swapchainExtent;

		std::vector<vk::ImageView> m_swapchainImageViews;
	};

}

#endif