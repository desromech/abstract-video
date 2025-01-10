# AbstractVideo cmake build script.
cmake_minimum_required(VERSION 3.5)
project(AVIDEO)

if(APPLE)
	set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
endif()

option(AVIDEO_BUILD_SAMPLES "Build AVIDEO Samples" OFF)

# Check the build type
if (CMAKE_BUILD_TYPE STREQUAL "")
	# CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
	# differentiation between debug and release builds.
	set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Output paths.
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/dist")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/;${CMAKE_MODULE_PATH}")

# Turn warnings
if (MSVC)
	# using Visual Studio C++
	#string(REGEX REPLACE "/W3" "/W4" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
	#string(REGEX REPLACE "/W3" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
	set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c11")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
endif()

if(UNIX)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()

if( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" ) 
  list( APPEND COMPILER_FLAGS -Wl,-no-undefined ) 
endif() 

# Build the thirdparty dependencies
add_subdirectory(thirdparty)

# Add some include directories
include_directories(
	.
	include
	${CMAKE_CURRENT_BINARY_DIR}/thirdparty/ffmpeg_install/include
)

link_directories(
	${CMAKE_CURRENT_BINARY_DIR}/thirdparty/ffmpeg_install/lib
)

# Set output dir.
set(MainOutputDirectory "${AVIDEO_BINARY_DIR}/dist")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MainOutputDirectory} )
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${MainOutputDirectory} )
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${MainOutputDirectory} )
foreach(Config ${CMAKE_CONFIGURATION_TYPES} )
	set(OutputDirectory "${AVIDEO_BINARY_DIR}/dist/${Config}")
    string( TOUPPER ${Config} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${OutputDirectory} )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${OutputDirectory} )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${OutputDirectory} )
endforeach()

# Samples libraries
set(AVIDEO_MAIN_LIB Avideo)
set(AVIDEO_SAMPLES_LIBS ${AVIDEO_SAMPLES_LIBS} ${SDL2_LIBRARIES} ${AVIDEO_MAIN_LIB})


# Build the implementations
add_subdirectory(implementations)

#if(AVIDEO_BUILD_SAMPLES)
	add_subdirectory(samples)
#endif()
