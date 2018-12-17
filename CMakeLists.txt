cmake_minimum_required(VERSION 3.10)
project(Bang)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BINDIR ${CMAKE_SOURCE_DIR}/bin)
MAKE_DIRECTORY(${BINDIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BINDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BINDIR})
set(CMAKE_CXX_FLAGS "-lncurses")

# Добавляю новые флаги для posgreesql -L/usr/local/Cellar/postgresql/11.1/include -lpq
if(APPLE)
    set(CMAKE_CXX_FLAGS "-lncurses -L/usr/local/Cellar/postgresql/11.1/include -lpq")
endif(APPLE)

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



add_executable(server
        src/net/Server.cpp
        src/net/socket.cpp
        src/logic/GameManager.cpp
        )

add_executable(client
        src/net/Client.cpp
        src/net/main_client.cpp
        src/net/socket.cpp
        src/window/Window.cpp
        src/parsers/SituationParser.cpp
        ${INSTALL_NCURSES})

add_executable(tests_situation
        src/logic/tests/TestsForGameSituation.cpp
        src/logic/GameManager.cpp
        src/logic/GameSituation.h
        src/logic/Card.h
        src/logic/PlayerInfo.h
        )
target_link_libraries(tests_situation gtest)

add_executable(tests_parsers
        src/parsers/tests/TestsForParsers.cpp
        src/parsers/StepParser.cpp
        src/parsers/SituationParser.cpp
        src/logic/Card.h
        src/logic/Step.h
        )
target_link_libraries(tests_parsers gtest)


add_executable(test_01
        src/parsers/tests/TestsForParsers.cpp
        src/logic/Step.h
        src/logic/Card.h
        src/logic/GameSituation.h
        )
target_link_libraries(test_01 gtest)

#add_executable(db
#        src/BD/checker.cpp
#        src/BD/DataBaseManager.h
#        src/BD/DataBaseManager.cpp
#)

#add_executable(parser_dec
#        src/parsers/checker.cpp
#        src/parsers/CardsParser.cpp
#        src/parsers/CardsParser.h
#)

#add_executable(json
#        src/parsers/nlohmann.cpp)

if(APPLE)
    add_custom_command(TARGET client PRE_BUILD COMMAND cd /tmp/ &&
            curl -O ftp://ftp.gnu.org/gnu/ncurses/ncurses-6.1.tar.gz &&
            tar -xzvf ncurses-6.1.tar.gz &&
            cd ./ncurses-6.1 && ./configure && make && sudo make install)
endif(APPLE)

if(UNIX AND NOT APPLE)
    add_custom_command(TARGET client PRE_BUILD COMMAND sudo apt-get install libncurses5-dev libncursesw5-dev)
endif(UNIX AND NOT APPLE)

#find_package(Curses REQUIRED)
#include_directories(${CURSES_INCLUDE_DIR})
#target_link_libraries(client ${CURSES_LIBRARIES})
