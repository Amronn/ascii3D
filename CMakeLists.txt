cmake_minimum_required(VERSION 3.10)

project(ASCII_photo_generator LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(APP_SOURCES
    src/main.cpp
)
# Define where your source assets are
set(ASSETS_DIR ${PROJECT_SOURCE_DIR}/assets/images)

# Define where you want to copy them in the build directory
set(BUILD_ASSETS_DIR ${CMAKE_BINARY_DIR}/assets/images) # CMAKE_BINARY_DIR is the build root

# Create the target directory if it doesn't exist (optional, but good practice)
file(MAKE_DIRECTORY ${BUILD_ASSETS_DIR})

add_compile_definitions(cimg_use_jpeg)


add_executable(main ${APP_SOURCES})


target_include_directories(main PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

if(UNIX) # Linux or macOS
    find_package(X11)
    if(X11_FOUND)
        target_link_libraries(main PRIVATE ${X11_LIBRARIES})
    else()
        message(WARNING "X11 not found. CImg display functions might not work.")
    endif()

    find_package(JPEG REQUIRED) # Make sure JPEG library is found

    if(JPEG_FOUND)
        message(STATUS "JPEG library found. Linking with: ${JPEG_LIBRARIES}")
        # Use target-based linking (recommended for modern CMake)
        target_link_libraries(main PRIVATE JPEG::JPEG)
        # Fallback if target-based linking doesn't work for your libjpeg installation
        # target_link_libraries(main PRIVATE ${JPEG_LIBRARIES})
    else()
        message(FATAL_ERROR "JPEG library not found. Please install libjpeg-dev (or equivalent).")
    endif()

    # ... other find_package for JPEG, PNG, etc.
endif()
add_custom_command(
    TARGET main
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${ASSETS_DIR}
        ${BUILD_ASSETS_DIR}
    COMMENT "Copying image assets to build directory"
)