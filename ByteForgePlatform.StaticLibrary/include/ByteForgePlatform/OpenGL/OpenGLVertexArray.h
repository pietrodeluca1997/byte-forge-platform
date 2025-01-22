#pragma once

#include <stdint.h>

typedef struct OpenGLVertexArray
{	
	uint32_t vertices_number;	
	uint32_t indexes_number;	
	uint32_t vertex_buffer_opengl_id;	
	uint32_t index_buffer_opengl_id;	
	uint32_t vertex_array_opengl_id;
} OpenGLVertexArray;

OpenGLVertexArray OpenGLVertexArray_New();
void OpenGLVertexArray_Free(OpenGLVertexArray* vertex_array);