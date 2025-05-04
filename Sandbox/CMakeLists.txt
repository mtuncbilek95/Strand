cmake_minimum_required(VERSION 3.20)

# ---------------------- FILE ADDITION -----------------------
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})
add_executable(Sandbox ${SOURCES})
# ------------------------------------------------------------

# ---------------------- INCLUDE DIRECTORIES ----------------
target_include_directories("Sandbox" PRIVATE "${CMAKE_SOURCE_DIR}/Source")
target_link_libraries("Sandbox" PRIVATE Runtime)

#target_link_libraries("Sandbox" PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,Runtime>")
# ------------------------------------------------------------

# ---------------------- COMPILER FLAGS ----------------------
if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()