cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

# ----------------------- INCLUDES ---------------------------
include(SetupVulkan)
include(SetupGLFW)
include(ExecuteReflection)
# ------------------------------------------------------------

# ---------------------- FILE ADDITION -----------------------
file(GLOB_RECURSE SUBDIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SUBDIRECTORIES})

file(GLOB_RECURSE INTERMEDIATE "${CMAKE_SOURCE_DIR}/Intermediate/*.cpp")
source_group(TREE "${CMAKE_SOURCE_DIR}/Intermediate" FILES ${INTERMEDIATE})

add_library(Runtime STATIC ${INTERMEDIATE} ${SUBDIRECTORIES})
# ------------------------------------------------------------

# ------------------- INCLUDE DIRECTORIES --------------------
target_include_directories(Runtime PRIVATE "${CMAKE_SOURCE_DIR}/Source")
target_include_directories(Runtime PUBLIC "${CMAKE_SOURCE_DIR}/Intermediate")
target_link_libraries(Runtime PUBLIC glm::glm fmt spdlog magic_enum stb assimp glfw EnTT::EnTT nlohmann_json)

DefineGlmMacros(Runtime)
AddStbMacros(Runtime)
SetupVulkan(Runtime)
SetupGLFW(Runtime)

if(WIN32)
    include(SetupWindows)
    SetupWin32(Runtime)
endif()
# ------------------------------------------------------------

# -------------------- RUNTIME REFLECTION --------------------
ExecuteReflection(Runtime "Source/Runtime" "Intermediate")
# ------------------------------------------------------------