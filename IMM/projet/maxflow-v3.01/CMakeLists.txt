PROJECT(projetImm)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(SRC
graph.cpp
maxflow.cpp
main.cpp
)
SET(HP
block.h
graph.h
)
ADD_EXECUTABLE(${PROJECT_NAME} ${SRC} ${HP})
