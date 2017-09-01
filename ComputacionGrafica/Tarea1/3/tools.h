#ifndef TOOLS_H
#define TOOLS_H

void genvertices(GLfloat *verts, int n){
    // cada iteracion es un vertice
    float incremento = (2/(n-1.0f));
    int cont = 0;
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            verts[3*cont]=(j*incremento)-1.0f;
            verts[(3*cont)+1]=(i*incremento)-1.0f;
            verts[(3*cont)+2]=0.0f;
            cont++;
        }
        
    }
}

//    0   3
//  2   1
void genindices(GLuint *indices, int n){
    // 0 1 2
    int cont = 0;
    for(int i = 0; i < (n*n); i++){
        if( n-1!=i%n && i<(n*n)-n-1){
            indices[6*cont] = i;
            indices[6*cont+1] = i+1;    
            indices[6*cont+2] = i+n;
            indices[6*cont+3] = i+n;
            indices[6*cont+4] = i+1+n;
            indices[6*cont+5] = i+1;
            cont++;            
        }
    }
}

int powsapito(int a,int b){
    int c=1;
    for(int x=0;x<b;x++){
        c=a*c;
    }
    return c;
}
#endif
