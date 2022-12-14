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

// @TODO lib�� ide���尡 release, debug ������ ���� �˸°� �ٲ��ٰ�
// (glfw release���� �߰�)
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glfw3.lib")


GLFWwindow* g_mainWindow = nullptr;
const char* glslVersion = NULL;
const unsigned int WINDOW_WIDTH = 1600;
const unsigned int WINDOW_HEIGHT = 1600;
// @TODO
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
Camera camera(glm::vec3(0.0f, 3.0f, 0.0f));
glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
glm::vec3 mousePos = glm::vec3(0.0f);

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
    // @TODO screen space -> world space
    // https://stackoverflow.com/questions/7692988/opengl-math-projecting-screen-space-to-world-space-coords
    // https://stackoverflow.com/questions/46749675/opengl-mouse-coordinates-to-space-coordinates/46752492#46752492
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);


    // 1. mousePos�� ndc�� ��ȯ
    float x_ndc = 2 * (xpos / WINDOW_WIDTH) - 1.0;
    float y_ndc = - 2 * (ypos / WINDOW_HEIGHT) + 1.0;


    // 2. screen -> world�� ������ȯ
    glm::mat4 screen2world = glm::inverse(projection * camera.GetViewMatrix());


    // @TODO y_ndc��ġ�� 0.0�� �ƴ� -1.0
    //glm::vec4 screenMousePos = glm::vec4(x_ndc, 0.0f, y_ndc, 1.0f);
    //glm::vec4 screenMousePos = glm::vec4(x_ndc, -1.0f, y_ndc, 1.0f);
    

    // @TODO 0.0 vs -1.0
    //glm::vec4 screenMousePos = glm::vec4(x_ndc, y_ndc, 0.0f, 1.0f);
    glm::vec4 screenMousePos = glm::vec4(x_ndc, y_ndc, -1.0f, 1.0f);
    glm::vec4 worldMousePos = screen2world * screenMousePos;

    // @TODO unProject ���
    //glm::unProject()


    // @TODO w�� ������� �ϴ°�?
    //worldMousePos.x /= worldMousePos.w;
    //worldMousePos.z /= worldMousePos.w;
    
    // @TODO 
    // �� ���� ī�޶� y��ǥ�� �����ϰ� ������� �ϴ���?
    worldMousePos.x *= 3.0f;
    worldMousePos.z *= 3.0f;
    printf("%f  %f\n", worldMousePos.x, worldMousePos.z);

    mousePos.x = worldMousePos.x;
    mousePos.y = 0.0f;
    mousePos.z = worldMousePos.z;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    // @TODO screen coordinate��ȯ�� ���ؼ� depth������ �ʿ��ѵ� (viewport����)
    //glDepthRange(n, f);
}

void errorCallback(int error, const char* description)
{
    fprintf(stderr, "GLFW error occured. Code: %d. Description: %s\n", error, description);
}

#endif // MAIN_H