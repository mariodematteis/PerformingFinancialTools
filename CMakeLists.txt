cmake_minimum_required(VERSION 3.28.3)
project(PerformingFinancialTool
        VERSION 0.1
        LANGUAGES CXX
        DESCRIPTION "")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(UNIX AND NOT APPLE)
    find_program(INTEL_CXX_COMPILER icpx)

    if (INTEL_CXX_COMPILER)
        set(CMAKE_C_COMPILER icc)
        set(CMAKE_CXX_COMPILER ${INTEL_CXX_COMPILER})
    else()
        message(FATAL_ERROR "Intel C++ Compiler not found.")
    endif()
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/artifacts/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/artifacts/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/artifacts/lib)

add_subdirectory(src)