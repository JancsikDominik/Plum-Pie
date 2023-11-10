#include "VKSwapchain.hpp"

#include "Debugging/Debug.hpp"
#include "Core/Vulkan/VKDevice.hpp"

namespace Plum::VK
{
	Swapchain::Swapchain(const Device& device, const vk::SurfaceKHR& surface, const App::Window& window)
	{
		Device::SwapChainSupportDetails swapChainSupport = device.QuerySwapchainSupport(device.GetPhysicalDevice(), surface);

		vk::SurfaceFormatKHR surfaceFormat = ChooseSwapchainSurfaceFormat(swapChainSupport.formats);
		vk::PresentModeKHR presentMode = ChooseSwapchainPresentMode(swapChainSupport.presentModes);
		vk::Extent2D extent = ChooseSwapchainExtent(swapChainSupport.capabilities, &window);

		uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

		if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
		{
			imageCount = swapChainSupport.capabilities.maxImageCount;
		}

		vk::SwapchainCreateInfoKHR createInfo;
		createInfo.surface = surface;
		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = vk::ImageUsageFlagBits::eColorAttachment;

		const auto& queueFamilyIndices = device.GetQueueFamilyIndices();

		if (queueFamilyIndices.at(VK::Device::QueueType::Graphics) != queueFamilyIndices.at(VK::Device::QueueType::Present))
		{
			uint32_t graphicsIndex = queueFamilyIndices.at(VK::Device::QueueType::Graphics).value();
			uint32_t presentIndex = queueFamilyIndices.at(VK::Device::QueueType::Graphics).value();

			uint32_t queueFamilyIndices[] = {
				graphicsIndex,
				presentIndex
			};

			// TODO: exclusive?
			createInfo.imageSharingMode = vk::SharingMode::eConcurrent;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else
		{
			createInfo.imageSharingMode = vk::SharingMode::eExclusive;
			createInfo.queueFamilyIndexCount = 0;
			createInfo.pQueueFamilyIndices = nullptr;
		}

		createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
		createInfo.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;
		createInfo.oldSwapchain = VK_NULL_HANDLE;

		const auto& logicalDevice = device.GetLogicalDevice();

		try
		{
			m_swapchain = logicalDevice.createSwapchainKHR(createInfo);
		}
		catch (const vk::SystemError& e)
		{
			Debug::Console::LogError("Failed to create swapchain: %s", e.what());
		}


		m_swapchainImages = logicalDevice.getSwapchainImagesKHR(m_swapchain);
		m_swapchainImageFormat = surfaceFormat.format;
		m_swapchainExtent = extent;

		Debug::Console::LogSuccess("Swapchain created");
	}

	const std::vector<vk::Image>& Swapchain::GetSwapchainImages() const
	{
		return m_swapchainImages;
	}

	const vk::Format& Swapchain::GetSwapchainImageFormat() const
	{
		return m_swapchainImageFormat;
	}

	const vk::Extent2D& Swapchain::GetExtent() const
	{
		return m_swapchainExtent;
	}

	void Swapchain::CleanUp(const Device& device)
	{
		device.GetLogicalDevice().destroySwapchainKHR(m_swapchain);
	}

	vk::SurfaceFormatKHR Swapchain::ChooseSwapchainSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& availableFormats) const
	{
		for (const auto& availableFormat : availableFormats)
		{
			if (availableFormat.format == vk::Format::eR8G8B8A8Srgb && availableFormat.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear)
			{
				return availableFormat;
			}
		}

		return availableFormats[0];
	}

	vk::PresentModeKHR Swapchain::ChooseSwapchainPresentMode(const std::vector<vk::PresentModeKHR>& availablePresentModes) const
	{
		for (const auto& availablePresentMode : availablePresentModes)
		{
			if (availablePresentMode == vk::PresentModeKHR::eMailbox)
			{
				return availablePresentMode;
			}
		}

		return vk::PresentModeKHR::eFifo;
	}

	vk::Extent2D Swapchain::ChooseSwapchainExtent(const vk::SurfaceCapabilitiesKHR& capabilities, const App::Window* window) const
	{
		if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
		{
			return capabilities.currentExtent;
		}
		else
		{
			const auto& size = window->GetSize();

			VkExtent2D extent = {
				static_cast<uint32_t>(size.width),
				static_cast<uint32_t>(size.height)
			};

			extent.width = std::clamp(extent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
			extent.height = std::clamp(extent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

			return extent;
		}
	}

}
