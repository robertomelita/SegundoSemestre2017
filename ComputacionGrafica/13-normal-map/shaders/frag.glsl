#version 130
#define SPOTLIGHT_CUT 0.999f    // valor limite: es inverso al radio del cono de luz
in vec2 st;
in vec3 view_dir_tan;
in vec3 light_dir_tan;
in vec4 test_tan;

uniform sampler2D texsamp_rgb;
uniform sampler2D texsamp_normal;

// propiedades luz
#define SPECULAR_EXP 20
vec4 la = vec4(0.02, 0.02, 0.02, 1.0);
vec4 ld = vec4(0.8, 0.8, 0.8, 1.0);
vec4 ls = vec4(0.5, 0.5, 0.5, 1.0);

// material objeto
vec4 ka = vec4(1.0, 1.0, 1.0, 1.0);
vec4 kd = vec4(1.0, 1.0, 1.0, 1.0);
vec4 ks = vec4(0.7, 0.7, 0.7, 1.0);

out vec4 frag_colour;
void main() {
	vec3 Ia = la.rgb * ka.rgb;

	// sample the normal map and covert from 0:1 range to -1:1 range
	vec3 normal_tan = texture (texsamp_normal, st).rgb;
	vec3 texel      = texture (texsamp_rgb, st).rgb;
	normal_tan = normalize (normal_tan * 2.0 - 1.0);

	// diffuse light equation done in tangent space
	vec3 direction_to_light_tan = normalize (-light_dir_tan);
	float dot_prod = dot (direction_to_light_tan, normal_tan);
	dot_prod = max (dot_prod, 0.0);
	//vec3 Id = vec3 (0.7, 0.7, 0.7) * vec3 (1.0, 0.5, 0.0) * dot_prod;
	vec3 Id = ld.rgb * kd.rgb * texel * dot_prod;

	// specular light equation done in tangent space
	vec3 reflection_tan = reflect (normalize (light_dir_tan), normal_tan);
	float dot_prod_specular = dot (reflection_tan, normalize (view_dir_tan));
	dot_prod_specular = max (dot_prod_specular, 0.0);
	float specular_factor = pow (dot_prod_specular, SPECULAR_EXP);
	//vec3 Is = vec3 (1.0, 1.0, 1.0) * vec3 (0.5, 0.5, 0.5) * specular_factor;
	vec3 Is = ls.rgb * ks.rgb * specular_factor;

	// phong light output
	frag_colour.rgb = Is + Id + Ia;
	frag_colour.a = 1.0;
}
