#include "gl_utils.h" // utility functions discussed in earlier tutorials
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include "vao.h"
#include "maths_funcs.h"
#define GL_LOG_FILE "gl.log"

// keep track of window size for things like the viewport and the mouse cursor
int g_gl_width = 640;
int g_gl_height = 480;
GLFWwindow* g_window = NULL;

void gameplay(float *x, float *y,float *tx, float *ty, float *deg){
	float d = 0.01f;
	if(glfwGetKey(g_window,GLFW_KEY_W)){
		*y +=d;
	}
	if(glfwGetKey(g_window,GLFW_KEY_A)){
		*x -=d;
	}
	if(glfwGetKey(g_window,GLFW_KEY_S)){
		*y -=d;
	}
	if(glfwGetKey(g_window,GLFW_KEY_D)){
		*x +=d;
	}
	if(glfwGetKey(g_window,GLFW_KEY_UP)){
		*ty +=d;
	}
	if(glfwGetKey(g_window,GLFW_KEY_DOWN)){
		*ty -=d;
	}
	if(glfwGetKey(g_window,GLFW_KEY_LEFT)){
		*tx -=d;
	}
	if(glfwGetKey(g_window,GLFW_KEY_RIGHT)){
		*tx +=d;
	}
	if(glfwGetKey(g_window,GLFW_KEY_Q)){
		*deg +=100*d;
	}
	if(glfwGetKey(g_window,GLFW_KEY_E)){
		*deg -=100*d;
	}
}

int main () {
	restart_gl_log();
	// all the GLFW and GLEW start-up code is moved to here in gl_utils.cpp
	start_gl();
	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable (GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"

	/* OTHER STUFF GOES HERE NEXT */
	GLfloat points[] = {
		 0.0f,	0.5f,	0.0f,
		 0.5f, -0.5f,	0.0f,
		-0.5f, -0.5f,	0.0f
	};
	
	GLfloat colours[] = {
		1.0f, 0.0f,  0.0f,
		0.0f, 1.0f,  0.0f,
		0.0f, 0.0f,  1.0f
	};

    GLuint indices[] = {0, 2, 1};
	
    GLuint vao = genvao(points, colours, indices, 9, 3);	
    GLuint shader_program = compile_link_shaders("vert.glsl", "frag.glsl");

    mat4 mat = identity_mat4();
	
	glUseProgram(shader_program);
	int matrix_location = glGetUniformLocation (shader_program, "matrix");
	glUniformMatrix4fv (matrix_location, 1, GL_FALSE, mat.m);
	
	glEnable (GL_CULL_FACE); // cull face
	glCullFace (GL_BACK); // cull back face
	glFrontFace (GL_CCW); // GL_CCW for counter clock-wise
	float dx = 0.0f;
	float dy = 0.0f;
	float tx = 1.0f;
	float ty = 1.0f;
	float deg = 0.0f;
	while(!glfwWindowShouldClose (g_window)){
		// add a timer for doing animation
		mat4 mat = identity_mat4();
		static double previous_seconds = glfwGetTime ();
		double current_seconds = glfwGetTime ();
		double elapsed_seconds = current_seconds - previous_seconds;
		previous_seconds = current_seconds;
		_update_fps_counter (g_window);
		// wipe the drawing surface clear
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport (0, 0, g_gl_width, g_gl_height);
		glUseProgram (shader_program);
		// update other events like input handling 
		glfwPollEvents ();
		if (GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose (g_window, 1);
		}
		gameplay(&dx,&dy,&tx,&ty,&deg);
		// update the matrix
		mat = rotate_z_deg(mat,deg);
		mat = scale(mat,vec3(tx, ty, 0.0));
		mat = translate(mat, vec3(dx, dy, 0.0));
		glUniformMatrix4fv (matrix_location, 1, GL_FALSE, mat.m);
		
		glBindVertexArray (vao);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(g_window);
	}
	// close GL context and any other GLFW resources
	glfwTerminate();
	return 0;
}
