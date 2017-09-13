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
    this->filename = filename;
    this->model = glm::mat4();
    this->pos = glm::vec3(0,0,0);
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
void malla::setpos(glm::vec3 pos){
    this->pos = pos;
    this->model = glm::translate(glm::mat4(),this->pos);
}
void malla::setmatloc(GLuint shaderprog, const char *name){
    this->matloc = glGetUniformLocation(shaderprog , name);
}
void model2Shader(GLuint shaderprog){
    glUseProgram (shaderprog);
    glUniformMatrix4fv(this->matloc, 1, GL_FALSE, &(this->model[0][0]));
}