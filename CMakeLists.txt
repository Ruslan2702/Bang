cmake_minimum_required(VERSION 3.10)
project(Bang)

set(CMAKE_CXX_STANDARD 11)

set(BINDIR ${CMAKE_SOURCE_DIR}/bin)
MAKE_DIRECTORY(${BINDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BINDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BINDIR})

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
ExternalProject_Add(
        gtest
        URL https://github.com/google/googletest/archive/master.zip
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
        # Disable install step
        INSTALL_COMMAND ""
)
ExternalProject_Get_Property(gtest source_dir binary_dir)
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)
set_target_properties(libgtest PROPERTIES "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a" "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
        )
add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)
set_target_properties(libgmock PROPERTIES "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a" "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
        )
include_directories("${source_dir}/googletest/include" "${source_dir}/googlemock/include")

add_executable(server src/net/simple_server.cpp src/net/socket.cpp src/net/socket.hpp)
add_executable(client src/net/main_client.cpp src/net/socket.cpp src/net/socket.hpp)

