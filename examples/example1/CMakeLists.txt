# examples/example1/CMakeLists.txt

# Define example executables
add_executable(example1 example1.cpp)

# Link the library
target_link_libraries(example1 PRIVATE niven)
