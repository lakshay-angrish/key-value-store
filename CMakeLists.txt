cmake_minimum_required(VERSION 3.10)

project(key-value-store VERSION 1.0 LANGUAGES CXX)

add_subdirectory(status)
add_subdirectory(db)
add_subdirectory(hash_table)
add_subdirectory(murmur_hash)
add_subdirectory(tests)