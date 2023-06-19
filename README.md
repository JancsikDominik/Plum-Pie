# Plum pie
Plum pie is OpenGL rendering engine made by a rookie. My first ever 'big' rendering project.
Currently the it only works on windows 10 and 11.
In the future I might make it multi-platform, and/or support Vulkan/DirectX alongside OpenGL.

Beware theat the project is WORK IN PROGRESS, and very bare bones right now.

## Dependencies
GLEW , GLFW, GLM, (ImGui in the future)

## Usage
Clone/download the repo, and you should be good to go. You can compile it using Visual studio. Dependencies are included in the ```./ext``` folder, so It should just compile when you download it. You should keep your shaders in the ```src/Shaders``` folder, there is a post-compile step, which copies the contents of the Shader folder next to the .exe (e.g. ```bin/x64/Debug/Shaders```), so you can access your shaders in the code with a relative path.
