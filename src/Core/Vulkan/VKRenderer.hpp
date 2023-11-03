#ifndef PLUMPIE_VKRENDERER_HPP
#define PLUMPIE_VKRENDERER_HPP

#include <vulkan/vulkan.hpp>

#include "Core/Renderer.hpp"

namespace Plum::VK
{

	class Renderer : public Plum::Renderer
	{
	public:
		Renderer(const std::string& appName, std::vector<const char*> externalExtensions);

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
		void InitVulkan(const std::string& appName, std::vector<const char*> externalExtensions);
		void CleanUpVulkan();

		vk::Instance m_vulkanInstance = nullptr;
		vk::PhysicalDevice m_chosenGPU = nullptr;
		vk::Device m_device = nullptr;
		vk::SurfaceKHR m_surface = nullptr;

	private:
		// To initialize vulkan
		void CreateVulkanInstance(const std::string& appName, std::vector<const char*> externalExtensions);
		void GetPhysicalDevice();
		void CreateVulkanDevice();
		void CreateSwapChain();

		// TODO: validation layers
		// TODO: rendering pipeline

		// To destroy vulkan
	};

}

#endif