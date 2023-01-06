#pragma once
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glfw3.lib")
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"

GLFWwindow* g_mainWindow = nullptr;
const unsigned int WINDOW_WIDTH = 1920;
const unsigned int WINDOW_HEIGHT = 1080;
//const unsigned int WINDOW_WIDTH = 2160;
//const unsigned int WINDOW_HEIGHT = 1920;

int init(const char* caption = "ShaderIDE");
void processInput(GLFWwindow* window);
void errorCallback(int error, const char* description);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

int init(const char* caption)
{
#if defined(_DEBUG)
    //printf("//////////////////\n");
    //printf("//  DEBUG MODE  //\n");
    //printf("//////////////////\n");
    // @TODO change lib depening on IDE build mode (+ add glfw release build option)
#endif
    if (glfwInit() == 0)
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return 0;
    }

    // https://stackoverflow.com/questions/67239235/how-do-i-create-a-centered-glfw-window
    int count, monitorX, monitorY;
    GLFWmonitor** monitors = glfwGetMonitors(&count);
    // @TODO monitor index
    const GLFWvidmode* videoMode = glfwGetVideoMode(monitors[0]);
    glfwGetMonitorPos(monitors[0], &monitorX, &monitorY);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // @TODO independent of resize issue
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    // @TODO no title bar
    //glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
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

    glfwSetWindowPos(g_mainWindow,
        monitorX + (videoMode->width - WINDOW_WIDTH) / 2,
        monitorY + (videoMode->height - WINDOW_HEIGHT) / 2);
    //glfwShowWindow(g_mainWindow);

    glfwMakeContextCurrent(g_mainWindow);
    glfwSetErrorCallback(errorCallback);
    glfwSetFramebufferSizeCallback(g_mainWindow, framebufferSizeCallback);

    // @TODO InputMode
    //glfwSetInputMode(g_mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //glfwSetInputMode(g_mainWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

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
    // @NOTE screen coordinate transform == glViewport + glDepthRange
    //glDepthRange(n, f);
}

void errorCallback(int error, const char* description)
{
    fprintf(stderr, "GLFW error occured. Code: %d. Description: %s\n", error, description);
}
