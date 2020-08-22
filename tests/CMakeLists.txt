#Locate gtest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#Linking
add_executable(executeTests all_tests.cpp)
target_link_libraries(executeTests ${GTEST_LIBRARIES} pthread status db)