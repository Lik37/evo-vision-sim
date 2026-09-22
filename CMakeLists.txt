cmake_minimum_required(VERSION 3.15)
project(evo-vision-sim VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_executable(evo-vision-sim main.cpp)

target_link_libraries(evo-vision-sim PRIVATE SFML::Graphics SFML::Window SFML::System)

if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/assets")
    file(CREATE_LINK 
        "${CMAKE_CURRENT_SOURCE_DIR}/assets" 
        "${CMAKE_CURRENT_BINARY_DIR}/assets" 
        SYMBOLIC)
endif()
