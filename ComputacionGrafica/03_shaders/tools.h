#ifndef TOOLS_H
#define TOOLS_H

const char* GL_type_to_string (GLenum type) {
	switch (type) {
		case GL_BOOL: return "bool";
		case GL_INT: return "int";
		case GL_FLOAT: return "float";
		case GL_FLOAT_VEC2: return "vec2";
		case GL_FLOAT_VEC3: return "vec3";
		case GL_FLOAT_VEC4: return "vec4";
		case GL_FLOAT_MAT2: return "mat2";
		case GL_FLOAT_MAT3: return "mat3";
		case GL_FLOAT_MAT4: return "mat4";
		case GL_SAMPLER_2D: return "sampler2D";
		case GL_SAMPLER_3D: return "sampler3D";
		case GL_SAMPLER_CUBE: return "samplerCube";
		case GL_SAMPLER_2D_SHADOW: return "sampler2DShadow";
		default: break;
	}
	return "other";
}

/* print errors in shader compilation */
void _print_shader_info_log (GLuint shader_index) {
	int max_length = 2048;
	int actual_length = 0;
	char log[2048];
	glGetShaderInfoLog (shader_index, max_length, &actual_length, log);
	printf ("shader info log for GL index %i:\n%s\n", shader_index, log);
}

/* print errors in shader linking */
void _print_programme_info_log (GLuint sp) {
	int max_length = 2048;
	int actual_length = 0;
	char log[2048];
	glGetProgramInfoLog (sp, max_length, &actual_length, log);
	printf ("program info log for GL index %i:\n%s", sp, log);
}

/* validate shader */
bool is_valid (GLuint sp) {
	int params = -1;

	glValidateProgram (sp);
	glGetProgramiv (sp, GL_VALIDATE_STATUS, &params);
	printf ("program %i GL_VALIDATE_STATUS = %i\n", sp, params);
	if (GL_TRUE != params) {
		_print_programme_info_log (sp);
		return false;
	}
	return true;
}

/* print absolutely everything about a shader - only useful if you get really
stuck wondering why a shader isn't working properly */
void print_all (GLuint sp) {
	int params = -1;
	int i;

	printf ("--------------------\nshader programme %i info:\n", sp);
	glGetProgramiv (sp, GL_LINK_STATUS, &params);
	printf ("GL_LINK_STATUS = %i\n", params);

	glGetProgramiv (sp, GL_ATTACHED_SHADERS, &params);
	printf ("GL_ATTACHED_SHADERS = %i\n", params);

	glGetProgramiv (sp, GL_ACTIVE_ATTRIBUTES, &params);
	printf ("GL_ACTIVE_ATTRIBUTES = %i\n", params);

	for (i = 0; i < params; i++) {
		char name[64];
		int max_length = 64;
		int actual_length = 0;
		int size = 0;
		GLenum type;
		glGetActiveAttrib (sp, i, max_length, &actual_length, &size, &type,
                           name);
		if (size > 1) {
			int j;
			for (j = 0; j < size; j++) {
				char long_name[64];
				int location;

				sprintf (long_name, "%s[%i]", name, j);
				location = glGetAttribLocation (sp, long_name);
				printf ("  %i) type:%s name:%s location:%i\n",
					i, GL_type_to_string (type), long_name, location);
			}
		} else {
			int location = glGetAttribLocation (sp, name);
			printf ("  %i) type:%s name:%s location:%i\n",
				i, GL_type_to_string (type), name, location);
		}
	}

	glGetProgramiv (sp, GL_ACTIVE_UNIFORMS, &params);
	printf ("GL_ACTIVE_UNIFORMS = %i\n", params);
	for (i = 0; i < params; i++) {
		char name[64];
		int max_length = 64;
		int actual_length = 0;
		int size = 0;
		GLenum type;
		glGetActiveUniform (sp, i, max_length, &actual_length, &size, &type,
                            name);
		if (size > 1) {
			int j;
			for (j = 0; j < size; j++) {
				char long_name[64];
				int location;

				sprintf (long_name, "%s[%i]", name, j);
				location = glGetUniformLocation (sp, long_name);
				printf ("  %i) type:%s name:%s location:%i\n",
					i, GL_type_to_string (type), long_name, location);
			}
		} else {
			int location = glGetUniformLocation (sp, name);
			printf ("  %i) type:%s name:%s location:%i\n",
				i, GL_type_to_string (type), name, location);
		}
	}

	_print_programme_info_log (sp);
}

/* copy a shader from a plain text file into a character array */
bool parse_file_into_str (const char* file_name, char* shader_str, int max_len) {
	FILE* file = fopen (file_name , "r");
	if (!file) {
		gl_log_err ("ERROR: opening file for reading: %s\n", file_name);
		return false;
	}
	size_t cnt = fread (shader_str, 1, max_len - 1, file);
	if ((int)cnt >= max_len - 1) {
		gl_log_err ("WARNING: file %s too big - truncated.\n", file_name);
	}
	if (ferror (file)) {
		gl_log_err ("ERROR: reading shader file %s\n", file_name);
		fclose (file);
		return false;
	}
	// append \0 to end of file string
	shader_str[cnt] = 0;
	fclose (file);
	return true;
}

GLuint compile_link_shaders(const char *vsfile, const char *fsfile){
	char vertex_shader[1024 * 256];
	char fragment_shader[1024 * 256];
	GLuint vs, fs, shader_programme;
	const GLchar* p;
	int params = -1;

	/* load shaders from files here */
	parse_file_into_str (vsfile, vertex_shader, 1024 * 256);
	parse_file_into_str (fsfile, fragment_shader, 1024 * 256);

	vs = glCreateShader (GL_VERTEX_SHADER);
	p = (const GLchar*)vertex_shader;
	glShaderSource (vs, 1, &p, NULL);
	glCompileShader (vs);

	/* check for shader compile errors - very important! */

	glGetShaderiv (vs, GL_COMPILE_STATUS, &params);
	if (GL_TRUE != params) {
		fprintf (stderr, "ERROR: GL shader index %i did not compile\n", vs);
		_print_shader_info_log (vs);
		return 1; /* or exit or something */
	}

	fs = glCreateShader (GL_FRAGMENT_SHADER);
	p = (const GLchar*)fragment_shader;
	glShaderSource (fs, 1, &p, NULL);
	glCompileShader (fs);

	/* check for compile errors */
	glGetShaderiv (fs, GL_COMPILE_STATUS, &params);
	if (GL_TRUE != params) {
		fprintf (stderr, "ERROR: GL shader index %i did not compile\n", fs);
		_print_shader_info_log (fs);
		return 1; /* or exit or something */
	}

	shader_programme = glCreateProgram ();
	glAttachShader (shader_programme, fs);
	glAttachShader (shader_programme, vs);
	glLinkProgram (shader_programme);

	/* check for shader linking errors - very important! */
	glGetProgramiv (shader_programme, GL_LINK_STATUS, &params);
	if (GL_TRUE != params) {
		fprintf (
			stderr,
			"ERROR: could not link shader programme GL index %i\n",
			shader_programme
		);
		_print_programme_info_log (shader_programme);
		return 1;
	}
	print_all (shader_programme);
	bool result = is_valid (shader_programme);
	assert (result);
    return shader_programme;
}

#endif
