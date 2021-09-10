cmake_minimum_required(VERSION 3.20)
project(joby)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG  "-g")
set(CMAKE_BUILD_TYPE Debug)

add_library(joby
        src/simulation_pipeline.cpp
        src/aircraft_simulation_runner.cpp
        src/evotl_aircraft.cpp
        src/evotl_aircraft_builder.cpp
        src/charging_station.cpp
        src/simulation_runner.cpp
        )
target_include_directories(joby PUBLIC include)

add_executable(joby_main src/main.cpp)
target_include_directories(joby_main PUBLIC include)
target_link_libraries(joby_main joby)

add_subdirectory(test)
