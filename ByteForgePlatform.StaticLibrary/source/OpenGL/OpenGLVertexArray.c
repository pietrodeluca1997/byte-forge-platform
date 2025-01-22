#include "ByteForgePlatform/OpenGL/OpenGLVertexArray.h"

#include <glad/glad.h>

OpenGLVertexArray OpenGLVertexArray_New()
{
	float vertex_buffer[] =
	{
		// Position          // Texture coordinates
	    -0.5f,  0.5f, 0.0f,	 0.0f, 0.0f, // Top left vertex
		 0.5f,  0.5f, 0.0f,  1.0f, 0.0f, // Top right vertex
		 0.5f, -0.5f, 0.0f,  1.0f, 1.0f, // Bottom right vertex
	    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f  // Bottom left vertex
	};

	uint32_t index_buffer[] =
	{
		0, 1, 2, // First triangle
		2, 3, 0  // Second triangle
	};

	OpenGLVertexArray vertex_array = { 0 };
	vertex_array.vertices_number = 4;
	vertex_array.indexes_number = 6;
	
	glGenVertexArrays(1, &vertex_array.vertex_array_opengl_id);
	glGenBuffers(1, &vertex_array.vertex_buffer_opengl_id);
	glGenBuffers(1, &vertex_array.index_buffer_opengl_id);

	glBindVertexArray(vertex_array.vertex_array_opengl_id);

	glBindBuffer(GL_ARRAY_BUFFER, vertex_array.vertex_buffer_opengl_id);
	glBufferData(GL_ARRAY_BUFFER, vertex_array.vertices_number * 5 * sizeof(float), &vertex_buffer, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex_array.index_buffer_opengl_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertex_array.indexes_number * sizeof(uint32_t), &index_buffer, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 3 * sizeof(float));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return vertex_array;
}

void OpenGLVertexArray_Free(OpenGLVertexArray* vertex_array)
{
	if (vertex_array)
	{
		if (vertex_array->vertex_array_opengl_id)
		{
			glDeleteVertexArrays(1, &vertex_array->vertex_array_opengl_id);
			vertex_array->vertex_array_opengl_id = 0;
		}
				
		if (vertex_array->vertex_buffer_opengl_id)
		{
			glDeleteBuffers(1, &vertex_array->vertex_buffer_opengl_id);
			vertex_array->vertex_buffer_opengl_id = 0;
		}

		if (vertex_array->index_buffer_opengl_id)
		{
			glDeleteBuffers(1, &vertex_array->index_buffer_opengl_id);
			vertex_array->index_buffer_opengl_id = 0;
		}
	}
}