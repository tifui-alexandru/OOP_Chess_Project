cmake_minimum_required(VERSION 3.14)
project(Chess)
set(SFML_ROOT "C:/Libraries/SFML-2.4.2")
# set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_MODULE_PATH "C:/Libraries/SFML-2.5.1/cmake/Modules")
find_package(SFML 2 REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp include/utils.h include/board.h src/board.cpp include/pieces.h src/pieces.cpp src/game.cpp include/game.h src/move.cpp include/move.h)
add_executable(Chess ${SOURCE_FILES})

target_link_libraries(Chess ${SFML_LIBRARIES} )