cmake_minimum_required(VERSION 3.16)
project(CoffeEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRE ON)

find_package(SDL2 REQUIRED)

 

add_executable(CoffeEngine 
    engine/main.cpp
    engine/core/Application.cpp
)


target_include_directories(CoffeEngine PRIVATE
    engine
    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(CoffeEngine 
    ${SDL2_LIBRARIES}
)
