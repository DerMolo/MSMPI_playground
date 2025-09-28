cmake_minimum_required(VERSION 3.21)
project(MSMPI_playground LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Path to your local vcpkg_installed folder
set(VCPKG_INSTALLED "${CMAKE_SOURCE_DIR}/vcpkg_installed/x64-windows")

find_path(MSMPI_INCLUDE_DIR mpi.h
  PATHS "${VCPKG_INSTALLED}/include")

find_library(MSMPI_LIBRARY msmpi
  PATHS "${VCPKG_INSTALLED}/lib")

if (NOT MSMPI_INCLUDE_DIR)
  message(FATAL_ERROR "Could not find mpi.h. Looked in ${VCPKG_INSTALLED}/include")
endif()

if (NOT MSMPI_LIBRARY)
  message(FATAL_ERROR "Could not find msmpi.lib. Looked in ${VCPKG_INSTALLED}/lib")
endif()

include_directories(
    ${CMAKE_SOURCE_DIR}/vcpkg_installed/x64-windows/include
)
link_directories(
    ${CMAKE_SOURCE_DIR}/vcpkg_installed/x64-windows/lib
)

add_executable(msmpitest msMPITest.cpp)
target_include_directories(msmpitest PRIVATE ${MSMPI_INCLUDE_DIR})
target_link_libraries(msmpitest PRIVATE ${MSMPI_LIBRARY})
