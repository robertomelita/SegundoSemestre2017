#ifndef TOOLS_H
#define TOOLS_H

void genvertices(GLfloat *verts){
    // cada iteracion es un vertice
    verts[0] = -0.5f;
    verts[1] = 0.5f;
    verts[2] = 0.0f;

    verts[3] = 0.5f;
    verts[4] = -0.5f;
    verts[5] = 0.0f;

    verts[6] = -0.5f;
    verts[7] = -0.5f;
    verts[8] = 0.0f;

    verts[9] = 0.5f;
    verts[10] = 0.5f;
    verts[11] = 0.0f;

}

//    0   3
//  2   1
void genindices(GLuint *indices){
	// 0 1 2
	indices[0] = 1;
	indices[1] = 0;
	indices[2] = 2; 		
}

void genindices2(GLuint *indices){
    indices[0] = 0;
	indices[1] = 1;
    indices[2] = 3;
}
#endif
