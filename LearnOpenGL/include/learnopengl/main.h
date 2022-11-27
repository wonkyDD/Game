#ifndef MAIN_H
#define MAIN_H

// @NOTE
// Physx, bullet3, ImGui, ImGuizmo, freetype,   

#pragma comment(lib, "opengl32.lib")
// @TODO glfw3 release로 교체
#pragma comment(lib, "glfw3.lib")
// @NOTE assimp가 확실히 release에서 빠름
//#pragma comment(lib, "assimp-vc143-mtd.lib")
#pragma comment(lib, "assimp-vc143-mt.lib")
// @TODO box2d release로 교체
//#pragma comment(lib, "box2d.lib")


#include <stdio.h>
#include <assert.h>
#define ASSERT(x) assert(x)
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
// #include <imgui/imgui.h>
#include <learnopengl/shader.h>
#include <learnopengl/filesystem.h>
#include <learnopengl/camera.h>
//#include <learnopengl/mesh.h>
#include <learnopengl/model.h>


// @TODO
// 1. 함수 및 클래스 declare/define 분리?
// 2. 전역변수는 어디다 관리할 건지?
GLFWwindow* g_mainWindow = nullptr;
const char* glslVersion = NULL;
const unsigned int WINDOW_WIDTH = 1920;
const unsigned int WINDOW_HEIGHT = 1080;

float deltaTime = 0.0f;
float lastTime = 0.0f;

bool firstMouse = true;
float lastX = WINDOW_WIDTH / 2.0;
float lastY = WINDOW_HEIGHT / 2.0;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
int polygonMode = GL_TRIANGLES;


int init(const char* caption = "Testbed");
void processInput(GLFWwindow* window);
void cursorPosCallback(GLFWwindow* window, double xposIn, double yposIn);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void errorCallback(int error, const char* description);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);


// @TODO
// glfwInit, glfwCreateWindow, gladLoadGLLoader 별로
// 리턴하는 int값을 따로 만들어줄지? 아니면 enum을 따로 리턴해줄지?
// 
// @TODO 
// Enum 네이밍 방식? (EInit은 좀;;)

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
    glfwSetScrollCallback(g_mainWindow, scrollCallback);
    glfwSetCursorPosCallback(g_mainWindow, cursorPosCallback);

    // @TODO InputMode
    //glfwSetInputMode(g_mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // glfwSetInputMode(g_mainWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return 0;
    }

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);

    // @TODO shader 컴파일도 Init에서 처리하는 방법?
    // Shader mainShader("main_vs.hlsl", "main_fs.hlsl");
    //glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
    return 1;
}

// @TODO ImGUI와 box2d 의 createUI
// 
// void createUI()
// {
// 	IMGUI_CHECKVERSION();
// 	ImGui::CreateContext();

// 	bool success;
// 	success = ImGui_ImplGlfw_InitForOpenGL(g_mainWindow, false);
// 	if (success == false)
// 	{
// 		printf("ImGui_ImplGlfw_InitForOpenGL failed\n");
// 		assert(false);
// 	}

// 	success = ImGui_ImplOpenGL3_Init(glslVersion);
// 	if (success == false)
// 	{
// 		printf("ImGui_ImplOpenGL3_Init failed\n");
// 		assert(false);
// 	}

// 	// Search for font file
// 	const char* fontPath1 = "data/droid_sans.ttf";
// 	const char* fontPath2 = "../data/droid_sans.ttf";
// 	const char* fontPath = nullptr;
// 	FILE* file1 = fopen(fontPath1, "rb");
// 	FILE* file2 = fopen(fontPath2, "rb");
// 	if (file1)
// 	{
// 		fontPath = fontPath1;
// 		fclose(file1);
// 	}

// 	if (file2)
// 	{
// 		fontPath = fontPath2;
// 		fclose(file2);
// 	}

// 	if (fontPath)
// 	{
// 		ImGui::GetIO().Fonts->AddFontFromFileTTF(fontPath, 13.0f);
// 	}
// }

unsigned int loadTexture(const char* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format = NULL;
        if (nrComponents == 1)      format = GL_RED;
        else if (nrComponents == 3) format = GL_RGB;
        else if (nrComponents == 4) format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        fprintf(stderr, "Texture failed to load at path: %s\n", path);
        stbi_image_free(data);
    }

    return textureID;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.ProcessKeyboard(LEFT, deltaTime);

    // @TODO
    // ImGui로 ambient, specular의
    // intensity를 각각 조절하도록

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) polygonMode = GL_FILL;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) polygonMode = GL_LINE;
}

void cursorPosCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset, GL_TRUE);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void errorCallback(int error, const char* description)
{
    fprintf(stderr, "GLFW error occured. Code: %d. Description: %s\n", error, description);
}

#endif // MAIN_H