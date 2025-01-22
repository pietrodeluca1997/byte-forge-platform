#include "ByteForgePlatform/OpenGL/OpenGLShader.h"

#include <ByteForgeLogging.h>

#include <glad/glad.h>

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

static void OpenGLShader_GetCompilationResult(uint8_t opengl_shader_id, OpenGL_EShaderType shader_type)
{
    int compilation_succeeded;
    char compilation_log_buffer[1024];

    if (shader_type != SHADER_PROGRAM)
    {
        glGetShaderiv(opengl_shader_id, GL_COMPILE_STATUS, &compilation_succeeded);

        if (!compilation_succeeded)
        {
            glGetShaderInfoLog(opengl_shader_id, sizeof(compilation_log_buffer), NULL, compilation_log_buffer);
            LOG_FATAL("Error when trying to compile shader. OpenGL Message: %s", compilation_log_buffer);
        }
    }
    else
    {
        glGetProgramiv(opengl_shader_id, GL_LINK_STATUS, &compilation_succeeded);

        if (!compilation_succeeded)
        {
            glGetProgramInfoLog(opengl_shader_id, sizeof(compilation_log_buffer), NULL, compilation_log_buffer);
            LOG_FATAL("Error when trying to link shader program. OpenGL Message: %s", compilation_log_buffer);
        }
    }
    
}

OpenGLShader OpenGLShader_New(const char* vertex_shader_code, const char* fragment_shader_code)
{
	OpenGLShader shader = { 0 };
	
	shader.vertex_shader_code = vertex_shader_code;
	shader.opengl_vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shader.opengl_vertex_shader_id, 1, &shader.vertex_shader_code, NULL);
	glCompileShader(shader.opengl_vertex_shader_id);
    OpenGLShader_GetCompilationResult(shader.opengl_vertex_shader_id, SHADER_VERTEX);

	shader.fragment_shader_code = fragment_shader_code;
	shader.opengl_fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shader.opengl_fragment_shader_id, 1, &shader.fragment_shader_code, NULL);
	glCompileShader(shader.opengl_fragment_shader_id);
    OpenGLShader_GetCompilationResult(shader.opengl_fragment_shader_id, SHADER_FRAGMENT);

	shader.opengl_shader_program_id = glCreateProgram();
	glAttachShader(shader.opengl_shader_program_id, shader.opengl_vertex_shader_id);
	glAttachShader(shader.opengl_shader_program_id, shader.opengl_fragment_shader_id);
	glLinkProgram(shader.opengl_shader_program_id);
    OpenGLShader_GetCompilationResult(shader.opengl_shader_program_id, SHADER_PROGRAM);

	glDeleteShader(shader.opengl_vertex_shader_id);
	glDeleteShader(shader.opengl_fragment_shader_id);

	return shader;
}

void OpenGLShader_Free(OpenGLShader* shader)
{
    if (shader)
    {
        if (shader->opengl_shader_program_id)
        {
            glDeleteProgram(shader->opengl_shader_program_id);
            shader->opengl_shader_program_id = 0;
        }

        if (shader->opengl_vertex_shader_id)
        {
            glDeleteShader(shader->opengl_vertex_shader_id);
            shader->opengl_vertex_shader_id = 0;
        }

        if (shader->opengl_fragment_shader_id)
        {
            glDeleteShader(shader->opengl_fragment_shader_id);
            shader->opengl_fragment_shader_id = 0;
        }
    }
}
