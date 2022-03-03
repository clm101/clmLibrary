#add_subdirectory("clmMath")
#add_subdirectory("clmUtil")
cmake_minimum_required(VERSION 3.21)
project(clmLibrary)

set(MSVC_TOOLSET_VERSION 143)

# C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(clmLibrary)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/clmMath")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/clmUtil")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/benchmark")

find_package(Vulkan MODULE REQUIRED)

target_include_directories(
	clmLibrary
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
	${Vulkan_INCLUDE_DIR}
)
target_link_libraries(
	clmLibrary
	PRIVATE
	${Vulkan_LIBRARY}
)