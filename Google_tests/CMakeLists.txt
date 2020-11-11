project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# adding the Google_Tests_run target
add_executable(Google_Tests_run ../tests1.cpp ../proj3.cpp ../proj3.hpp ../Wordset.cpp ../Wordset.hpp)

# linking Google_Tests_run with DateConverter_lib which will be tested

target_link_libraries(Google_Tests_run gtest gtest_main)
