#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tools.h"


int main(int argc, char *argv[]) {
    if(!glfwInit()){
        fprintf(stderr, "error inicializando GLFW\n");
        exit(EXIT_FAILURE);
    }


    GLFWwindow* window = glfwCreateWindow(640, 480, "info265", NULL, NULL);
    glfwMakeContextCurrent(window);

    glewInit();
    int nvert = 4;
    int TRI = 3;
    int nind = 3;
    GLfloat *vertices = (GLfloat*)malloc(sizeof(GLfloat)*nvert*TRI);
    GLfloat *colors = (GLfloat*)malloc(sizeof(GLfloat)*nvert*TRI);
    GLuint *indices1 = (GLuint*)malloc(sizeof(GLuint)*nind);
    GLuint *indices2 = (GLuint*)malloc(sizeof(GLuint)*nind);

    genvertices(vertices);
    genindices(indices1);
    genindices2(indices2);

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
	GLuint vao1;
	glGenVertexArrays(1, &vao1);
	glBindVertexArray(vao1);

    // generar VBO de vertices
    GLuint vbo_points1;
    glGenBuffers(1, &vbo_points1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_points1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*nvert*TRI, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);

    // generar EBO de los triangulos (el EBO se asocia al VAO bindeado en este instante)
    // element buffer object --> ebo
    GLuint ebo_triangles1;
    glGenBuffers(1, &ebo_triangles1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_triangles1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*nind, indices1, GL_STATIC_DRAW);


    // gen and bind VAO
	GLuint vao2;
	glGenVertexArrays(1, &vao2);
	glBindVertexArray(vao2);

    // generar VBO de vertices
    GLuint vbo_points2;
    glGenBuffers(1, &vbo_points2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_points2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*nvert*TRI, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);

    // generar EBO de los triangulos (el EBO se asocia al VAO bindeado en este instante)
    // element buffer object --> ebo
    GLuint ebo_triangles2;
    glGenBuffers(1, &ebo_triangles2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_triangles2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*nind, indices2, GL_STATIC_DRAW);



    

    // unbind VAOGL_UNSIGNED_INT
    glBindVertexArray(0);
    while (!glfwWindowShouldClose(window)) {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        // bind VAO
	    glUseProgram (shader_programme);
        glBindVertexArray(vao1);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glUseProgram (shader_programme);
        glBindVertexArray(vao2);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
