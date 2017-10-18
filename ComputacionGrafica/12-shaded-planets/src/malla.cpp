#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string>
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include "maths_funcs.h"
#include "tools.h"
#include "malla.h"
#include "stb_image.h"

using namespace std;
malla::malla(char* filename){
	vec3 pos = vec3(0,0,0);
	this->filename = filename;
	assert(load_mesh(filename, &vao, &nvertices));
}

malla::malla(){
	vec3 pos = vec3(0,0,0);
}

// gets
GLuint malla::get_vao(){
    return this->vao;
}

int malla::get_numvertices(){
    return this->nvertices;
}

int malla::get_numfaces(){
    return this->nfaces;
}

vec3 malla::get_pos(){
    return this->pos;
}

char* malla::get_filename(){
    return this->filename;
}

GLuint malla::get_facetype(){
    return this->FTYPE;
}

GLuint malla::get_facefactor(){
    return this->FFACTOR;
}

void malla::set_pos(vec3 p){
    this->pos = p;
}

mat4 malla::get_matrix(){
    return this->M;
}

int malla::get_matloc(){
    return this->matloc;
}





// sets

void malla::set_numvertices(int nvertices){
    this->nvertices = nvertices;
}

void malla::set_numfaces(int nfaces){
    this->nfaces = nfaces;
}

void malla::set_facetype(GLuint FTYPE){
    this->FTYPE = FTYPE;
}

void malla::set_facefactor(GLuint FFACTOR){
    this->FFACTOR = FFACTOR;
}

void malla::set_matrix(mat4 M){
    this->M = M;
}

void malla::set_matloc(int matloc){
    this->matloc = matloc;
}



// functions
void malla::reset_matrix(){
    this->M = identity_mat4();
}

void malla::print_matrix(){
    print(this->M);
}

void malla::mtranslate(vec3 d){
    this->M = translate(get_matrix(), d); 
}

void malla::mrotatey(float d){
    this->M = rotate_y_deg(get_matrix(), d); 
}

void malla::makevao(vec3 *vertices, vec3* normals, vec2 *texcoords, int *indices){
        glGenVertexArrays (1, &vao);
        glBindVertexArray (vao);

            glGenBuffers (1, &vbo);
            glBindBuffer (GL_ARRAY_BUFFER, vbo);
            glBufferData ( GL_ARRAY_BUFFER, 3 * nvertices * sizeof (GLfloat), vertices, GL_STATIC_DRAW);
            glGenBuffers(1, &ebo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*get_numfaces()*get_facefactor(), indices, GL_STATIC_DRAW);
            glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            glEnableVertexAttribArray (0);

            glGenBuffers (1, &nbo);
            glBindBuffer (GL_ARRAY_BUFFER, nbo);
            glBufferData ( GL_ARRAY_BUFFER, 3 * nvertices * sizeof (GLfloat), normals, GL_STATIC_DRAW);
            glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            glEnableVertexAttribArray (1);

            
            glGenBuffers (1, &tbo);
            glBindBuffer (GL_ARRAY_BUFFER, tbo);
            glBufferData ( GL_ARRAY_BUFFER, 2 * nvertices * sizeof (GLfloat), texcoords, GL_STATIC_DRAW);
            glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
            glEnableVertexAttribArray (2);

            
        glBindVertexArray(0);
        
}

bool malla::load_texture (const char* file_name) {
	int x, y, n;
	int force_channels = 4;
	unsigned char* image_data = stbi_load (file_name, &x, &y, &n, force_channels);
    //printf("x = %i    y = %i\n", x, y);
	if (!image_data) {
		fprintf (stderr, "ERROR: could not load %s\n", file_name);
		return false;
	}
	// NPOT check
	if ((x & (x - 1)) != 0 || (y & (y - 1)) != 0) {
		fprintf (
			stderr, "WARNING: texture %s is not power-of-2 dimensions\n", file_name
		);
	}
	int width_in_bytes = x * 4;
	unsigned char *top = NULL;
	unsigned char *bottom = NULL;
	unsigned char temp = 0;
	int half_height = y / 2;

	for (int row = 0; row < half_height; row++) {
		top = image_data + row * width_in_bytes;
		bottom = image_data + (y - row - 1) * width_in_bytes;
		for (int col = 0; col < width_in_bytes; col++) {
			temp = *top;
			*top = *bottom;
			*bottom = temp;
			top++;
			bottom++;
		}
	}
	glGenTextures (1, &tex);
	glActiveTexture (GL_TEXTURE0);
	glBindTexture (GL_TEXTURE_2D, tex);
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	glGenerateMipmap (GL_TEXTURE_2D);
    // probar cambiar GL_CLAMP_TO_EDGE por GL_REPEAT
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	GLfloat max_aniso = 16.0f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_aniso);
	// set the maximum!
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_aniso);
	return true;
}
