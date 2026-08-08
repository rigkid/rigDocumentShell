file(READ "${CMAKE_CURRENT_LIST_DIR}/pack.json" PACK_JSON)
string(JSON PACK_NAME GET "${PACK_JSON}" name)

add_library(${PACK_NAME} STATIC
	src/rigDocumentShell.cpp
	src/rigDocumentShell.h
	src/DocumentShell.cpp
	src/DocumentShell.h
	src/SkippedKeysWindow.cpp
	src/SkippedKeysWindow.h
)
target_link_libraries(${PACK_NAME} PUBLIC rigkit)
target_include_directories(${PACK_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>
)
# IWindow / Mui live in rigImGui — consumers already link it; include for compile.
if(TARGET rigImGui)
	target_link_libraries(${PACK_NAME} PUBLIC rigImGui)
endif()
message(STATUS "Configured pack: ${PACK_NAME} (document host chrome)")
