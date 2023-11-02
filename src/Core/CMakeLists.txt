add_subdirectory(EventSystem)
add_subdirectory(Vulkan)

target_sources(PlumPie PRIVATE 
	Renderer.hpp 
	Shader.hpp
	ShaderProgram.hpp
	Texture.hpp
	Formats.hpp
)