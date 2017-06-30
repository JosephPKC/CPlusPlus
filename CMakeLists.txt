cmake_minimum_required(VERSION 3.6)
project(C__)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp DataStructs/Lists/LinkedList.h DataStructs/Lists/DoubleLinkedList.h DataStructs/Lists/CircularLinkedList.h DataStructs/Lists/Stack.h DataStructs/Lists/Queue.h Projects/Maze/Maze.cpp Projects/Maze/Maze.h Projects/Maze/MazeGenerator.cpp Projects/Maze/MazeGenerator.h Projects/Maze/MazeSolver.cpp Projects/Maze/MazeSolver.h)
add_executable(C__ ${SOURCE_FILES})