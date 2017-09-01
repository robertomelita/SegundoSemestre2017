#ifndef _OBJECTS_H_
#define _OBJECTS_H_

GLuint genvbo(GLfloat *array, int n){
    GLuint vbo;
	glGenBuffers (1, &vbo);
	glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferData (GL_ARRAY_BUFFER, n * sizeof (GLfloat), array, GL_STATIC_DRAW);
    return vbo;
}

GLuint genvao(GLfloat *verts, GLfloat *cols, GLuint *indices, int nvert, int nind){
    GLuint vao;
    glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer (GL_ARRAY_BUFFER, genvbo(verts, nvert));
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer (GL_ARRAY_BUFFER, genvbo(cols, nvert));
	glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    return vao;
}

#endif