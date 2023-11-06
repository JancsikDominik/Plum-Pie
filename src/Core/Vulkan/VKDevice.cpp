#include "VKDevice.hpp"

#include <set>

#include "Debugging/Console.hpp"
#include "Debugging/Debug.hpp"

namespace Plum::VK
{
	std::string DeviceQueueToString(Device::QueueType q)
	{
		switch (q)
		{
		case Device::QueueType::Graphics:
			return "Graphics";
		case Device::QueueType::Compute:
			return "Compute";
		case Device::QueueType::Transfer:
			return "Transfer";
		case Device::QueueType::Sparse:
			return "Sparse";
		case Device::QueueType::VideoDecode:
			return "VideoDecode";
		case Device::QueueType::OpticalFlow:
			return "OpticalFlow";
		case Device::QueueType::Present:
			return "Present";
		default:
			PLUM_ASSERT(false);
			return "";
		}
	}

	Device::Device(const vk::Instance& instance, const vk::SurfaceKHR& surface)
	{
		m_queueFamilyIndicies = {
			{ QueueType::Graphics,		{} },
			{ QueueType::Compute,		{} },
			{ QueueType::Transfer,		{} },
			{ QueueType::Sparse,		{} },
			{ QueueType::VideoDecode,	{} },
			{ QueueType::OpticalFlow,	{} },
			{ QueueType::Present,		{} }
		};

		if (surface != nullptr)
		{
			m_deviceExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
		}

		PickGPU(instance, surface);
		CreateLogicalDevice();
		GetDeviceQueueHandles();
	}

	Device::~Device()
	{
		for (const auto& imgView : m_swapchainImageViews)
			m_device.destroyImageView(imgView);

		m_device.destroySwapchainKHR(m_swapchain);
		m_device.destroy();
	}

	void Device::CreateLogicalDevice()
	{
		std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies = {
			m_queueFamilyIndicies[QueueType::Graphics].value(),
			m_queueFamilyIndicies[QueueType::Present].value(),
			m_queueFamilyIndicies[QueueType::Compute].value()
		};

		float queuePriority = 1.0f;
		for (uint32_t queueFamily : uniqueQueueFamilies) {
			vk::DeviceQueueCreateInfo queueCreateInfo {
				{},
					queueFamily,
					1,
					& queuePriority
			};
			queueCreateInfos.push_back(queueCreateInfo);
		}

		vk::PhysicalDeviceFeatures deviceFeatures;

		vk::DeviceCreateInfo createInfo;
		createInfo.pQueueCreateInfos = queueCreateInfos.data();
		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = static_cast<uint32_t>(m_deviceExtensions.size());
		createInfo.ppEnabledExtensionNames = m_deviceExtensions.data();

		// TODO: validation layers
		//if (enableValidationLayers) {
		//	createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		//	createInfo.ppEnabledLayerNames = validationLayers.data();
		//}
		//else {
		createInfo.enabledLayerCount = 0;
		//}

		try
		{
			m_device = m_chosenGPU.createDevice(createInfo);
		}
		catch (const vk::SystemError& e)
		{
			Debug::Console::LogError("Failed to create logical device: %s", e.what());
		}

		Debug::Console::LogSuccess("Logical device created");
	}

	void Device::PickGPU(const vk::Instance& instance, const vk::SurfaceKHR& surface)
	{
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

		if (deviceCount == 0)
		{
			Debug::Console::LogError("Failed to find GPUs with Vulkan support");
			abort();
		}

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

		for (const auto& device : devices)
		{
			if (IsDeviceSuitable(device, surface))
			{
				m_chosenGPU = device;
				m_queueFamilyIndicies = FindQueueFamilies(m_chosenGPU, surface);
			}
		}

		if (m_chosenGPU == nullptr)
		{
			Debug::Console::LogError("Failed to find suitible GPU");
			abort();
		}

		vk::PhysicalDeviceProperties gpuProperties = m_chosenGPU.getProperties();

		Debug::Console::LogSuccess("Picked GPU for rendering: %s", gpuProperties.deviceName);
	}

	bool Device::IsDeviceSuitable(const vk::PhysicalDevice& device, const vk::SurfaceKHR& surface) const
	{
		bool swapChainAdequate = false;
		if (CheckDeviceExtensionSupport(device))
		{
			SwapChainSupportDetails swapChainSupport = QuerySwapchainSupport(device, surface);
			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
		}

		return CheckDeviceQueueSupport(device, surface) && swapChainAdequate;
	}

	void Device::GetDeviceQueueHandles()
	{
		for (auto const& [key, val] : m_queueFamilyIndicies)
		{
			if (val.has_value())
			{
				vk::Queue q = m_device.getQueue(m_queueFamilyIndicies[key].value(), 0);

				if (q)
				{
					m_deviceQueues[key] = q;
					Debug::Console::LogInfo("Got %s device queue handle", DeviceQueueToString(key).c_str());
				}
			}
		}
	}

	Device::QueueFamilyIndices Device::FindQueueFamilies(const vk::PhysicalDevice& device, const vk::SurfaceKHR& surface) const
	{
		QueueFamilyIndices indices;

		std::vector<vk::QueueFamilyProperties> queueFamilies;
		queueFamilies = device.getQueueFamilyProperties();

		for (int i = 0; i < queueFamilies.size(); i++)
		{
			if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eGraphics)
			{
				indices[QueueType::Graphics] = i;
			}
			if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eCompute)
			{
				indices[QueueType::Compute] = i;
			}
			if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eTransfer)
			{
				indices[QueueType::Transfer] = i;
			}
			if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eSparseBinding)
			{
				indices[QueueType::Sparse] = i;
			}
			if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eVideoDecodeKHR)
			{
				indices[QueueType::VideoDecode] = i;
			}
			if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eOpticalFlowNV)
			{
				indices[QueueType::OpticalFlow] = i;
			}

			// checking if it can render to surface
			if (surface != nullptr && device.getSurfaceSupportKHR(i, surface))
			{
				indices[QueueType::Present] = i;
			}

		}

		return indices;
	}

	bool Device::CheckDeviceExtensionSupport(const vk::PhysicalDevice& device) const
	{
		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

		std::vector<vk::ExtensionProperties> availableExtensions = device.enumerateDeviceExtensionProperties();

		std::set<std::string> requiredExtensions(m_deviceExtensions.begin(), m_deviceExtensions.end());

		for (const auto& extension : availableExtensions)
		{
			requiredExtensions.erase(extension.extensionName);
		}

		return requiredExtensions.empty();
	}

	bool Device::CheckDeviceQueueSupport(const vk::PhysicalDevice& device, const vk::SurfaceKHR& surface) const
	{
		const auto& indices = FindQueueFamilies(device, surface);

		if (surface != nullptr)
			return indices.at(QueueType::Graphics).has_value() && indices.at(QueueType::Present).has_value();
		else
			return indices.at(QueueType::Graphics).has_value();
	}
	
	void Device::CreateSwapchain(const App::Window* window, const vk::SurfaceKHR& surface)
	{
		SwapChainSupportDetails swapChainSupport = QuerySwapchainSupport(m_chosenGPU, surface);

		vk::SurfaceFormatKHR surfaceFormat = ChooseSwapchainSurfaceFormat(swapChainSupport.formats);
		vk::PresentModeKHR presentMode = ChooseSwapchainPresentMode(swapChainSupport.presentModes);
		vk::Extent2D extent = ChooseSwapchainExtent(swapChainSupport.capabilities, window);

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

		if (m_queueFamilyIndicies[QueueType::Graphics] != m_queueFamilyIndicies[QueueType::Present])
		{
			uint32_t queueFamilyIndices[] = {
				m_queueFamilyIndicies[QueueType::Graphics].value(),
				m_queueFamilyIndicies[QueueType::Present].value()
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

		try
		{
			m_swapchain = m_device.createSwapchainKHR(createInfo);
		}
		catch (const vk::SystemError& e)
		{
			Debug::Console::LogError("Failed to create swapchain: %s", e.what());
		}


		m_swapchainImages = m_device.getSwapchainImagesKHR(m_swapchain);
		m_swapchainImageFormat = surfaceFormat.format;
		m_swapchainExtent = extent;

		Debug::Console::LogSuccess("Swapchain created");
	}

	void Device::CreateImageViews()
	{
		m_swapchainImageViews.resize(m_swapchainImages.size());

		for (int i = 0; i < m_swapchainImages.size(); i++)
		{
			vk::ImageViewCreateInfo createInfo;
			createInfo.image = m_swapchainImages[i];
			createInfo.viewType = vk::ImageViewType::e2D;
			createInfo.format = m_swapchainImageFormat;
			createInfo.components.r = vk::ComponentSwizzle::eIdentity;
			createInfo.components.g = vk::ComponentSwizzle::eIdentity;
			createInfo.components.b = vk::ComponentSwizzle::eIdentity;
			createInfo.components.a = vk::ComponentSwizzle::eIdentity;
			createInfo.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
			createInfo.subresourceRange.baseMipLevel = 0;
			createInfo.subresourceRange.levelCount = 1;
			createInfo.subresourceRange.baseArrayLayer = 0;
			createInfo.subresourceRange.layerCount = 1;

			try
			{
				m_swapchainImageViews[i] = m_device.createImageView(createInfo);
			}
			catch (const vk::SystemError& e)
			{
				Debug::Console::LogError("Failed to create image view: %s", e.what());
			}
		}

		Debug::Console::LogSuccess("Swapchain image views created");
	}

	SwapChainSupportDetails Device::QuerySwapchainSupport(const vk::PhysicalDevice& device, const vk::SurfaceKHR& surface) const
	{
		SwapChainSupportDetails details{
			device.getSurfaceCapabilitiesKHR(surface),
			device.getSurfaceFormatsKHR(surface),
			device.getSurfacePresentModesKHR(surface)
		};

		return details;
	}

	vk::SurfaceFormatKHR Device::ChooseSwapchainSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& availableFormats) const
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

	vk::PresentModeKHR Device::ChooseSwapchainPresentMode(const std::vector<vk::PresentModeKHR>& availablePresentModes) const
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

	vk::Extent2D Device::ChooseSwapchainExtent(const vk::SurfaceCapabilitiesKHR& capabilities, const App::Window* window) const
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

