CC=g++
#CC=gcc

SRC=src/*.cpp
LIBS=`pkg-config --libs freealut` -lGL -lGLEW -lglfw -lassimp -lm
EXEC=bin/prog
FLAGS=-std=c++11

all:
	${CC} ${FLAGS} ${SRC} ${LIBS} -o ${EXEC}


clear:
	rm bin/*
