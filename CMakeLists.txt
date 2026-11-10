file(READ "${CMAKE_CURRENT_LIST_DIR}/pack.json" PACK_JSON)
string(JSON PACK_NAME GET "${PACK_JSON}" name)

foreach(_dep IN ITEMS rigImGui rigProject)
	if(NOT TARGET ${_dep})
		if(DEFINED RIGKIT_ROOT AND NOT RIGKIT_ROOT STREQUAL "")
			set(_dir "${RIGKIT_ROOT}/packs/${_dep}")
		else()
			set(_dir "${CMAKE_SOURCE_DIR}/packs/${_dep}")
		endif()
		if(EXISTS "${_dir}/CMakeLists.txt")
			add_subdirectory("${_dir}" "${CMAKE_BINARY_DIR}/packs/${_dep}")
		endif()
	endif()
endforeach()

add_library(${PACK_NAME} STATIC
	src/rigDocumentShell.cpp
	src/rigDocumentShell.h
	src/DocumentShell.cpp
	src/DocumentShell.h
	src/PagesWindow.h
	src/SkippedKeysWindow.cpp
	src/SkippedKeysWindow.h
)
target_link_libraries(${PACK_NAME} PUBLIC rigkit)
target_include_directories(${PACK_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>
)
# ImGuiPanel lives in rigImGui; CPage / pages.h live in rigProject.
foreach(_dep IN ITEMS rigImGui rigProject)
	if(TARGET ${_dep})
		target_link_libraries(${PACK_NAME} PUBLIC ${_dep})
	endif()
endforeach()
message(STATUS "Configured pack: ${PACK_NAME} (document host chrome)")
