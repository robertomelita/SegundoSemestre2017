#ifndef TOOLS_H
#define TOOLS_H


void genvertices(GLfloat *verts, int n){
    // cada iteracion es un vertice
    float PI = 3.14159265358979323846f;
    float incremento = (PI/(n-1));
    float cont = 0.0f;

    verts[0]=0.0f;
    verts[1]=-0.7f;
    verts[2]=0.0f;

    for(int i = 1; i < n+1 ; i++){
        double aux = cosf(cont);
        verts[3*i] = aux;
        verts[3*i+1] = sinf(cont);
        verts[3*i+2] = 0.0f;
        cont = cont + incremento;
    }

}

//    0   3
//  2   1
void genindices(GLuint *indices, int n){
    // 0 1 2
    for(int i = 0; i < n-1; i++){
        indices[3*i] = 0;
        indices[3*i+1] = i+1;
        indices[3*i+2] = i + 2;
    }
}
#endif
