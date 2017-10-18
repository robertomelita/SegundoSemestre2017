#ifndef MALLA_H
#define MALLA_H

#define TRIANGLE_FACTOR 3
#define QUAD_FACTOR     4

using namespace std;

class malla{
    private:
        char* filename;
        int nvertices;
        int nfaces;
        mat4 M;
        vec3 pos;
        GLuint FTYPE;
        GLuint FFACTOR;
        GLuint vao, vbo, nbo, tbo, ebo;
	    int matloc;

    protected:
        GLuint tex;
        GLuint shaderprog;

    public:
        malla(char *filename);
        malla();

        // functions
        void makevao(vec3 *vertices, vec3* normals, vec2* texcoords, int *indices);
        bool load_texture(const char* file_name);
        void mtranslate(vec3 d);
        void mrotatey(float d);
        void reset_matrix();
        void print_matrix();

        // gets
        vec3 get_pos();
        mat4 get_matrix();
        GLuint get_vao();
        GLuint get_facetype();
        GLuint get_facefactor();
        char* get_filename();
        int get_numvertices();
        int get_numfaces();
        int get_matloc();


        // sets
        void set_pos(vec3 p);
        void set_facetype(GLuint FTYPE);
        void set_facefactor(GLuint FFACTOR);
        void set_numvertices(int nvert);
        void set_numfaces(int ntri);
        void set_matrix(mat4 M);
        void set_matloc(int matloc);

};

#endif
