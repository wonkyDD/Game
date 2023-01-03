/*
* @TODO : " " vs < >
* - glad, glfw, stb, glm, imgui, yyjson, fmod, freetype, imguizmo, assimp, ffmpeg
* 
*/
#pragma once
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui/imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "yyjson/yyjson.h"
#include "shader.h"
#include "camera.h"
#include "draw.h"
#include "math.h"
#include "game.h"
//#include <fmod/fmod.hpp>

// @TODO change lib depening on IDE build mode (+ add glfw release build option)
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glfw3.lib")
// @TODO fmodL vs fmod
//#pragma comment(lib, "fmod_vc.lib")
//#pragma comment(lib, "fmodL_vc.lib")

GLFWwindow* g_mainWindow = nullptr;
const unsigned int WINDOW_WIDTH = 1600;
const unsigned int WINDOW_HEIGHT = 1600;
Camera camera(glm::vec3(0.0f, 3.0f, 0.0f));
glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
glm::vec3 mousePos = glm::vec3(0.0f);
// @TODO make Game class as singletone
Game game;
// @TODO input manager
bool isLeftReleased = false;
//bool isSPressed= false;

int init(const char* caption = "Gomoku");
void processInput(GLFWwindow* window);
void errorCallback(int error, const char* description);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void cursorPosCallback(GLFWwindow* window, double xposIn, double yposIn);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);


int init(const char* caption)
{
#if defined(_DEBUG)
    //printf("//////////////////\n");
    //printf("//  DEBUG MODE  //\n");
    //printf("//////////////////\n");

    // @TODO change lib depening on IDE build mode (+ add glfw release build option)
#endif // _DEBUG

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
    glfwSetCursorPosCallback(g_mainWindow, cursorPosCallback);
    glfwSetMouseButtonCallback(g_mainWindow, mouseButtonCallback);

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

    //if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && !isSPressed)
    //{
    //    isSPressed = true;
    //}

    //if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE && isSPressed)
    //{
    //    isSPressed = false;
    //    game.CheckGameOver();
    //}
}

void cursorPosCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    float x_ndc = 2 * (xpos / WINDOW_WIDTH) - 1.0;
    float y_ndc = - 2 * (ypos / WINDOW_HEIGHT) + 1.0;
    glm::mat4 screen2world = glm::inverse(projection * camera.GetViewMatrix());

    // @TODO y_ndc pos
    //glm::vec4 screenMousePos = glm::vec4(x_ndc, 0.0f, y_ndc, 1.0f);
    //glm::vec4 screenMousePos = glm::vec4(x_ndc, -1.0f, y_ndc, 1.0f);

    // @TODO 0.0 vs -1.0
    //glm::vec4 screenMousePos = glm::vec4(x_ndc, y_ndc, -1.0f, 1.0f);
    glm::vec4 screenMousePos = glm::vec4(x_ndc, y_ndc, 0.0f, 1.0f);
    glm::vec4 worldMousePos = screen2world * screenMousePos;

    // @TODO reason why multiplied by value equal to cameraPos.y
    worldMousePos.x *= 3.0f;
    worldMousePos.z *= 3.0f;

    mousePos.x = worldMousePos.x;
    mousePos.y = 0.0f;
    mousePos.z = worldMousePos.z;
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        //printf("press\n");
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        //printf("release\n");
        isLeftReleased = true;
    }
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
