cmake_minimum_required(VERSION 3.10)
project(DataCollection)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(data_source data_source.cpp)
target_link_libraries(data_source ${Boost_LIBRARIES})

add_executable(data_center data_center.cpp)
target_link_libraries(data_center ${Boost_LIBRARIES})
