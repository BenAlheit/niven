# examples/example2/CMakeLists.txt

# Define example executables
add_executable(example2 example2.cpp)

# Link the library
target_link_libraries(example2 PRIVATE niven)
