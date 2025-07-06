cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

include(FetchContent)

# Make URL variable
if(NOT DEFINED TOML_URL)
    set(TOML_URL https://github.com/marzer/tomlplusplus.git)
endif()

# TOML Library
FetchContent_Declare(
        tomlplusplus
        EXCLUDE_FROM_ALL
        GIT_REPOSITORY ${TOML_URL}
        GIT_TAG v3.4.0
        GIT_SHALLOW TRUE
)

set(TOML_BUILD_TESTS OFF CACHE BOOL "Build toml++ tests" FORCE)
set(TOML_BUILD_EXAMPLES OFF CACHE BOOL "Build toml++ examples" FORCE)

FetchContent_MakeAvailable(tomlplusplus)