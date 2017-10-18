#ifndef ENEMIGO_H
#define ENEMIGO_H

using namespace std;

class enemigo: public malla {
    private:
        int vida;
        GLuint vao, vbo;
        int numvertices;
        vec3 pos;
        char* filename;

    public:
        enemigo(char *filename);
        void atacar();
        void moverse();
        void morir();

        // gets
        int getvida();
        // sets
        void setvida(int vida);
};

#endif
