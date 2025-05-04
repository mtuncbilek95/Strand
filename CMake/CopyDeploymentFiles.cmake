cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

function(CopyShaders TARGET_NAME)
    file(GLOB SHADER_FILES
        ${CMAKE_SOURCE_DIR}/Shaders/${TARGET_NAME}/*
    )

    file(GLOB HELPER_SHADER_FILES
        ${CMAKE_SOURCE_DIR}/Shaders/Helpers/*
    )

    add_custom_command(
        TARGET ${TARGET_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory
                ${CMAKE_CURRENT_BINARY_DIR}/Shaders
        COMMAND ${CMAKE_COMMAND} -E make_directory
                ${CMAKE_CURRENT_BINARY_DIR}/Shaders/Helpers
        COMMAND ${CMAKE_COMMAND} -E copy
                ${SHADER_FILES}
                ${CMAKE_CURRENT_BINARY_DIR}/Shaders
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/Shaders/Helpers
                ${CMAKE_CURRENT_BINARY_DIR}/Shaders/Helpers
    )
endfunction()

function(CopyResources TARGET_NAME)
    add_custom_command(
        TARGET ${TARGET_NAME}
        POST_BUILD
        
        COMMAND ${CMAKE_COMMAND} -E make_directory
                ${CMAKE_CURRENT_BINARY_DIR}/Resources
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/Resources
                ${CMAKE_CURRENT_BINARY_DIR}/Resources
    )
endfunction()