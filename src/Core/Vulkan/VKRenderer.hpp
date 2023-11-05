#ifndef PLUMPIE_VKRENDERER_HPP
#define PLUMPIE_VKRENDERER_HPP

#include <optional>
#include <unordered_map>
#include <vulkan/vulkan.hpp>

#include "Core/Renderer.hpp"
#include "App/Window.hpp"

namespace Plum::VK
{
	enum class DeviceQueue
	{
		Graphics,
		Compute,
		Transfer,
		Sparse,
		VideoDecode,
		OpticalFlow,
		Present
	};

	struct SwapChainSupportDetails 
	{
		vk::SurfaceCapabilitiesKHR capabilities;
		std::vector<vk::SurfaceFormatKHR> formats;
		std::vector<vk::PresentModeKHR> presentModes;
	};

	class Renderer : public Plum::Renderer
	{
	public:
		using QueueFamilyIndices = std::unordered_map<DeviceQueue, std::optional<uint32_t>>;

		Renderer(const std::string& appName, std::vector<const char*> externalExtensions);
		Renderer(const App::Window* windowToRenderTo);

		virtual ~Renderer() override;

		virtual void SetViewport(int x, int y, int width, int height) override;
		virtual void SetClearColor(Color clearColor) override;
		virtual void SetCullFace(bool enable) override;
		virtual void SetDepthTest(bool enable) override;
		virtual void SetProgram(ShaderProgram& program) override;
		virtual void SetUniformData(const std::string& name, const std::any& value) override;

		virtual void Clear() override;
		virtual void Render() override;

	protected:
		void InitVulkan(const std::string& appName, std::vector<const char*> externalExtensions, const App::Window* window = nullptr);
		void CleanUpVulkan();

		vk::Instance m_vulkanInstance = nullptr;

		// TODO device class
		vk::PhysicalDevice m_chosenGPU = nullptr;
		vk::Device m_device = nullptr;
		QueueFamilyIndices m_queueFamilyIndicies;
		std::unordered_map<DeviceQueue, vk::Queue> m_deviceQueues;
		std::vector<const char*> m_deviceExtensions;

		vk::SurfaceKHR m_surface = nullptr;

		// TODO: swapchain class
		vk::SwapchainKHR m_swapchain = nullptr;
		std::vector<vk::Image> m_swapchainImages;
		vk::Format m_swapchainImageFormat;
		vk::Extent2D m_swapchainExtent;

	private:
		// Instance creation
		void CreateVulkanInstance(const std::string& appName, std::vector<const char*> externalExtensions);

		// Physical device creation
		void PickGPU(bool renderToSurface);
		QueueFamilyIndices FindQueueFamilies(const vk::PhysicalDevice& device) const;
		bool CheckDeviceExtensionSupport(const vk::PhysicalDevice& device) const;
		bool CheckDeviceQueueSupport(const vk::PhysicalDevice& device, bool renderToSurface) const;
		bool IsDeviceSuitable(const vk::PhysicalDevice& device, bool renderToSurface) const;
		void GetDeviceQueueHandles();

		// Logical device creation
		void CreateVulkanDevice();

		// Swap chain creation
		void CreateSwapchain(const App::Window* window);
		SwapChainSupportDetails QuerySwapchainSupport(const vk::PhysicalDevice& device) const;
		vk::SurfaceFormatKHR ChooseSwapchainSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& availableFormats) const;
		vk::PresentModeKHR ChooseSwapchainPresentMode(const std::vector<vk::PresentModeKHR>& availablePresentModes) const;
		vk::Extent2D ChooseSwapchainExtent(const vk::SurfaceCapabilitiesKHR& capabilities, const App::Window* window) const;

		// Image view creation
		void CreateImageViews();

		// TODO: validation layers
		// TODO: rendering pipeline
	};

}

#endif