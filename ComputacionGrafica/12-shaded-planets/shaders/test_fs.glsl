#version 130
in vec3 normal;
in vec2 st;
in vec3 light;
out vec4 frag_colour;
uniform sampler2D basic_texture;

void main() {
	vec4 texel = texture (basic_texture, st);
	frag_colour = texel*vec4(light,0);
}
