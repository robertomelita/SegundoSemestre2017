#ifndef MALLA_H
#define MALLA_H

using namespace std;

class malla{
    private:
        GLuint vao, vbo;
        int numvertices;
        glm::mat4 model;
        glm::vec3 pos;
        char* filename;

    public:
        malla(char *filename);

        // gets
        GLuint getvao();
        int getnumvertices();
        glm::vec3 getpos();
        char* getfilename();

        // sets
        void setvao(GLuint vao);
        void setnumvertices(int num);
        void setpos(glm::vec3 p);
        void setfilename(char *f);
        void setmatloc(GLuint shaderprog, const char *name);
        void model2Shader(GLuint shaderprog);
};

#endif
