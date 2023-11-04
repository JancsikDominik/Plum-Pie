#include "VKRenderer.hpp"

#include "Debugging/Console.hpp"
#include "Debugging/Debug.hpp"


namespace Plum::VK
{
	std::string DeviceQueueToString(DeviceQueue q)
	{
		switch (q)
		{
		case DeviceQueue::Graphics:
			return "Graphics";
		case DeviceQueue::Compute:
			return "Compute";
		case DeviceQueue::Transfer:
			return "Transfer";
		case DeviceQueue::Sparse:
			return "Sparse";
		case DeviceQueue::VideoDecode:
			return "VideoDecode";
		case DeviceQueue::OpticalFlow:
			return "OpticalFlow";
		default:
			PLUM_ASSERT(false);
			return "";
		}
	}

	Renderer::Renderer(const std::string& appName, std::vector<const char*> externalExtensions)
	{
		m_queueFamilyIndicies = {
			{ DeviceQueue::Graphics,	{} },
			{ DeviceQueue::Compute,		{} },
			{ DeviceQueue::Transfer,	{} },
			{ DeviceQueue::Sparse,		{} },
			{ DeviceQueue::VideoDecode,	{} },
			{ DeviceQueue::OpticalFlow,	{} }
		};

		InitVulkan(appName, externalExtensions);
	}


	Renderer::Renderer(const GLFW::Window* windowToRenderTo)
	{
		m_queueFamilyIndicies = {
			{ DeviceQueue::Graphics,	{} },
			{ DeviceQueue::Compute,		{} },
			{ DeviceQueue::Transfer,	{} },
			{ DeviceQueue::Sparse,		{} },
			{ DeviceQueue::VideoDecode,	{} },
			{ DeviceQueue::OpticalFlow,	{} }
		};

		InitVulkan(windowToRenderTo->GetWindowTitle(), windowToRenderTo->GetRequiredExtensions(), windowToRenderTo);
	}


	Renderer::~Renderer()
	{
		CleanUpVulkan();
	}


	void Renderer::SetViewport(int x, int y, int width, int height)
	{
	}

	
	void Renderer::SetClearColor(Color clearColor)
	{
	}

	
	void Renderer::SetCullFace(bool enable)
	{
	}

	
	void Renderer::SetDepthTest(bool enable)
	{
	}

	
	void Renderer::SetProgram(ShaderProgram& program)
	{
	}

	
	void Renderer::SetUniformData(const std::string& name, const std::any& value)
	{
	}

	
	void Renderer::Clear()
	{
	}

	
	void Renderer::Render()
	{
	}


	void Renderer::InitVulkan(const std::string& appName, std::vector<const char*> externalExtensions, const GLFW::Window* window)
	{
		Debug::Console::LogInfo("Initializing Vulkan...");
		
		CreateVulkanInstance(appName, externalExtensions);

		// allowing to render without a window for off-screen rendering
		if (window != nullptr)
			m_surface = window->CreateWindowSurface(m_vulkanInstance);

		PickGPU();
		CreateVulkanDevice();
		GetDeviceQueueHandles();
		CreateSwapChain();

		Debug::Console::LogSuccess("Initialized Vulkan");
	}


	void Renderer::CreateVulkanInstance(const std::string& appName, std::vector<const char*> externalExtensions)
	{
		uint32_t version;
		vkEnumerateInstanceVersion(&version);

		Debug::Console::LogInfo("System supports Vulkan version: %d.%d.%d", 
								VK_API_VERSION_MAJOR(version), 
								VK_API_VERSION_MINOR(version),
								VK_API_VERSION_PATCH(version));
		// zeroing out patch
		version &= ~(0xFFFU);

		vk::ApplicationInfo appInfo {
			appName.c_str(),
			version,
			"PlumPie",
			version,
			version
		};

		vk::InstanceCreateInfo createInfo {
			vk::InstanceCreateFlags(),
			&appInfo,
			0,				// we disable validation layers for now
			nullptr,		// we disable validation layers for now
			static_cast<uint32_t>(externalExtensions.size()),
			externalExtensions.data()
		};

		try 
		{
			m_vulkanInstance = vk::createInstance(createInfo);

			Debug::Console::LogInfo("Using extensions: ");
			for (const auto& extName : externalExtensions)
				Debug::Console::Log("\t    %s", extName);
		}
		catch (vk::SystemError err) 
		{
			Debug::Console::LogError("Failed to create Vulkan instance.");
			abort();
		}

		Debug::Console::LogSuccess("Vulkan instance created");
	}


	void Renderer::PickGPU()
	{
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(m_vulkanInstance, &deviceCount, nullptr);

		if (deviceCount == 0)
		{
			Debug::Console::LogError("Failed to find GPUs with Vulkan support");
			abort();
		}

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(m_vulkanInstance, &deviceCount, devices.data());

		for (const auto& device : devices)
		{
			if (IsDeviceSuitable(device))
			{
				m_chosenGPU = device;
				m_queueFamilyIndicies = FindQueueFamilies(m_chosenGPU);
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


	Renderer::QueueFamilyIndices Renderer::FindQueueFamilies(const vk::PhysicalDevice& device) const
	{
		QueueFamilyIndices indices;

		std::vector<vk::QueueFamilyProperties> queueFamilies;
		queueFamilies = device.getQueueFamilyProperties();

		for (int i = 0; i < queueFamilies.size(); i++)
		{
			if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eGraphics)
			{
				indices[DeviceQueue::Graphics] = i;
			}
			else if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eCompute)
			{
				indices[DeviceQueue::Compute] = i;
			}
			else if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eTransfer)
			{
				indices[DeviceQueue::Transfer] = i;
			}
			else if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eSparseBinding)
			{
				indices[DeviceQueue::Sparse] = i;
			}
			else if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eVideoDecodeKHR)
			{
				indices[DeviceQueue::VideoDecode] = i;
			}
			else if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eOpticalFlowNV)
			{
				indices[DeviceQueue::OpticalFlow] = i;
			}
		}

		return indices;
	}


	bool Renderer::IsDeviceSuitable(const vk::PhysicalDevice& device) const
	{
		const auto& indices = FindQueueFamilies(device);
		return indices.at(DeviceQueue::Graphics).has_value();
	}


	void Renderer::CreateVulkanDevice()
	{
		float queuePriority = 1.0f;

		vk::DeviceQueueCreateInfo queueCreateInfo {
			{},
			m_queueFamilyIndicies[DeviceQueue::Graphics].value(),
			1,
			&queuePriority
		};

		vk::PhysicalDeviceFeatures deviceFeatures;

		vk::DeviceCreateInfo createInfo;
		createInfo.pQueueCreateInfos = &queueCreateInfo;
		createInfo.queueCreateInfoCount = 1;
		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = 0;

		// TODO: validation layers
		//if (enableValidationLayers) {
		//	createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		//	createInfo.ppEnabledLayerNames = validationLayers.data();
		//}
		//else {
			createInfo.enabledLayerCount = 0;
		//}

		m_device = m_chosenGPU.createDevice(createInfo);

		Debug::Console::LogSuccess("Logical device created");
	}


	void Renderer::GetDeviceQueueHandles()
	{
		for (auto const& [key, val] : m_queueFamilyIndicies)
		{
			if (val.has_value())
			{
				m_deviceQueues[key] = m_device.getQueue(m_queueFamilyIndicies[key].value(), 0);
				Debug::Console::LogInfo("Got %s device queue handle", DeviceQueueToString(key).c_str());
			}
		}
	}


	void Renderer::CreateSwapChain()
	{
	}


	void Renderer::CleanUpVulkan()
	{
		m_device.destroy();
		m_vulkanInstance.destroy();

		Debug::Console::LogSuccess("Vulkan destroyed");
	}
}

