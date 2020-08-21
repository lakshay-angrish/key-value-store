add_library(
	status
	status.h
	status.cpp
)

target_include_directories(status PUBLIC "${CMAKE_CURRENT_SOURCE_DIRECTORY}")