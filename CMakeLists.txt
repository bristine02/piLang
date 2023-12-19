cmake_minimum_required(VERSION 3.10)

project(piLang)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_COMPILER "g++")

# Add your source files here
set(SOURCES
    main.cpp
    lib_symbol.cpp
    lexer.cpp
)

# Executable
add_executable(main ${SOURCES})

# Include directories
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Set compiler flags
# target_compile_options(main PRIVATE -Wall -Wextra -Werror)
# Set default compile flags for GCC
if(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "GCC detected, adding compile flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Wall -Wextra")
endif(CMAKE_COMPILER_IS_GNUCXX)

# Clean-up target
add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/Debug
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/Release
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_CURRENT_BINARY_DIR}/main
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Add clean_all as a dependency for the "clean" target
add_custom_target(cleanup DEPENDS clean_all)
