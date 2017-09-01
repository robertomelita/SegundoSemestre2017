#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "tools.h"


int main(int argc, char *argv[]) {
    if(!glfwInit()){
        fprintf(stderr, "error inicializando GLFW\n");
        exit(EXIT_FAILURE);
    }

    if(argc!=2){
        printf("Ejecute como ./prog n ,(con n > 0");
        return(EXIT_FAILURE);
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "info265", NULL, NULL);
    glfwMakeContextCurrent(window);

    glewInit();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    int n = atoi(argv[1]);
    int nvert = n+2;
    int TRI = 3;
    int nind = (n-1)*TRI;
    GLfloat *vertices = (GLfloat*)malloc(sizeof(GLfloat)*nvert*TRI+1);
    GLfloat *colors = (GLfloat*)malloc(sizeof(GLfloat)*nvert*TRI+1);
    GLuint *indices = (GLuint*)malloc(sizeof(GLuint)*nind);

    genvertices(vertices, n);
    genindices(indices , n);

   /* for(int i = 0; i < (n-1); i++){
        printf("%f,n", vertices[i]);
    }*/

	const char* vertex_shader =
	"#version 130\n"
	"in vec3 vp;"
	"void main () {"
	"	gl_Position = vec4 (vp, 1.0);"
	"}";
	/* the fragment shader colours each fragment (pixel-sized area of the
	triangle) */
	const char* fragment_shader =
	"#version 130\n"
	"out vec4 frag_colour;"
	"void main () {"
	"	frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
	"}";
	/* GL shader objects for vertex and fragment shader [components] */
	GLuint vs, fs;
	/* GL shader programme object [combined, to link] */
	GLuint shader_programme;
    
	vs = glCreateShader (GL_VERTEX_SHADER);
	glShaderSource (vs, 1, &vertex_shader, NULL);
	glCompileShader (vs);
	fs = glCreateShader (GL_FRAGMENT_SHADER);
	glShaderSource (fs, 1, &fragment_shader, NULL);
	glCompileShader (fs);
	shader_programme = glCreateProgram ();
	glAttachShader (shader_programme, fs);
	glAttachShader (shader_programme, vs);
    glLinkProgram (shader_programme);
    

    // gen and bind VAO
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

    // generar VBO de vertices
    GLuint vbo_points;
    glGenBuffers(1, &vbo_points);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_points);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*nvert*TRI, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);

    // generar EBO de los triangulos (el EBO se asocia al VAO bindeado en este instante)
    // element buffer object --> ebo
    GLuint ebo_triangles;
    glGenBuffers(1, &ebo_triangles);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_triangles);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*nind, indices, GL_STATIC_DRAW);

   

    // unbind VAOGL_UNSIGNED_INT
    glBindVertexArray(0);
    while (!glfwWindowShouldClose(window)) {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        // bind VAO
	    glUseProgram (shader_programme);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, TRI*(n), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
