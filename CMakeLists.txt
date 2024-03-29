#=============================================
#				Project setup
#=============================================

cmake_minimum_required(VERSION 3.6)

project(PlumPie
        DESCRIPTION "Vulkan rendering framework"
        LANGUAGES CXX C
)

# Setting output dir to ../Bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../Bin)

# Enable folders (for Visual Studio).
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Adding the dll
add_executable(PlumPie)

# Using c++20
target_compile_features(PlumPie PUBLIC cxx_std_20)

cmake_policy(SET CMP0076 NEW)
cmake_policy(SET CMP0079 NEW)


#=============================================
#				Main source
#=============================================

# I'll only ever have one target in this project (the dll), so I'll set up everyting here
# no need for custom functions
add_subdirectory(src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
get_target_property(target_source_dir PlumPie SOURCE_DIR)
get_target_property(target_sources_ PlumPie SOURCES)
source_group(TREE ./ FILES ${target_sources_} PREFIX "")


#=============================================
#				Dependencies
#=============================================

add_subdirectory(ext)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ext)
get_target_property(target_source_dir PlumPie SOURCE_DIR)
get_target_property(target_sources_ PlumPie SOURCES)
source_group(TREE ./ FILES ${target_sources_} PREFIX "")

# GLFW stuff
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Vulkan stuff
find_package(Vulkan REQUIRED)
target_link_libraries(PlumPie PRIVATE Vulkan::Vulkan)
target_include_directories(PlumPie PRIVATE ${Vulkan_INCLUDE_DIRS}) 

#=============================================
#			Preprocessor definitions
#=============================================

target_compile_definitions(PlumPie
    PUBLIC
    $<$<CONFIG:Debug>:PLUM_DEBUG>
)