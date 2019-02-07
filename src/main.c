
#include <glad/glad.h>
// glfw must be included after glad
#include "util.h"

#include <GLFW/glfw3.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Die Vertex Daten, mit denen der Vertex Buffer befuellt werden soll.
 */
float vertex_positions[4][2] = {{-0.75, -0.75}, {0.75, 0.75}, {-0.75, 0.75}, {0.75, -0.75}};

/**
 * Die Indices, mit denen der Index Buffer befuellt werden soll.
 */
unsigned int index_buffer[6] = {0, 1, 2, 0, 3, 1};

/**
 * Der Farbwert, mit dem der Uniform Buffer befuellt werden soll.
 */
float fragment_color[4] = {1.0f, 0.0f, 0.0f, 1.0f};

/**
 * Die Größe einer einzigen Position in den Vertex Daten.
 */
int SAI_VERTEX_BUFFER_ELEMENT_SIZE = sizeof(vertex_positions[0]) / sizeof(vertex_positions[0][0]);

/**
 * Die Größe der gesamten Vertex Daten.
 */
int SAI_VERTEX_BUFFER_SIZE = sizeof(vertex_positions) / sizeof(float);

/**
 * Die Größe der gesamten Index Daten.
 */
int SAI_INDEX_BUFFER_SIZE = sizeof(index_buffer) / sizeof(index_buffer[0]);

/**
 * Kreiert den Vertex Buffer und befuellt ihn mit den Daten aus dem Array vertex_positions.
 *
 * 
 */
GLuint sai_create_vertex_buffer(void)
{
    GLuint vao_id;
    glGenVertexArrays(1, &vao_id);
    glBindVertexArray(vao_id);

    GLuint vbo_id;
    glGenBuffers(1, &vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * SAI_VERTEX_BUFFER_SIZE, vertex_positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, SAI_VERTEX_BUFFER_ELEMENT_SIZE, GL_FLOAT, GL_FALSE,
                          sizeof(float) * SAI_VERTEX_BUFFER_ELEMENT_SIZE, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return vao_id;
}

GLuint sai_create_index_buffer(void)
{
    GLuint buffer_id;
    glGenBuffers(1, &buffer_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, SAI_INDEX_BUFFER_SIZE * sizeof(unsigned int), index_buffer,
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return buffer_id;
}

GLuint sai_compile_shader(GLenum shader_type, const char* shader_code)
{
    GLuint shader = glCreateShader(shader_type);

    glShaderSource(shader, 1, &shader_code, NULL);

    glCompileShader(shader);

    int compile_status;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);

    if(compile_status == GL_FALSE)
    {
        int log_length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
        char* message = (char*)malloc(log_length * sizeof(char));
        glGetShaderInfoLog(shader, log_length, &log_length, message);
        sai_log(message);
        free(message);
        return 0;
    }

    return shader;
}

GLuint sai_load_shaders(void)
{
    GLuint program = glCreateProgram();

    const char* vertex_shader_code = sai_read_file("shader/example_shader.vs.glsl");

    GLuint vs = sai_compile_shader(GL_VERTEX_SHADER, vertex_shader_code);

    free((void*)vertex_shader_code);

    if(vs == 0)
        return 0;

    const char* fragment_shader_code = sai_read_file("shader/example_shader.fs.glsl");

    GLuint fs = sai_compile_shader(GL_FRAGMENT_SHADER, fragment_shader_code);

    free((void*)fragment_shader_code);

    if(fs == 0)
        return 0;

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDetachShader(program, vs);
    glDetachShader(program, fs);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void sai_set_color_uniform_data(GLuint program)
{
    GLint uniform_location = glGetUniformLocation(program, "u_color");

    if(uniform_location == -1)
        return;

    glUniform4f(uniform_location, fragment_color[0], fragment_color[1], fragment_color[2], fragment_color[3]);
}

int main(void)
{
    sai_log("Starting application...");

    sai_open_window();
    sai_load_opengl();

    sai_log("Creating vertex buffer...");
    GLuint vao_id = sai_create_vertex_buffer();

    glBindVertexArray(vao_id);
    sai_log("Vertex buffer has been created.");

    sai_log("Creating index buffer...");
    GLuint index_buffer = sai_create_index_buffer();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    sai_log("Index buffer has been created.");

    sai_log("Processing shaders...");
    GLuint program = sai_load_shaders();

    if(program == 0)
    {
        sai_fatal("Shaders could not be processed.");
        exit(1);
    }

    glUseProgram(program);
    sai_log("Shaders have been processed...");

    sai_log("Setting up uniform buffer...");
    sai_set_color_uniform_data(program);
    sai_log("Uniform buffer has been set up.");

    sai_log("Now entering main loop...");

    while(sai_should_window_stay_open())
    {
        glDrawElements(GL_TRIANGLES, SAI_INDEX_BUFFER_SIZE, GL_UNSIGNED_INT, NULL);

        sai_update_window();
    }

    sai_log("Exited main loop.");

    sai_close_window();

    sai_log("Program ran successfully.");
}
