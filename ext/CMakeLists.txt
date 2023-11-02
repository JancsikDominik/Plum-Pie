add_subdirectory(stb)
add_subdirectory(glm)
add_subdirectory(glfw)

target_link_libraries(PlumPie PRIVATE glfw)
target_include_directories(PlumPie PUBLIC glfw/include)
target_link_directories(PlumPie PUBLIC glfw/src)

target_link_libraries(PlumPie PRIVATE glm)
target_include_directories(PlumPie PUBLIC glm)