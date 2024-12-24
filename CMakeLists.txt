# cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

# set(TARGET niven)

# # set(CMAKE_BUILD_WITH_INSTALL_RPATH 0)
# # set(INSTALL_RPATH "/lib/intel64:/lib/intel64_win:/lib/win-x64:/home/ben/deal/deal.II-v9.6.0/lib:/home/ben/deal/libtorch/lib:/usr/lib/x86_64-linux-gnu/openmpi/lib:/home/ben/deal/trilinos-release-14-4-0/lib:/usr/local/lib:/home/ben/deal/hdf5-1.12.2/lib:/home/ben/deal/oce-OCE-0.18.3/lib:/home/ben/deal/slepc-3.18.3/lib:/home/ben/deal/petsc-3.18.6/lib:/home/ben/deal/parmetis-4.0.3/lib:/home/ben/deal/sundials-5.7.0/lib:/home/ben/deal/symengine-0.8.1/lib:/home/ben/deal/p4est-2.3.6/FAST/lib:")

# SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

#  file(GLOB_RECURSE TARGET_SRC  "src/*.cc" "src/*.cpp" "src/*.h" "src/*.hpp")
#  set(TARGET_SRC ${TARGET_SRC})

#  message(${TARGET_SRC})


# project(${TARGET})


# add_executable(${TARGET} ./src/niven.cpp)



cmake_minimum_required(VERSION 3.10)

# Project name
project(niven)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

 file(GLOB_RECURSE TARGET_SRC  "src/*.cc" "src/*.cpp" "src/*.h" "src/*.hpp")
# Source files

set(SOURCES ${TARGET_SRC})
# set(SOURCES
#     src/main.cpp
#     src/MyClass.cpp
# )

# Add the executable
add_executable(niven ${SOURCES})
