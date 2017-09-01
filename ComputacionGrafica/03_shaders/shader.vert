#version 130

in vec3 vp;

void main() {
    vec3 op = vp;
	gl_Position = vec4(op, 1.0);
}
