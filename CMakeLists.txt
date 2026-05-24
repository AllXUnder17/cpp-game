set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_minimum_required(VERSION 3.16)
project(RaylibPixelGame CXX)

set(CMAKE_BUILD_TYPE Debug)

# 1. Force C++17 Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

# 2. DEEP SEARCH: Automatically find every .cpp file in src/ and all its subfolders
file(GLOB_RECURSE GAME_SOURCES "src/*.cpp")

# 3. Define our final game executable and hand it our auto-found source files
add_executable(${PROJECT_NAME} ${GAME_SOURCES}
   src/entities/coin.cpp)
   
# 4. Tell CMake where your Raylib Header (.h) files are
# Tell CMake where your header files are 
target_include_directories(${PROJECT_NAME} PRIVATE  
    "C:/raylib/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"   # <-- ADD THIS LINE!
) 

# 5. Tell CMake where your Raylib Library (.lib) files are
target_link_directories(${PROJECT_NAME} PRIVATE "C:/raylib/lib")

# 6. Link Raylib and standard Windows graphics/audio dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE 
    raylib 
    opengl32 
    gdi32 
    winmm
) 

# 7. Copy assets (like gun.png) to the build folder so the game can find them
# This keeps your running game from crashing due to missing textures!
# Copy the entire assets directory to your build folder automatically
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")