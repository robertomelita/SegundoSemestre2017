class esfera: public malla{
    private:
        int slices;
        int stacks;
        float radius;


    public:
        esfera(int slices, int stacks, float radius, GLuint shaderprog);
        void generate();
        void render();
};
