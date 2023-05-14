# The minimum required cmake version
cmake_minimum_required(VERSION 3.16)

project(autograd VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)          # ensure cmake instructs compiler to use C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON) # ensure the C++ standard given before is actually used
set(CMAKE_CXX_EXTENSIONS OFF)       # avoid compile flags of the type -std=gnu++1z add

# Solution Folder options:
if (${CMAKE_SOURCE_DIR} STREQUAL ${PROJECT_SOURCE_DIR})
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
	set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")
endif()

include(GNUInstallDirs)
if ($ENV{VERBOSE})
	message(STATUS "CMAKE_INSTALL_INCLUDEDIR: ${CMAKE_INSTALL_INCLUDEDIR}")
	message(STATUS "CMAKE_INSTALL_DATADIR   : ${CMAKE_INSTALL_DATADIR}")
	message(STATUS "CMAKE_INSTALL_LIBDIR    : ${CMAKE_INSTALL_LIBDIR}")
	message(STATUS "CMAKE_INSTALL_DOCDIR    : ${CMAKE_INSTALL_DOCDIR}")
	message(STATUS "CMAKE_INSTALL_PREFIX    : ${CMAKE_INSTALL_PREFIX}")
endif()

# Set relative install directories
set(INSTALL_INCLUDE_DIR "${CMAKE_INSTALL_INCLUDEDIR}")
set(INSTALL_CMAKE_DIR "${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}/cmake/")

# Save all executables (unit tests & examples) in the same place:
set(EXECUTABLE_OUTPUT_PATH ${${PROJECT_NAME}_BINARY_DIR}/bin CACHE PATH "Output directory for executables")

# Define autograd lib (header-only)
add_library(autograd INTERFACE)
add_library(autograd::autograd ALIAS autograd)

# Set autograd compilation features to be propagated to client code.
target_compile_features(autograd INTERFACE cxx_std_17)

# Adding the install interface generator expression makes sure that the include
# files are installed to the proper location (provided by GNUInstallDirs)
target_include_directories(autograd
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${INSTALL_INCLUDE_DIR}>)

# Build the examples
option(AUTOGRAD_BUILD_EXAMPLES "Build examples" ON)
if(AUTOGRAD_BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()

# Build the tests
option(AUTOGRAD_BUILD_TESTS "Build tests" ON)
if(AUTOGRAD_BUILD_TESTS)
	add_subdirectory(tests)
endif()


install(TARGETS autograd
        EXPORT autogradTargets)

install(EXPORT autogradTargets
        NAMESPACE autograd::
        DESTINATION "${INSTALL_CMAKE_DIR}")

install(
	DIRECTORY "${PROJECT_SOURCE_DIR}/include/autograd"
	DESTINATION ${INSTALL_INCLUDE_DIR})