#pragma once

#include <stdint.h>

typedef enum 
{
	SHADER_VERTEX,
	SHADER_FRAGMENT,
	SHADER_PROGRAM
} OpenGL_EShaderType;

typedef struct OpenGLShader
{
	char* vertex_shader_code;
	uint8_t opengl_vertex_shader_id;
	char* fragment_shader_code;
	uint8_t opengl_fragment_shader_id;
	uint8_t opengl_shader_program_id;	
} OpenGLShader;

OpenGLShader OpenGLShader_New(const char* vertex_shader_code, const char* fragment_shader_code);
void OpenGLShader_Free(OpenGLShader* shader);