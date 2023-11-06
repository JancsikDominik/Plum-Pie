#include "VKRenderer.hpp"

#include <set>

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
		case DeviceQueue::Present:
			return "Present";
		default:
			PLUM_ASSERT(false);
			return "";
		}
	}

	Renderer::Renderer(const std::string& appName, std::vector<const char*> externalExtensions)
	{
		InitVulkan(appName, externalExtensions);
	}

	Renderer::Renderer(const App::Window* windowToRenderTo)
	{
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

	void Renderer::InitVulkan(const std::string& appName, std::vector<const char*> externalExtensions, const App::Window* window)
	{
		Debug::Console::LogInfo("Initializing Vulkan...");
		
		CreateVulkanInstance(appName, externalExtensions);

		// allowing to render without a window for off-screen rendering
		if (window != nullptr)
		{
			m_surface = window->CreateWindowSurface(m_vulkanInstance);
		}

		// explicit lifetime control, cuz we have to destroy it before the instance gets destroyed
		m_device = new Device(m_vulkanInstance, m_surface);

		m_device->CreateSwapchain(window, m_surface);
		m_device->CreateImageViews();

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
		catch (const vk::SystemError& e)
		{
			Debug::Console::LogError("Failed to create Vulkan instance: %s", e.what());
		}

		Debug::Console::LogSuccess("Vulkan instance created");
	}

	void Renderer::CreatePipeline()
	{
	}

	void Renderer::CleanUpVulkan()
	{
		delete m_device;

		m_vulkanInstance.destroySurfaceKHR(m_surface);
		m_vulkanInstance.destroy();

		Debug::Console::LogSuccess("Vulkan destroyed");
	}
}

