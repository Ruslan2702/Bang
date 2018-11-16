cmake_minimum_required(VERSION 3.10)
project(Bang)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BINDIR ${CMAKE_SOURCE_DIR}/bin)
MAKE_DIRECTORY(${BINDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BINDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BINDIR})
set(CMAKE_CXX_FLAGS "-lncurses")



#set(INSTALL_NCURSES ${CMAKE_CURRENT_BINARY_DIR} )
#add_custom_command(OUTPUT ${INSTALL_NCURSES} COMMAND sudo apt-get install libncurses5-dev libncursesw5-dev)
#add_custom_target("install_lib")
#add_custom_command(TARGET "deploy" POST_BUILD <some command>)


# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif()

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(tests tests/first_test.cpp)
target_link_libraries(tests gtest_main)

add_executable(server src/net/Server.cpp src/net/socket.cpp src/net/socket.hpp src/net/Server.h)
add_executable(client src/net/Client.cpp src/net/main_client.cpp src/net/socket.cpp src/window/Window.cpp ${INSTALL_NCURSES})

if(UNIX AND NOT APPLE)
    add_custom_command(TARGET client PRE_BUILD COMMAND sudo apt-get install libncurses5-dev libncursesw5-dev)
endif(UNIX AND NOT APPLE)

if(APPLE)
    add_custom_command(TARGET client PRE_BUILD COMMAND brew install libncurses5-dev libncursesw5-dev)
endif()


target_link_libraries(client ncurses)
target_link_libraries(tests gtest_main)

