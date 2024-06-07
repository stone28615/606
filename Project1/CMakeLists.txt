cmake_minimum_required(VERSION 3.10)
project(DataCollection)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(data_source data_source.cpp)
target_link_libraries(data_source ${Boost_LIBRARIES})

find_package(SQLite3 REQUIRED)
include_directories(${SQLite3_INCLUDE_DIRS})

add_executable(data_center data_center.cpp)
target_link_libraries(data_center ${Boost_LIBRARIES} ${SQLite3_LIBRARIES})

# Add a custom target to create the log directory
add_custom_target(create_log_directory
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/log
)

# Ensure log directory is created before building executables
add_dependencies(data_center create_log_directory)
add_dependencies(data_source create_log_directory)

