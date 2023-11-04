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
		vk::PhysicalDevice m_chosenGPU = nullptr;
		vk::Device m_device = nullptr;
		vk::SurfaceKHR m_surface = nullptr;

		QueueFamilyIndices m_queueFamilyIndicies;
		std::unordered_map<DeviceQueue, vk::Queue> m_deviceQueues;

	private:
		// To initialize vulkan
		void CreateVulkanInstance(const std::string& appName, std::vector<const char*> externalExtensions);
		void PickGPU(bool renderToSurface);
		QueueFamilyIndices FindQueueFamilies(const vk::PhysicalDevice& device) const;
		bool IsDeviceSuitable(const vk::PhysicalDevice& device, bool renderToSurface) const;
		void CreateVulkanDevice();
		void GetDeviceQueueHandles();
		void CreateSwapChain();

		// TODO: validation layers
		// TODO: rendering pipeline

		// To destroy vulkan
	};

}

#endif