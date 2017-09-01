#version 130

uniform float dp;
in vec3 vp;

void main() {
    vec3 op = vp;
    op.x += dp;
	gl_Position = vec4(op+dp, 1.0);
}
