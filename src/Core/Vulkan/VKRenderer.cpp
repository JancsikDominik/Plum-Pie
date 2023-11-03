#include "VKRenderer.hpp"

#include "Debugging/Console.hpp"


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
		GetPhysicalDevice();
		CreateVulkanDevice();
		CreateSwapChain();

		Debug::Console::LogSuccess("Initialized Vulkan.");
	}


	void Renderer::CreateVulkanInstance(const std::string& appName, std::vector<const char*> externalExtensions)
	{
		Debug::Console::LogInfo("Creating Vulkan instance...");

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
	}


	void Renderer::GetPhysicalDevice()
	{

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
	}
}

