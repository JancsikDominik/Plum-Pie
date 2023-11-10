#ifndef PLUMPIE_VKDEVICE_HPP
#define PLUMPIE_VKDEVICE_HPP

#include <optional>
#include <unordered_map>

#include <vulkan/vulkan.hpp>

#include "App/Window.hpp"
#include "Core/Memory.hpp"
#include "VKSwapchain.hpp"

namespace Plum::VK
{
	class Device
	{
	public:
		struct SwapChainSupportDetails
		{
			vk::SurfaceCapabilitiesKHR capabilities;
			std::vector<vk::SurfaceFormatKHR> formats;
			std::vector<vk::PresentModeKHR> presentModes;
		};

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

		using QueueMap = std::unordered_map<QueueType, vk::Queue>;
		using QueueFamilyIndices = std::unordered_map<QueueType, std::optional<uint32_t>>;

		Device(const vk::Instance& instance, const vk::SurfaceKHR& surface = nullptr);
		~Device();

		void DestroySwapchain(Owned<Swapchain>& swapchain);
		void CreateImageViews(const Owned<Swapchain>& swapchain);

		[[nodiscard]] Owned<Swapchain> CreateSwapchain(const App::Window* window, const vk::SurfaceKHR& surface = nullptr);

		[[nodiscard]] SwapChainSupportDetails QuerySwapchainSupport(const vk::PhysicalDevice& phDevice, const vk::SurfaceKHR& surface) const;
		[[nodiscard]] const QueueFamilyIndices& GetQueueFamilyIndices() const;
		[[nodiscard]] const vk::PhysicalDevice& GetPhysicalDevice() const;
		[[nodiscard]] const vk::Device& GetLogicalDevice() const;
		[[nodiscard]] const QueueMap& GetDeviceQueues() const;

	private:
		void CreateLogicalDevice();

		// Physical device creation
		void PickGPU(const vk::Instance& instance, const vk::SurfaceKHR& surface);
		QueueFamilyIndices FindQueueFamilies(const vk::PhysicalDevice& device, const vk::SurfaceKHR& surface) const;
		bool CheckDeviceExtensionSupport(const vk::PhysicalDevice& device) const;
		bool CheckDeviceQueueSupport(const vk::PhysicalDevice& device, const vk::SurfaceKHR& surface) const;
		bool IsDeviceSuitable(const vk::PhysicalDevice& device, const vk::SurfaceKHR& surface) const;
		void GetDeviceQueueHandles();

		vk::PhysicalDevice m_chosenGPU = nullptr;
		vk::Device m_device = nullptr;
		QueueFamilyIndices m_queueFamilyIndicies;
		QueueMap m_deviceQueues;
		std::vector<const char*> m_deviceExtensions;
		std::vector<vk::ImageView> m_swapchainImageViews;
	};

}

#endif