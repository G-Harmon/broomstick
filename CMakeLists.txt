cmake_minimum_required(VERSION 3.20)
project(joby)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG  "-g")
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_VERBOSE_MAKEFILE ON)


add_library(joby
        src/simulation_pipeline.cpp
        src/aircraft_simulation_runner.cpp
        src/evotl_aircraft.cpp
        src/evotl_aircraft_builder.cpp
        src/charging_station.cpp
        src/simulation_runner.cpp
        )
target_include_directories(joby PUBLIC include)

# This first attempt did not work.
#find_package(Threads)
#target_link_libraries(joby_main ${CMAKE_THREAD_LIBS_INIT})

# you need the "-pthread" argument, not just adding the libpthread library: https://stackoverflow.com/questions/63985373/cmake-error-undefined-reference-to-pthread-create
add_link_options(-pthread)

add_executable(joby_main src/main.cpp)
target_include_directories(joby_main PUBLIC include)
target_link_libraries(joby_main joby)

add_subdirectory(test)
