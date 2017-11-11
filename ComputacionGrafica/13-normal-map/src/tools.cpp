#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <assimp/cimport.h> // C importer
#include <assimp/scene.h> // collects data
#include <assimp/postprocess.h> // various extra operations
#include "maths_funcs.h"
#include "gl_utils.h"
#include "tools.h"

#define PI 3.14159265359

void init_gl(int width, int height){
	restart_gl_log ();
	start_gl ();
	glEnable (GL_DEPTH_TEST); // enable depth-testing
    glEnable( GL_POINT_SMOOTH );
	glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"
	//glEnable (GL_CULL_FACE); // cull face
	//glCullFace (GL_BACK); // cull back face
	glFrontFace (GL_CCW); // set counter-clock-wise vertex order to mean the front
	glClearColor (0.0, 0.0, 0.0, 1.0); // grey background to help spot mistakes
	glViewport (0, 0, width, height);
}

bool gameplay(float cam_speed, double elapsed_seconds, float *cam_pos, float *cam_yaw, float cam_yaw_speed){
    bool cam_moved = false;
    float ryaw = *cam_yaw*PI/180.0;
    if (glfwGetKey (g_window, GLFW_KEY_A)) {

        cam_pos[0] -= cos(ryaw)* cam_speed * elapsed_seconds;

        cam_pos[2] += sin(ryaw)* cam_speed * elapsed_seconds;

        cam_moved = true;

    }

    if (glfwGetKey (g_window, GLFW_KEY_D)) {

        cam_pos[0] += cos(ryaw)* cam_speed * elapsed_seconds;

        cam_pos[2] -= sin(ryaw)* cam_speed * elapsed_seconds;

        cam_moved = true;

    }
    if (glfwGetKey (g_window, GLFW_KEY_PAGE_UP)) {
        cam_pos[1] += cam_speed * elapsed_seconds;
        cam_moved = true;
    }
    if (glfwGetKey (g_window, GLFW_KEY_PAGE_DOWN)) {
        cam_pos[1] -= cam_speed * elapsed_seconds;
        cam_moved = true;
    }
    if (glfwGetKey (g_window, GLFW_KEY_W)) {
        cam_pos[0] -= sin(ryaw)* cam_speed * elapsed_seconds;
        cam_pos[2] -= cos(ryaw)* cam_speed * elapsed_seconds;
        cam_moved = true;
    }
    if (glfwGetKey (g_window, GLFW_KEY_S)) {
        cam_pos[0] += sin(ryaw)* cam_speed * elapsed_seconds;
        cam_pos[2] += cos(ryaw)* cam_speed * elapsed_seconds;
        cam_moved = true;
    }
    if (glfwGetKey (g_window, GLFW_KEY_LEFT)) {
        *cam_yaw += cam_yaw_speed * elapsed_seconds;
        cam_moved = true;
    }
    if (glfwGetKey (g_window, GLFW_KEY_RIGHT)) {
        *cam_yaw -= cam_yaw_speed * elapsed_seconds;
        cam_moved = true;
    }

    //if(cam_moved){
    //    printf("yaw = %f\n", *cam_yaw);
    //}
    return cam_moved;
}

