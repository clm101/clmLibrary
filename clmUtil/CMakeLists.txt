target_sources(
	clmLibrary
	PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/clm_err.cpp"
)

target_include_directories(
	clmLibrary
	PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
)