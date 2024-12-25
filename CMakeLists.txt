cmake_minimum_required(VERSION 3.10)

# Project name
# project(niven)
project(niven VERSION 1.0.0 LANGUAGES CXX)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
# include_directories(include)

#  file(GLOB_RECURSE TARGET_SRC  "src/*.cc" "src/*.cpp" "src/*.h" "src/*.hpp")
# # Source files

# set(SOURCES ${TARGET_SRC})
# # set(SOURCES
# #     src/main.cpp
# #     src/MyClass.cpp
# # )

# # Add the executable
# add_executable(niven ${SOURCES})

###########################
###########################
###########################

# Add the library (source files are in src/CMakeLists.txt)
add_subdirectory(src)

# Add tests and examples
# option(BUILD_TESTS "Build tests" ON)
# if (BUILD_TESTS)
#     enable_testing()
#     add_subdirectory(tests)
# endif()

option(BUILD_EXAMPLES "Build examples" ON)
if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
