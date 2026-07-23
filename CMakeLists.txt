cmake_minimum_required(VERSION 3.16)
project(RaylibPixelGame CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

# 1. Force C++17 Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Debug flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-g)
endif()

# 2. Scan the entire src directory for all .cpp files
file(GLOB_RECURSE GAME_SOURCES "src/*.cpp")

# 3. Define the main executable
add_executable(${PROJECT_NAME} ${GAME_SOURCES})

# 4. Include paths (Project headers + Local Raylib + System Raylib fallback)
target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/raylib/include"
    "C:/raylib/include"
)

# 5. Linker library search paths
target_link_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/raylib/lib"
    "C:/raylib/lib"
)

# 6. Link Raylib and Windows graphics/audio dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE
    raylib
    opengl32
    gdi32
    winmm
)

# 7. Force standard console entry point (main)
target_link_options(${PROJECT_NAME} PRIVATE "-mconsole")

# 8. Copy assets to build directory whenever assets change
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    "${CMAKE_CURRENT_BINARY_DIR}/assets"
)