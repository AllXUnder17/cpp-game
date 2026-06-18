set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_minimum_required(VERSION 3.16)
project(RaylibPixelGame CXX)

# Back to normal debug configurations
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-g)
endif()

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# 1. Force C++17 Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
 
# 2. FIXED DEEP SEARCH: Scan the entire src directory for any and all .cpp files
file(GLOB_RECURSE GAME_SOURCES "src/*.cpp")

# 3. Define our final game executable using all scanned source files
add_executable(${PROJECT_NAME} ${GAME_SOURCES})  
   
# 4. Tell CMake where your header (.h) files are 
target_include_directories(${PROJECT_NAME} PRIVATE  
    "C:/raylib/include" 
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)   

# 5. Tell CMake where your Raylib Library (.lib / .a) files are
target_link_directories(${PROJECT_NAME} PRIVATE "C:/raylib/lib")

# 6. Link Raylib and standard Windows system graphics/audio dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE 
    raylib 
    opengl32  
    gdi32 
    winmm
) 

# 7. FIXED WINMAIN LINKER BUG: Forces MinGW to look for standard int main() 
target_link_options(${PROJECT_NAME} PRIVATE "-mconsole")

# 8. Copy assets directory to your build folder automatically
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")