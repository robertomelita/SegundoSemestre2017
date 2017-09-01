#ifndef VAO_H
#define VAO_H

GLuint genvbo(float *data, int n){
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, n * sizeof (GLfloat), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return vbo;
}

GLuint genebo(GLuint *indices, int n){
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*n, indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return ebo;
}

// 2) Implementar "GLuint genvao(GLfloat *verts, GLfloat *cols, GLuint *indices, int nvert, int nind)" 
// que crea el VAO asociado a los arreglos y retorna el identificador. Haga  uso de genvbo() dentro de genvao para facilitar las cosas.
GLuint genvao(GLfloat *verts, GLfloat *cols, GLuint *indices, int nvert, int nind){
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

    GLuint points_vbo = genvbo(verts, nvert);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

    GLuint colors_vbo = genvbo(cols, nvert);
	glBindBuffer (GL_ARRAY_BUFFER, colors_vbo);
	glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

    GLuint ebo = genebo(indices, nind);
    glBindVertexArray(0);
    return vao;
}

#endif
