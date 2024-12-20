cmake_minimum_required(VERSION 3.31)
project(NemoLib)

if(NOT CMAKE_BUILD_TYPE)
    set(default_build_type "Debug")
    message(STATUS "Set the build type to `${default_build_type}` as none was specified.")
    set(CMAKE_BUILD_TYPE ${default_build_type} CACHE STRING "Chooce the build type." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
message(STATUS "myProject Build Type: ${CMAKE_BUILD_TYPE}")

# Set the version for myProject
set(myProject_Version_Major 0)
set(myProject_Version_Minor 1)
set(myProject_Version_Patch 0)
set(myProject_Version_Status "-dev")
set(PROJECT_VERSION
    "${myProject_Version_Major}.${myProject_Version_Minor}.${myProject_Version_Patch}${myProject_Version_Status}"
)
message(STATUS "${PROJECT_NAME} version: ${PROJECT_VERSION}")

# Export setup to lsp
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
option(NEMOLIB_IMGUI "Build library with imgui" ON)

# Load files
file(GLOB LIBSOURCES "src/*.cpp")
file(GLOB IMGUISOURCES "imgui/*.cpp")
file(GLOB LIBHEADERS "include/*.hpp")
file(GLOB IMGUIHEADERS "imgui/*.h")
set(HEADERS "${LIBHEADERS};${IMGUIHEADERS};imgui/backends/imgui_impl_sdl3.h;imgui/backends/imgui_impl_sdlrenderer3.h;imgui/backends/imgui_impl_opengl3.h")
set(SOURCES "${LIBSOURCES};${IMGUISOURCES};imgui/backends/imgui_impl_sdl3.cpp;imgui/backends/imgui_impl_sdlrenderer3.cpp;imgui/backends/imgui_impl_opengl3.cpp")

# Add library
if(NEMOLIB_IMGUI)
    add_library(
        nemolib
        STATIC
        ${SOURCES}
        ${HEADERS}
    )
    set_target_properties(nemolib PROPERTIES PUBLIC_HEADER "${HEADERS}")
else()
    add_library(
        nemolib
        STATIC
        ${LIBSOURCES}
        ${HEADERS}
    )
    set_target_properties(nemolib PROPERTIES PUBLIC_HEADER "${LIBHEADERS}")
endif()

target_include_directories(
    nemolib
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${PROJECT_SOURCE_DIR}/imgui
    PUBLIC ${PROJECT_SOURCE_DIR}/imgui/backends
)
install(
    TARGETS nemolib
    EXPORT nemolib
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include/nemolib
)
