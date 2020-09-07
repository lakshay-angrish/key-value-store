add_library(
	murmur
	MurmurHash3.h
	MurmurHash3.cpp
)

target_include_directories(murmur INTERFACE "${CMAKE_CURRENT_SOURCE_DIRECTORY}")