#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string>
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include "maths_funcs.h"
#include "tools.h"
#include "malla.h"
#include "enemigo.h"

using namespace std;
enemigo::enemigo(char* filename) : malla(filename){
	vida = 100;
	assert(load_mesh(filename, &vao, &numvertices));
}

void enemigo::atacar(){
}

void enemigo::moverse(){
}

void enemigo::morir(){
}



// gets
int enemigo::getvida(){
    return this->vida;
}
/*
        // sets
        void setvida(int vida);
        void setvao(GLuint vao);
        void setnumvertices(int num);
        void setpos(vec3 p);
        void setfilename(char *f);
        */

