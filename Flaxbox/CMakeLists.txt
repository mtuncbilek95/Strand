cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

# ---------------------- FILE ADDITION -----------------------
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})
add_executable("Flaxbox" ${SOURCES})
# ------------------------------------------------------------

# ---------------------- INCLUDE DIRECTORIES ----------------
target_include_directories("Flaxbox" PRIVATE "${CMAKE_SOURCE_DIR}/Source")
target_link_libraries("Flaxbox" PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,Runtime>")

target_link_libraries("Flaxbox" PRIVATE ftxui::screen ftxui::dom ftxui::component)
# ------------------------------------------------------------