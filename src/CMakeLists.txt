# src/CMakeLists.txt

# Gather source files
set(SOURCES
    CodeBlock.cpp
    Timer.cpp
)

# Define the library target
add_library(niven ${SOURCES})

# Set include directories for the target
target_include_directories(niven
    PUBLIC
        # $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include/niven>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:include>
)

# Set target properties
set_target_properties(niven PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    OUTPUT_NAME niven
)

# Link dependencies (if any)
# target_link_libraries(my_library PRIVATE some_dependency)


# Install library
install(TARGETS niven
    EXPORT niven_targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

# Install headers
install(DIRECTORY ../include/ DESTINATION include)

# Export target for package configuration
install(EXPORT niven_targets
    FILE nivenConfig.cmake
    NAMESPACE niven::
    DESTINATION lib/cmake/niven
)
