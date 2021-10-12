cmake_minimum_required(VERSION 3.15)
project(sfml_base_widgets)

set(CMAKE_CXX_STANDARD 20)
set(SFML_USE_STATIC_STD_LIBS ON)
set(SFML_STATIC_LIBRARIES ON)

set(sfml_base_widgets_DIR ${CMAKE_CURRENT_LIST_DIR})
find_package(sfml_base_widgets REQUIRED)

add_executable(sfml_base_widgets_main main.cpp)
target_link_libraries(sfml_base_widgets_main sfml_base_widgets)
