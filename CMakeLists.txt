cmake_minimum_required(VERSION 2.6)

#Locate gtest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#Linking
add_executable(executeTests status_test.cpp)
target_link_libraries(executeTests ${GTEST_LIBRARIES} pthread)