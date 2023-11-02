add_subdirectory(stb)
add_subdirectory(glm)
add_subdirectory(glfw)

target_link_libraries(PlumPie glfw)
target_include_directories(PlumPie PUBLIC glfw/include)

target_link_libraries(PlumPie glm)
target_include_directories(PlumPie PUBLIC glfw/include)