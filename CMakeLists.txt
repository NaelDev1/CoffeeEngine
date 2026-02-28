cmake_minimum_required(VERSION 3.16)
project(CoffeeEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Executável ---
add_executable(CoffeeEngine 
    engine/main.cpp
    engine/core/Application.cpp
    engine/core/LayerStack.cpp
    engine/core/Timer.cpp
    engine/core/Window.cpp
    engine/core/Camera.cpp
    engine/render/Renderer2D.cpp
    engine/input/InputSystem.cpp
    engine/core/Log.cpp
)

# --- Include engine ---
target_include_directories(CoffeeEngine PRIVATE engine)

# --- SDL2 ---
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

if(APPLE)
    # Homebrew paths Mac M1
    target_include_directories(CoffeeEngine PRIVATE /opt/homebrew/include/SDL2)
    target_link_libraries(CoffeeEngine PRIVATE 
        ${SDL2_LIBRARIES}
        /opt/homebrew/lib/libSDL2_image.dylib
        /opt/homebrew/lib/libSDL2_ttf.dylib
    )
elseif(UNIX AND NOT APPLE)  # Linux
    target_include_directories(CoffeeEngine PRIVATE 
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
    )
    target_link_libraries(CoffeeEngine PRIVATE 
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
    )
else()  # Windows
    # Adicione aqui se precisar
endif()