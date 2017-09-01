/******************************************************************************\
| OpenGL 4 Example Code.                                                       |
| Accompanies written series "Anton's OpenGL 4 Tutorials"                      |
| Email: anton at antongerdelan dot net                                        |
| First version 27 Jan 2014                                                    |
| Copyright Dr Anton Gerdelan, Trinity College Dublin, Ireland.                |
| See individual libraries for separate legal notices                          |
|******************************************************************************|
| Shaders.                                                                     |
| I put some utility stuff, discussed in the previous demo into a file called  |
| gl_utils to keep this main file tidier                                       |
| I put GLFW and GLEW start-up code into a "start_GL()" function. remember to  |
| uncomment the version number code if on an Apple machine                     |
\******************************************************************************/
#include "gl_utils.h"
#include <GL/glew.h> /* include GLEW and new version of GL on Windows */
#include <GLFW/glfw3.h> /* GLFW helper library */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "tools.h"
/* #include <stdbool.h> // for visual studio i had to comment this out and
 define pure-C bool :( */
#define bool int
#define true 1
#define false 0

/* keep track of window size for things like the viewport and the mouse
 cursor */
int g_gl_width = 640;
int g_gl_height = 480;
GLFWwindow* g_window = NULL;

int main () {
    // indicadores
	GLuint vbo, vao, ebo, shader_program;
	GLint colour_loc, posv;
    // vertices e indices
	GLfloat points[] = {
		 0.0f,	0.5f,	0.0f,
		-0.5f, -0.5f,	0.0f,
		 0.5f, -0.5f,	0.0f
	};
    GLuint indices[] = {0,1,2};

    // inicializacion OpenGL
	restart_gl_log();
	start_gl();

    // compilar y linkear shaders
    shader_program = compile_link_shaders("vert.glsl", "frag.glsl" );

	/* tell GL to only draw onto a pixel if the shape is closer to the viewer*/
	glEnable (GL_DEPTH_TEST); /* enable depth-testing */
	glDepthFunc (GL_LESS); /* depth-testing interprets a smaller value as "closer" */


    // crear macro contenedor vao
	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);
        // vbo vertices 
        // crear vbo de vertices
        glGenBuffers (1, &vbo);
        glBindBuffer (GL_ARRAY_BUFFER, vbo);
        glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (GLfloat), points, GL_STATIC_DRAW);
        glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray (0);

        // ebo indices
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*3, indices, GL_STATIC_DRAW);
    glBindVertexArray(0);

    // referencia a la variable "inputColor" en el shader
	colour_loc = glGetUniformLocation (shader_program, "incolor");
	assert(colour_loc > -1);

	posv = glGetUniformLocation (shader_program, "dp");
	assert(posv > -1);

    // indicar que se usara el shader nuestro
	glUseProgram (shader_program);
    // pasar a la GPU, el valor de "inputcolor"
	float t=0.5f;
	float c,c1 = 0;
    fflush(stdout);
	while (!glfwWindowShouldClose (g_window)) {
		_update_fps_counter (g_window);
		/* wipe the drawing surface clear */
		c = 1.0f+sinf(t)/2.0f;
		c1 = 1.0f+sinf(t+2.0f)/2.0f;
		glUniform4f (colour_loc, c, c1, 0.0f, 1.0f);
		t+=0.1;
		glUniform4f (posv, t, 1.0f, 1.0f,1.0f);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport (0, 0, g_gl_width, g_gl_height);

		glUseProgram (shader_program);
		glBindVertexArray (vao);
		/* draw points 0-3 from the currently bound VAO with current in-use shader */
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		/* update other events like input handling */
		glfwPollEvents();
		if(GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_ESCAPE)){
			glfwSetWindowShouldClose (g_window, 1);
		}
		/* put the stuff we've been drawing onto the display */
		glfwSwapBuffers (g_window);
	}
	/* close GL context and any other GLFW resources */
	glfwTerminate();
	return 0;
}
