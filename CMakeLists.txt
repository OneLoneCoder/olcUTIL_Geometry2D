# require version 3.10 or higher
cmake_minimum_required(VERSION 3.10)

#
# Project
#
#   - dictates the output executable filename
#
project(olcUTIL_Geometry2D)

# detect emscripten environment
if (${CMAKE_CXX_COMPILER} MATCHES ".*em[+][+]")
    set(EMSCRIPTEN TRUE)
else()
    set(EMSCRIPTEN FALSE)
endif()

# Set C++ Standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# output html for emscripten
if (EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX .html)
endif (EMSCRIPTEN)

# Directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Source Files are Curated Here
# Source Files are Curated Here
file( GLOB APP_SOURCES ${CMAKE_SOURCE_DIR}/*.cpp )

foreach( testSourceFile ${APP_SOURCES} )

    get_filename_component( testName ${testSourceFile} NAME_WE )
    add_executable( ${testName} ${testSourceFile} )

    # OpenGL
    if (NOT EMSCRIPTEN)
        set(OpenGL_GL_PREFERENCE LEGACY)
        find_package(OpenGL REQUIRED)
        include_directories(${OpenGL_INCLUDE_DIRS})
        target_link_libraries(${testName} ${OpenGL_LIBRARIES} OpenGL::GL)
    endif (NOT EMSCRIPTEN)

    # Apple Specifics
    if (APPLE AND NOT EMSCRIPTEN)

        # Carbon
        FIND_LIBRARY(CARBON_LIBRARY Carbon)
        target_link_libraries(${testName} ${CARBON_LIBRARY})

        # GLUT
        find_package(GLUT REQUIRED)
        target_link_libraries(${testName} ${GLUT_LIBRARIES})

    endif (APPLE AND NOT EMSCRIPTEN)
        
    # Linux Specifics
    if (UNIX AND NOT APPLE AND NOT EMSCRIPTEN)

        # X11
        find_package(X11 REQUIRED)
        target_link_libraries(${testName} ${X11_LIBRARIES})

        include_directories(${X11_INCLUDE_DIRS})

    endif (UNIX AND NOT APPLE AND NOT EMSCRIPTEN)

    # UNIX or UNIX-like (Linux, MacOS, MSYS2, Cygwin, etc)
    if (UNIX)
        
        # Threads
        if (NOT EMSCRIPTEN)
            find_package(Threads REQUIRED)
            target_link_libraries(${testName} ${Threads_LIBRARIES})
            
            include_directories(${Threads_INCLUDE_DIRS})
        endif (NOT EMSCRIPTEN)
        
        # PNG
        if (EMSCRIPTEN)
            execute_process(COMMAND embuilder build libpng OUTPUT_QUIET)
            execute_process(COMMAND embuilder build zlib OUTPUT_QUIET)
        endif (EMSCRIPTEN)
        
        find_package(PNG REQUIRED)
        target_link_libraries(${testName} ${PNG_LIBRARIES})
        include_directories(${PNG_INCLUDE_DIRS})

        set_target_properties(${testName} PROPERTIES COMPILE_FLAGS "-ggdb3 -Og")
        
    endif (UNIX)

    # Windows Specifics
    if (WIN32 AND NOT EMSCRIPTEN)
        
        # We need to specify the output for each configuration to make it work
        # on Visual Studio solutions.
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib")
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib")
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin")
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/lib")
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/lib")
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/bin")
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib")
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib")
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin")
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_PROFILE "${CMAKE_BINARY_DIR}/lib")
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_PROFILE "${CMAKE_BINARY_DIR}/lib")
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_PROFILE "${CMAKE_BINARY_DIR}/bin")

        if (MSVC)
            # set the startup project to the target executable instead of ALL_BUILD
            set_property(
                DIRECTORY
                ${CMAKE_CURRENT_SOURCE_DIR}
                PROPERTY
                VS_STARTUP_PROJECT
                ${testName}
            )
            
            # set working directory for Visual Studio Debugger
            set_target_properties(
                ${testName} PROPERTIES
                VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
            )
            
        endif (MSVC)
        
        # GDI+
        set(GDIPLUS_LIBRARY gdiplus)
        target_link_libraries(${testName} ${GDIPLUS_LIBRARY})
        
        # Shlwapi
        set(SHLWAPI_LIBRARY shlwapi)
        target_link_libraries(${testName} ${SHLWAPI_LIBRARY})
        
        # Dwmapi
        set(DWMAPI_LIBRARY dwmapi)
        target_link_libraries(${testName} ${DWMAPI_LIBRARY})

    endif (WIN32 AND NOT EMSCRIPTEN)

    # Emscripten specifics
    if (EMSCRIPTEN)
        target_link_options(
            ${testName}
            PRIVATE
            -sALLOW_MEMORY_GROWTH=1
            -sMAX_WEBGL_VERSION=2
            -sMIN_WEBGL_VERSION=2
            -sUSE_LIBPNG=1)
    endif (EMSCRIPTEN)


    # Not on Mac; Not with MSVC; Not with Emscripten
    if (NOT APPLE AND NOT MSVC AND NOT EMSCRIPTEN)
        
        # C++ Filesystem
        target_link_libraries(${testName} stdc++fs)

    endif (NOT APPLE AND NOT MSVC AND NOT EMSCRIPTEN)

endforeach()


# set include directory
if (EXISTS "${CMAKE_SOURCE_DIR}/${C_CXX_HEADERS_DIR}" AND IS_DIRECTORY "${CMAKE_SOURCE_DIR}/${C_CXX_HEADERS_DIR}")
    include_directories("${CMAKE_SOURCE_DIR}/${C_CXX_HEADERS_DIR}")
endif (EXISTS "${CMAKE_SOURCE_DIR}/${C_CXX_HEADERS_DIR}" AND IS_DIRECTORY "${CMAKE_SOURCE_DIR}/${C_CXX_HEADERS_DIR}")

include_directories("${CMAKE_SOURCE_DIR}/third_party")


# Define an option to enable/disable unit tests
option(ENABLE_GEOM2D_UNIT_TESTS "Enable unit tests for /olcUTIL_Geometry2D" OFF)

# unit tests
# I use this with cmake -G Ninja -DBUILD_GMOCK=OFF -DINSTALL_GTEST=OFF -DENABLE_GEOM2D_UNIT_TESTS=ON ..
if(ENABLE_GEOM2D_UNIT_TESTS)
    enable_testing()

    # Code Coverage
    set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/cmake")
    include(coverage)
    add_coverage_target("*/tests/*")

    # Fetch Google Test
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git 
        GIT_TAG v1.14.0
    )
    FetchContent_MakeAvailable(googletest)

    add_executable(unit_tests 
        tests/test_circle.cpp # TODO: use cmake to find all test files
    )

    # Disable optimization for coverage
    # TODO: only tested with gcc
    target_compile_options(unit_tests PRIVATE 
        -O0 -fprofile-arcs -ftest-coverage --coverage
    )
    target_link_options(unit_tests PRIVATE --coverage)  

    target_link_libraries(unit_tests gtest_main)

    add_test(NAME unit_tests COMMAND unit_tests)
endif()
