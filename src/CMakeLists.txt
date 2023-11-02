add_subdirectory(AppBase)
#add_subdirectory(Assets)
add_subdirectory(Core)
add_subdirectory(Debugging)
add_subdirectory(GLFWWrappers)
add_subdirectory(Graphics)
add_subdirectory(STBWrappers)

target_sources(PlumPie PRIVATE main.cpp)