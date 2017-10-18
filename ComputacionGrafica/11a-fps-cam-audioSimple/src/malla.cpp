#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string>
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "tools.h"
#include "malla.h"

using namespace std;
malla::malla(char* filename){
    glm::vec3 pos = glm::vec3(0,0,0);
	this->filename = filename;
	assert(load_mesh(filename, &vao, &numvertices));
}

GLuint malla::getvao(){
    return this->vao;
}

int malla::getnumvertices(){
    return this->numvertices;
}

glm::vec3 malla::getpos(){
    return this->getpos();
}

char* malla::getfilename(){
    return this->filename;
}
