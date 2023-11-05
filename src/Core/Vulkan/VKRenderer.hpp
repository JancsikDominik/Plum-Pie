#ifndef PLUMPIE_VKRENDERER_HPP
#define PLUMPIE_VKRENDERER_HPP

#include <optional>
#include <unordered_map>
#include <vulkan/vulkan.hpp>

#include "Core/Renderer.hpp"
#include "App/Window.hpp"

#include "VKDevice.hpp"

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
		Device* m_device;
		vk::SurfaceKHR m_surface = nullptr;

	private:
		void CreateVulkanInstance(const std::string& appName, std::vector<const char*> externalExtensions);
		void CreatePipeline();

		// TODO: validation layers
	};

}

#endif