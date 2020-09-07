add_library(
	db
	db.h
)

target_include_directories(db PUBLIC "${CMAKE_CURRENT_SOURCE_DIRECTORY}")

target_link_libraries(db status hash_table)