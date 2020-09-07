add_library(
	status
	status.h
	status.cpp
)

target_include_directories(status INTERFACE "${CMAKE_CURRENT_SOURCE_DIRECTORY}")