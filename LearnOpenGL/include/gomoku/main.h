#ifndef MAIN_H
#define MAIN_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <gomoku/shader.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glfw3.lib")


GLFWwindow* g_mainWindow = nullptr;
const char* glslVersion = NULL;
const unsigned int WINDOW_WIDTH = 1920;
const unsigned int WINDOW_HEIGHT = 1080;


int init(const char* caption = "Gomoku");
void processInput(GLFWwindow* window);
void errorCallback(int error, const char* description);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);


int init(const char* caption)
{
    if (glfwInit() == 0)
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return 0;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    g_mainWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, caption, NULL, NULL);
    if (g_mainWindow == NULL)
    {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return 0;
    }

    glfwMakeContextCurrent(g_mainWindow);
    glfwSetErrorCallback(errorCallback);
    glfwSetFramebufferSizeCallback(g_mainWindow, framebufferSizeCallback);

    // @TODO InputMode
    //glfwSetInputMode(g_mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // glfwSetInputMode(g_mainWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return 0;
    }

    // @TODO stb flip
    //stbi_set_flip_vertically_on_load(true);

    return 1;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    // @TODO
    // screen coordinate변환을 위해서 depth설정도 필요한데 (viewport포함)
    //glDepthRange(n, f);
}

void errorCallback(int error, const char* description)
{
    fprintf(stderr, "GLFW error occured. Code: %d. Description: %s\n", error, description);
}

#endif // MAIN_H