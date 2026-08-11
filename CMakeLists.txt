cmake_minimum_required(VERSION 3.10.0)
project(evo-vision-sim VERSION 0.1.0 LANGUAGES C CXX)

add_executable(evo-vision-sim main.cpp)

target_link_libraries(evo-vision-sim PRIVATE sfml-graphics sfml-window sfml-system)
