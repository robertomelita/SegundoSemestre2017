/******************************************************************************\
| OpenGL 4 Example Code.                                                       |
| Accompanies written series "Anton's OpenGL 4 Tutorials"                      |
| Email: anton at antongerdelan dot net                                        |
| First version 27 Jan 2014                                                    |
| Copyright Dr Anton Gerdelan, Trinity College Dublin, Ireland.                |
| See individual libraries for separate legal notices                          |
|******************************************************************************|
| Vertex Buffer Objects and interpolation                                      |
\******************************************************************************/
#include "gl_utils.h" // utility stuff discussed in previous tutorials is here
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include "objects.h"
#define GL_LOG_FILE "gl.log"

// keep track of window size for things like the viewport and the mouse cursor
int g_gl_width = 640;
int g_gl_height = 480;
GLFWwindow* g_window = NULL;

int main (int argc, char **argv){
	if(argc != 2){
		printf("Ejecute como ./prog n");
		return EXIT_FAILURE;
	}
	int n = atoi(argv[1]);
	srand(2); 

	restart_gl_log ();
	// all the start-up code for GLFW and GLEW is called here
	start_gl ();

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable (GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"

	int nvert = n*3;
	int nvertq = 12;

	/* OTHER STUFF GOES HERE NEXT */
	GLfloat *points = (GLfloat*)malloc(sizeof(GLfloat)*(n*3));
	for(int i = 0; i < n; i++)
	{
		points[3*i] = (float)rand()/((float)RAND_MAX/2)-1;
		points[3*i+1] = (float)rand()/((float)RAND_MAX/2)-1;
		points[3*i+2] = (float)rand()/((float)RAND_MAX/2)-1;
	}
	
	GLfloat *colours = (GLfloat*)malloc(sizeof(GLfloat)*(n*3));

	for(int i = 0; i < 3*n; i++)
	{
		colours[i]= 1.0f;
	}

    // ejercicio (1.5)
    // informacion quads
    GLfloat qpoints[] = {
        0.4f, -0.3f, 0.0f,
        0.4f, -0.5f, 0.0f,
        -0.4f, -0.5f, 0.0f,
        -0.4f, -0.3f, 0.0f
    };

    // ejercicio (1.5)
    // colores quads
    GLfloat qcolors[] = {
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f
    };

    // VBO para quads
	GLuint qvbo = genvbo(qpoints, 12);
    // vbo colores quads
	GLuint qcvbo = genvbo(qcolors, 12);

    GLuint shader_program = compile_link_shaders("vert.glsl", "frag.glsl");

	glEnable (GL_CULL_FACE); // cull face
	glCullFace (GL_BACK); // cull back face
	glFrontFace (GL_CW); // GL_CCW for counter clock-wise
    glPointSize(10.0f);

	/* create the VAO.
	we bind each VBO in turn, and call glVertexAttribPointer() to indicate where
	the memory should be fetched for vertex shader input variables 0, and 1,
	respectively. we also have to explicitly enable both 'attribute' variables.
	'attribute' is the older name for vertex shader 'in' variables. */
	GLuint vao = genvao(points, colours, 0, nvert, 0);

    // ejercicio (1.5)
    // VAO de los QUADS
	GLuint qvao = genvao(qpoints, qcolors, 0, nvertq, 0);
	
	//glPolygonMode(GL_FRONT, GL_LINE);
	while (!glfwWindowShouldClose (g_window)) {
		_update_fps_counter (g_window);
		// wipe the drawing surface clear
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport (0, 0, g_gl_width, g_gl_height);
		glUseProgram (shader_program);

        // dibujando vertices de vao 1 (triangulos)
		glBindVertexArray (vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);


        // dibujando vertices de vao 2 (un quad)
        glBindVertexArray(qvao);
		glDrawArrays(GL_QUADS, 0, 4);

		// update other events like input handling 
		glfwPollEvents ();
		if (GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose (g_window, 1);
		}
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers (g_window);
	}
	
	// close GL context and any other GLFW resources
	glfwTerminate();
    return 0;
}
