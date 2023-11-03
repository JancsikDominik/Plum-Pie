#include "VKRenderer.hpp"

#include "Debugging/Console.hpp"
#include <Debugging/Debug.hpp>


namespace Plum::VK
{
	Renderer::Renderer(const std::string& appName, std::vector<const char*> externalExtensions)
	{
		InitVulkan(appName, externalExtensions);
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


	void Renderer::InitVulkan(const std::string& appName, std::vector<const char*> externalExtensions)
	{
		Debug::Console::LogInfo("Initializing Vulkan...");
		
		CreateVulkanInstance(appName, externalExtensions);
		PickGPU();
		CreateVulkanDevice();
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

		// TODO: better way to do this, maybe user could select it somehow
		m_chosenGPU = devices[0];

		if (m_chosenGPU == nullptr)
		{
			Debug::Console::LogError("Failed to find suitible GPU");
			abort();
		}

		vk::PhysicalDeviceProperties gpuProperties = m_chosenGPU.getProperties();

		Debug::Console::LogSuccess("Picked GPU for rendering: %s", gpuProperties.deviceName);
	}


	void Renderer::CreateVulkanDevice()
	{
	}


	void Renderer::CreateSwapChain()
	{
	}


	void Renderer::CleanUpVulkan()
	{
		vkDestroyInstance(m_vulkanInstance, nullptr);

		Debug::Console::LogSuccess("Vulkan destroyed");
	}
}

