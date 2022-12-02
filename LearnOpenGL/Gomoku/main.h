#ifndef MAIN_H
#define MAIN_H

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "camera.h"
#include "draw.h"
#include "UI.h"

// @TODO lib를 ide빌드가 release, debug 인지에 따라 알맞게 바꿔줄것
// (glfw release빌드 추가)
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glfw3.lib")


GLFWwindow* g_mainWindow = nullptr;
const char* glslVersion = NULL;
const unsigned int WINDOW_WIDTH = 1600;
const unsigned int WINDOW_HEIGHT = 1600;
// @TODO
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
Camera camera(glm::vec3(0.0f, 3.0f, 0.0f));


int init(const char* caption = "Gomoku");
void processInput(GLFWwindow* window);
void errorCallback(int error, const char* description);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void cursorPosCallback(GLFWwindow* window, double xposIn, double yposIn);


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
    glfwSetCursorPosCallback(g_mainWindow, cursorPosCallback);

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

void cursorPosCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    // @TODO screen space -> clip/view/world(?) space
    // https://stackoverflow.com/questions/7692988/opengl-math-projecting-screen-space-to-world-space-coords


    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    //printf("%f  %f\n", xpos, ypos);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    // @TODO screen coordinate변환을 위해서 depth설정도 필요한데 (viewport포함)
    //glDepthRange(n, f);
}

void errorCallback(int error, const char* description)
{
    fprintf(stderr, "GLFW error occured. Code: %d. Description: %s\n", error, description);
}

#endif // MAIN_H