#include <assimp/cimport.h> // C importer
#include <assimp/scene.h> // collects data
#include <assimp/postprocess.h> // various extra operations
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include "maths_funcs.h"
#include "gl_utils.h"
#include "tools.h"
#include "malla.h"

#define GL_LOG_FILE "log/gl.log"
#define PHONG_SHADING_VS_FILE "shaders/vert.glsl"
#define PHONG_SHADING_FS_FILE "shaders/frag.glsl"
#define ONE_DEG_IN_RAD (2.0 * M_PI) / 360.0 // 0.017444444

// keep track of window size for things like the viewport and the mouse cursor
int g_gl_width = 1280;
int g_gl_height = 720;
GLFWwindow* g_window = NULL;

int main(){
    init_gl(g_gl_width, g_gl_height);
	GLuint shader_programme = create_programme_from_files ( PHONG_SHADING_VS_FILE, PHONG_SHADING_FS_FILE);

	// input variables
    mat4 pers_mat = perspective(67.0f, (float)g_gl_width / (float)g_gl_height, 0.1f, 100.0f);
    mat4 ortho_mat = orthographic(-100, 100, 2.5, -2.5, -4, 4);
    // para gameplay con camara
    mat4 proj = pers_mat;
    // para estatico, se ve mejor
    // mat4 proj = ortho_mat;
	
	float cam_speed = 1.0f; // 1 unit per second
	float cam_yaw_speed = 70.0f; // 10 degrees per second
	float cam_pos[] = {0.0f, 0.0f, 5.0f}; // don't start at zero, or we will be too close
	float cam_yaw = 0.0f; // y-rotation in degrees
	mat4 T = translate (identity_mat4 (), vec3 (-cam_pos[0], -cam_pos[1], -cam_pos[2]));
	mat4 R = rotate_y_deg (identity_mat4 (), -cam_yaw);
	mat4 view_mat = R * T;
	
	int view_mat_location = glGetUniformLocation (shader_programme, "view");
	int vmatloc_fs = glGetUniformLocation (shader_programme, "view_mat");
	glUseProgram (shader_programme);
	glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, view_mat.m);
	glUniformMatrix4fv (vmatloc_fs, 1, GL_FALSE, view_mat.m);
	int proj_mat_location = glGetUniformLocation (shader_programme, "proj");
	glUseProgram (shader_programme);
	glUniformMatrix4fv (proj_mat_location, 1, GL_FALSE, proj.m);



    printf("loading earth model......."); fflush(stdout);
	malla *earth = new malla((const char*)"mallas/esfera.obj", shader_programme, GL_TRIANGLES);
    printf("done\nloading earth textures......."); fflush(stdout);
	earth->load_texture_rgb("textures/earth8k.jpg", "texsamp_rgb");
	earth->load_texture_normal("textures/earth8k-normal.png", "texsamp_normal");

    printf("done\nloading moon model......."); fflush(stdout);
	malla *moon = new malla((const char*)"mallas/esfera.obj", shader_programme, GL_TRIANGLES);
    printf("done\nloading moon textures......."); fflush(stdout);
	moon->load_texture_rgb("textures/moon8k.jpg", "texsamp_rgb");
	moon->load_texture_normal("textures/moon4k-normal.jpg", "texsamp_normal");
    printf("done\n"); fflush(stdout);

    float earth_rot = 0.0f;
    float moon_rot = 0.0f, moon_orbit = 0.0f;
	while(!glfwWindowShouldClose (g_window)){
		static double previous_seconds = glfwGetTime ();
		double current_seconds = glfwGetTime ();
		double elapsed_seconds = current_seconds - previous_seconds;
		previous_seconds = current_seconds;
	
		_update_fps_counter (g_window);
		// wipe the drawing surface clear
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport (0, 0, g_gl_width, g_gl_height);
		glUseProgram (shader_programme);

		// render earth
		earth->reset_matrix();
		earth->mrotate(vec3(0.0f, earth_rot, 0.0f));
		earth->render_indices();

		// render moon
		moon->reset_matrix();
		moon->mrotate(vec3(0.0f, moon_rot, 0.0f));
		moon->mtranslate(vec3(6.0f, 1.0f, 1.0f));
		moon->mrotate(vec3(0.0f, moon_orbit, 0.0f));
		moon->mscale(vec3(0.3, 0.3f, 0.3f));
		moon->render_indices();

		// update other events like input handling 
		glfwPollEvents();
		// control keys
        bool cam_moved = gameplay(cam_speed, elapsed_seconds, cam_pos, &cam_yaw, cam_yaw_speed);
		// update view matrix
		if(cam_moved){
            // cam translation
			mat4 T = translate (identity_mat4 (), vec3 (-cam_pos[0], -cam_pos[1], -cam_pos[2]));
            mat4 R = rotate_y_deg(identity_mat4 (), -cam_yaw); // 
			//mat4 view_mat = R * T;
			mat4 view_mat = R * T;
			glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, view_mat.m);
			glUniformMatrix4fv(vmatloc_fs, 1, GL_FALSE, view_mat.m);
		}
		if (GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_ESCAPE)){
			glfwSetWindowShouldClose (g_window, 1);
		}
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers (g_window);
        earth_rot   +=  0.1f;
        moon_rot    += -0.15f;
        moon_orbit  +=  0.5f;
	}
	// close GL context and any other GLFW resources
	glfwTerminate();
	return 0;
}
