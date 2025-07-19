cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

# ----------------------- INCLUDES ---------------------------
if(DEFINED ENV{QT_DIR})
    list(APPEND CMAKE_PREFIX_PATH $ENV{QT_DIR})
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)
include(HandleQT)

qt_standard_project_setup()
# ------------------------------------------------------------

# ----------------------- QT ADDITION ------------------------
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTORCC_OPTIONS "--compress" "9")
# ------------------------------------------------------------

# ---------------------- QT RESOURCES ------------------------
set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}/Resources/Editor/EditorResource.qrc")
# ------------------------------------------------------------

# ----------------------- PROJECT NAME -----------------------
file(GLOB_RECURSE SUBDIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp" 
	"${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.qrc" "${CMAKE_CURRENT_SOURCE_DIR}/*.qml" "${CMAKE_CURRENT_SOURCE_DIR}/*.moc")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SUBDIRECTORIES})

qt_add_executable(Editor ${SUBDIRECTORIES} ${RESOURCE_DIR})
# ------------------------------------------------------------

# ------------------- INCLUDE DIRECTORIES --------------------
target_include_directories(Editor PRIVATE "${CMAKE_SOURCE_DIR}/Source")

target_link_libraries(Editor
    PUBLIC
        Qt::Core
        Qt::Widgets
)

target_link_libraries(Editor PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,Runtime>")
target_precompile_headers(Editor PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Core/PCH.h")
# ------------------------------------------------------------

# ---------------------- FILE ADDITION -----------------------
add_custom_command(
    TARGET Editor POST_BUILD
    COMMAND $ENV{QT_DIR}/bin/windeployqt.exe
    "\"$<TARGET_FILE:Editor>\""
)
# ------------------------------------------------------------