cmake_minimum_required(VERSION 3.16)
project(CoffeeEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC OFF)  # Não precisamos de Qt

# --- Encontrar pacotes com pkg-config ---
find_package(PkgConfig REQUIRED)

# Verificar e obter todas as informações das bibliotecas
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf>=2.0.0)

# --- Incluir diretórios para todas as bibliotecas ---
include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
)

# --- Adicionar definições de compilação (se houver) ---
add_definitions(
    ${SDL2_CFLAGS_OTHER}
    ${SDL2_IMAGE_CFLAGS_OTHER}
    ${SDL2_TTF_CFLAGS_OTHER}
)

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

# --- Incluir diretórios do engine ---
target_include_directories(CoffeeEngine PRIVATE engine)

# --- Linkar bibliotecas (funciona em Linux e Mac) ---
target_link_libraries(CoffeeEngine PRIVATE
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_LDFLAGS_OTHER}
    ${SDL2_IMAGE_LDFLAGS_OTHER}
    ${SDL2_TTF_LDFLAGS_OTHER}
)

# --- Configurações específicas para Mac (se necessário) ---
if(APPLE)
    # No Mac, às vezes precisamos adicionar frameworks
    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    find_library(IOKIT_LIBRARY IOKit REQUIRED)
    find_library(COREVIDEO_LIBRARY CoreVideo REQUIRED)
    
    target_link_libraries(CoffeeEngine PRIVATE
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${COREVIDEO_LIBRARY}
    )
endif()

# --- Mensagens de diagnóstico ---
message(STATUS "SDL2 encontrado: ${SDL2_FOUND}")
message(STATUS "SDL2_image encontrado: ${SDL2_IMAGE_FOUND}")
message(STATUS "SDL2_ttf encontrado: ${SDL2_TTF_FOUND}")
message(STATUS "SDL2 inclui: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2 bibliotecas: ${SDL2_LIBRARIES}")