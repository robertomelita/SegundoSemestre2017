#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string>
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include "maths_funcs.h"
#include "tools.h"
#include "malla.h"
#include "esfera.h"

#define eps 0.001
#define tMax 2
#define wh 6.0

esfera::esfera(int slices,int stacks, float radius, GLuint shaderprog){
    this->slices  = slices;
    this->stacks = stacks;
    this->radius = radius;
	set_matloc(glGetUniformLocation (shaderprog, "obj"));
    reset_matrix();
    generate();
    printf("esfera    %i   %i   %f\n", this->stacks, this->slices, this->radius);
}

void esfera::render(){
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(get_vao());
    glBindTexture(GL_TEXTURE_2D, tex);
    glPointSize(3.0);
    //print(get_matrix());
	glUniformMatrix4fv(get_matloc(), 1, GL_FALSE, get_matrix().m);
    glDrawElements(get_facetype(), get_facefactor()*get_numfaces(), GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_POINTS, 0, get_numvertices());
    glPointSize(1.0);
    glBindVertexArray(0);
}

void esfera::generate(){
    int i,j,nsl;
    float delsl,delst,x,y,z;
    delsl=2*M_PI/slices;
    nsl=slices+1;
    delst=(M_PI-2*eps*radius)/stacks;
    vec3 *vertices  = (vec3*)malloc(nsl*stacks*sizeof(vec3));
    vec3 *normals   = (vec3*)malloc(nsl*stacks*sizeof(vec3));
    vec2 *texcoords = (vec2*)malloc(nsl*stacks*sizeof(vec2));

    set_facetype(GL_QUADS);
    set_facefactor(QUAD_FACTOR);
    int *indices = (int*)malloc(get_facefactor()*slices*(stacks-1)*sizeof(int));

    int count = 0;
    for (j=0;j<stacks;j++){
        for (i=0;i<nsl;i++){
            // sphere coordinates
            x=radius*sin(delst*j+eps)*cos(i*delsl);
            y=radius*cos(delst*j+eps);
            z=radius*sin(delst*j+eps)*sin(i*delsl);
            //printf("xyz  %f   %f   %f\n", x, y, z);

            // vertices, normals, texcoords
            vertices[nsl*j+i]=vec3(x, y, z);
            normals[nsl*j+i]=vec3(x,y,z);

            texcoords[nsl*j+i]=vec2(((float ) nsl-1-i)/(nsl-1),1.0f- ((float ) j)/(stacks-1));
            //printf("texcoord[%i] = %f    %f\n", nsl*j+i, texcoords[nsl*j+i].v[0], texcoords[nsl*j+i].v[1]);

            // indices
            if ((j < stacks-1) && (i < slices)){
                indices[4*slices*j+4*i]   = nsl*j+i+1;
                indices[4*slices*j+4*i+1] = nsl*j+i;
                indices[4*slices*j+4*i+2] = nsl*(j+1)+i;
                indices[4*slices*j+4*i+3] = nsl*(j+1)+i+1;
                count++;
            }
        }
    }
    set_numfaces(count);
    set_numvertices(nsl*stacks);
    printf("numvertices  %i     numfaces %i\n", get_numvertices(), get_numfaces());
    makevao(vertices, normals, texcoords, indices);
}
