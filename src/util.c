#include "util.h"

#include <glad/glad.h>
// glfw must be included after glad
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

GLFWwindow* sai_window;

void sai_open_window(void)
{
    sai_log("Initializing GLFW...");
    if(!glfwInit())
    {
        sai_fatal("Could not initialize GLFW.");
        exit(1);
    }

    sai_log("GLFW initialized.");

    sai_log("Creatring and initializing GLFW window...");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    sai_window = glfwCreateWindow(800, 600, "OpenGL Example", NULL, NULL);

    if(!sai_window)
    {
        sai_fatal("Could not create GLFW window.");
        exit(1);
    }

    glfwSwapInterval(1);
    glfwMakeContextCurrent(sai_window);
    sai_log("GLFW window initialized.");
}

void sai_close_window(void)
{
    sai_log("Destroying GLFW window...");
    glfwDestroyWindow(sai_window);
    sai_log("GLFW window destroyed.");

    sai_log("Terminating GLFW...");
    glfwTerminate();
    sai_log("GLFW terminated.");
}

void sai_load_opengl(void)
{
    sai_log("Loading OpenGL functions...");
    if(!gladLoadGL())
    {
        sai_fatal("Could not load OpenGL functions.");
        exit(1);
    }
    sai_log("OpenGL functions have been loaded.");
}

int sai_should_window_stay_open(void)
{
    return !glfwWindowShouldClose(sai_window);
}

void sai_update_window(void)
{
    glfwSwapBuffers(sai_window);

    glfwPollEvents();
}

void sai_log(const char* str)
{
    printf("%s\n", str);
}

void sai_fatal(const char* str)
{
    fprintf(stderr, "%s Exiting program.\n", str);
}

const char* sai_read_file(const char* path)
{
    FILE* f = fopen(path, "r");
    fseek(f, 0, SEEK_END);
    long file_size = ftell(f);

    fseek(f, 0, SEEK_SET);

    char* ret = (char*)malloc((file_size + 1) * sizeof(char));
    fread(ret, file_size, 1, f);
    fclose(f);

    ret[file_size] = '\0';

    return ret;
}
