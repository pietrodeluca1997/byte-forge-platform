#pragma once

#include <stdint.h>

typedef struct OpenGLTexture
{
	uint32_t opengl_texture_id;
	int texture_width;
	int texture_height;
	void* pixels;
} OpenGLTexture;

OpenGLTexture OpenGLTexture_New(const int texture_width, const int texture_height, const void* pixels);
void OpenGLTexture_Free(OpenGLTexture* texture);