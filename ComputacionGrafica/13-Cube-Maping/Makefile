BIN = bin/cubemap
CC = g++
FLAGS = -Wall -pedantic
INC = -I ../common/include
LIBS = -lGL -lX11 -lXxf86vm -lXrandr -lpthread -lXi -lz -lGLEW -lglfw -lassimp
SRC = main.cpp maths_funcs.cpp gl_utils.cpp stb_image.c obj_parser.cpp

all:
	${CC} ${FLAGS} ${SRC} ${INC} ${LIBS} -o ${BIN}

clear:
	rm bin/*
