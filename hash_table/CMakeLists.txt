add_library(
	hash_table
	hash_table.h
	hash_table.cpp
)

target_include_directories(hash_table PUBLIC "${CMAKE_CURRENT_SOURCE_DIRECTORY}")

target_link_libraries(hash_table status)