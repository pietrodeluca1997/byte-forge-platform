#include "ByteForgePlatform/OpenGL/OpenGLTexture.h"

#include <glad/glad.h>

OpenGLTexture OpenGLTexture_New(const int texture_width, const int texture_height, const void* pixels)
{
	OpenGLTexture texture = { 0 };
	
	glGenTextures(1, &texture.opengl_texture_id);
	glBindTexture(GL_TEXTURE_2D, texture.opengl_texture_id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_width, texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	texture.texture_width = texture_width;
	texture.texture_height = texture_height;
	texture.pixels = pixels;

	return texture;
}