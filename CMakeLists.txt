cmake_minimum_required(VERSION 3.14)
project(Chess)
set(SFML_ROOT "C:/Libraries/SFML-2.5.1")
# set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_MODULE_PATH "C:/Libraries/SFML-2.5.1/cmake/Modules")
find_package(SFML 2 REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 17)
FILE(GLOB SOURCE_FILES main.cpp src/*.cpp include/*.h)
# set(SOURCE_FILES main.cpp include/*.h src/*.cpp include/utils.h include/board.h src/board.cpp include/pieces.h src/pieces.cpp src/game.cpp include/game.h src/move.cpp include/move.h include/about.h src/about.cpp src/game1v1.cpp src/GameMenu.cpp src/MainMenu.cpp include/game1v1.h include/GameMenu.h include/MainMenu.h include/gameFront.h src/gameFront.cpp)
add_executable(Chess ${SOURCE_FILES})

target_link_libraries(Chess ${SFML_LIBRARIES} )