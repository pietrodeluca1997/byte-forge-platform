#include "PlatformTestFixture.h"

#include <ByteForgeMath/Matrix4.h>
#include <ByteForgePlatform/OpenGL/OpenGLVertexArray.h>
#include <ByteForgePlatform/OpenGL/OpenGLShader.h>
#include <ByteForgePlatform/OpenGL/OpenGLTexture.h>

#include <glad/glad.h>
#include <SDL3_image/SDL_image.h>

const static char* vertex_shader = "#version 460 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec2 in_texture_coordinates;\n"
"out vec2 texture_coordinates;\n"
"uniform mat4 projection_matrix;\n"
"uniform mat4 model_matrix;\n"
"void main()\n"
"{\n"
"   texture_coordinates = in_texture_coordinates;\n"
"   gl_Position = projection_matrix * model_matrix * vec4(position, 1.0);\n"
"}\n\0";

const static char* fragment_shader = "#version 460 core\n"
"in vec2 texture_coordinates;\n"
"uniform sampler2D in_texture;\n"
"out vec4 out_color;\n"
"void main()\n"
"{\n"
"    out_color = texture(in_texture, texture_coordinates);\n"
"}\n\0";
 
int main()
{
	PlatformTestFixture* fixture = { 0 };
	PlatformTestFixture_New(&fixture);

	PlatformOpenGLContext_Initialize(fixture->platform_data);

	SDL_Surface* surface = IMG_Load("./assets/background_layer_2.png");
	OpenGLTexture texture = OpenGLTexture_New(surface->w, surface->h, surface->pixels);
	SDL_DestroySurface(surface);

	OpenGLShader shader = OpenGLShader_New(vertex_shader, fragment_shader);
	OpenGLVertexArray vao = OpenGLVertexArray_New();

	glUseProgram(shader.opengl_shader_program_id);

	Matrix4_Linear projection = Matrix4_Orthographic(0, fixture->platform_data->window_data->viewport_width, 0, fixture->platform_data->window_data->viewport_height, -1.0f, 1.0f);
	
	int projection_matrix_location = glGetUniformLocation(shader.opengl_shader_program_id, "projection_matrix");
	glUniformMatrix4fv(projection_matrix_location, 1, GL_FALSE, &projection.data[0]);
	int texture_location = glGetUniformLocation(shader.opengl_shader_program_id, "in_texture");
	
	int model_matrix_location = glGetUniformLocation(shader.opengl_shader_program_id, "model_matrix");
	
	Matrix4_Linear background_model = Matrix4_Identity();
	background_model = Matrix4_Scale(background_model, 320.0f, 180.0f, 1.0f);
	background_model = Matrix4_Translate(background_model, 160.0f, 90.0f, 0.0f);

	glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, &background_model.data[0]);

	while (PlatformOpenGLContext_PollThreadEvents(NULL, NULL))
	{
		PlatformOpenGLContext_SetBackgroundColor(fixture->platform_data, 0.2f, 0.2f, 0.2f, 1.0f);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture.opengl_texture_id);
		glUniform1i(texture_location, 0);

		glBindVertexArray(vao.vertex_array_opengl_id);
		glDrawElements(GL_TRIANGLES, vao.indexes_number, GL_UNSIGNED_INT, NULL);

		PlatformOpenGLContext_SwapBuffers(fixture->platform_data);
	}
		
	PlatformTestFixture_Free(&fixture);

	return 0;
}