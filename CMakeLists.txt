cmake_minimum_required(VERSION 3.16)
project(CoffeeEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Executável ---
add_executable(CoffeeEngine 
    engine/main.cpp
    engine/core/Application.cpp
    engine/render/Renderer2D.cpp
    engine/input/InputSystem.cpp
    engine/core/Log.cpp
)

# --- Include engine ---
target_include_directories(CoffeeEngine PRIVATE engine)

# --- SDL2 ---
find_package(SDL2 REQUIRED)
target_include_directories(CoffeeEngine PRIVATE ${SDL2_INCLUDE_DIRS})

# --- SDL2_image ---
if(APPLE)
    # Homebrew paths Mac M1
    target_include_directories(CoffeeEngine PRIVATE /opt/homebrew/include/SDL2)
    target_link_libraries(CoffeeEngine PRIVATE ${SDL2_LIBRARIES} /opt/homebrew/lib/libSDL2_image.dylib)
else()
    # Linux / Windows
    find_package(SDL2_image REQUIRED)
    target_include_directories(CoffeeEngine PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})
    target_link_libraries(CoffeeEngine PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
endif()
