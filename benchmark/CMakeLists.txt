# C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

target_include_directories(
	clmLibrary
	PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
)