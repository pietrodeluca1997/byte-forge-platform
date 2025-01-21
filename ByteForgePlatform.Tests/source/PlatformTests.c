#include "PlatformTestFixture.h"

#include <ByteForgeMath/Matrix4.h>
#include <ByteForgePlatform/OpenGL/OpenGLVertexArray.h>
#include <ByteForgePlatform/OpenGL/OpenGLShader.h>

#include <glad/glad.h>

const static char* vertex_shader = "#version 460 core\n"
"layout (location = 0) in vec3 position;\n"
"uniform mat4 projection_matrix;\n"
"uniform mat4 model_matrix;\n"
"void main()\n"
"{\n"
"    gl_Position = projection_matrix * model_matrix * vec4(position, 1.0);\n"
"}\n\0";

const static char* fragment_shader = "#version 460 core\n"
"out vec4 out_color;\n"
"void main()\n"
"{\n"
"    out_color = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
"}\n\0";
 
int main()
{
	PlatformTestFixture* fixture = { 0 };
	PlatformTestFixture_New(&fixture);

	PlatformOpenGLContext_Initialize(fixture->platform_data);

	OpenGLShader shader = OpenGLShader_New(vertex_shader, fragment_shader);
	OpenGLVertexArray vao = OpenGLVertexArray_New();

	glUseProgram(shader.opengl_shader_program_id);

	Matrix4_Linear projection = Matrix4_Orthographic(0, fixture->platform_data->window_data->window_width, 0, fixture->platform_data->window_data->window_height, -1.0f, 1.0f);
	
	int projection_matrix_location = glGetUniformLocation(shader.opengl_shader_program_id, "projection_matrix");
	glUniformMatrix4fv(projection_matrix_location, 1, GL_FALSE, &projection.data[0]);

	int model_matrix_location = glGetUniformLocation(shader.opengl_shader_program_id, "model_matrix");
	
	Matrix4_Linear player_model = Matrix4_Identity();
	player_model = Matrix4_Scale(player_model, 512.0f, 50.0f, 1.0f);
	player_model = Matrix4_Translate(player_model, 512.0f, 384.0f, 0.0f);

	glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, &player_model.data[0]);

	while (PlatformOpenGLContext_PollThreadEvents(NULL, NULL))
	{
		PlatformOpenGLContext_SetBackgroundColor(fixture->platform_data, 0.2f, 0.2f, 0.2f, 1.0f);

		glUseProgram(shader.opengl_shader_program_id);
		glBindVertexArray(vao.vertex_array_opengl_id);
		glDrawElements(GL_TRIANGLES, vao.indexes_number, GL_UNSIGNED_INT, NULL);

		PlatformOpenGLContext_SwapBuffers(fixture->platform_data);
	}
		
	PlatformTestFixture_Free(&fixture);

	return 0;
}