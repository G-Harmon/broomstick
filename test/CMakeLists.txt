cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG  "-g")

include(FetchContent)
#set(FETCHCONTENT_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        703bd9caab50b139428cea1aaff9974ebee5742e # release-1.10.0
)
#FetchContent_Declare(
#        googletest
#        # Specify the commit you depend on and update it regularly.
#        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
#        SOURCE_DIR ${CMAKE_BINARY_DIR}/googletest
#)
#FetchContent_Populate(googletest
#        SUBBUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/subbuild
#        BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/build
#)

FetchContent_MakeAvailable(googletest)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()
#add_subdirectory(${CMAKE_BINARY_DIR}/googletest)

include(GoogleTest)
#find_package(GTest CONFIG REQUIRED)
add_executable(
        tests
        test_evotl_aircraft_builder_test.cpp
)
target_link_libraries(tests joby gtest gmock gtest_main)
target_include_directories(tests PUBLIC include)

gtest_discover_tests(tests WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
