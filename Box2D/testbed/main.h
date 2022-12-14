#ifndef MAIN_H
#define MAIN_H

#define _CRT_SECURE_NO_WARNINGS
#if defined(_WIN32)
#include <crtdbg.h>
#endif
#include <stdio.h>
//#include <assert.h>
#include <chrono>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// @TODO ImGui
#include "imgui/imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "draw.h"

// @TODO lib를 ide빌드가 release, debug 인지에 따라 알맞게 바꿔줄것
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glfw3.lib")

//#define ASSERT(x) assert(x) 

GLFWwindow* g_mainWindow = nullptr;
const unsigned int WINDOW_WIDTH = 1920;
const unsigned int WINDOW_HEIGHT = 1080;

int init(const char* caption = "testbed");
void createUI(GLFWwindow* g_mainWindow, const char* glslVersion = nullptr);
void updateUI();
void processInput(GLFWwindow* window);
void errorCallback(int error, const char* description);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);


// @TODO Enum으로 에러분류
int init(const char* caption)
{
#if defined(_WIN32)
    // Enable memory-leak reports
    _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG));
#endif

    if (glfwInit() == 0)
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
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
        return -1;
    }

    glfwMakeContextCurrent(g_mainWindow);
    //glfwSwapInterval(1); // Enable vsync
    glfwSetErrorCallback(errorCallback);
    glfwSetFramebufferSizeCallback(g_mainWindow, framebufferSizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    return 0;
}

void createUI(GLFWwindow* g_mainWindow, const char* glslVersion)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    bool success;
    success = ImGui_ImplGlfw_InitForOpenGL(g_mainWindow, false);
    if (success == false)
    {
        printf("ImGui_ImplGlfw_InitForOpenGL failed\n");
        assert(false);
    }

    // @TODO glslVersion과 nullptr
    //const char* glsl_version = "#version 460";
    success = ImGui_ImplOpenGL3_Init(glslVersion);
    if (success == false)
    {
        printf("ImGui_ImplOpenGL3_Init failed\n");
        assert(false);
    }


    // @TODO font 설정: imgui샘플, box2d

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    // Search for font file
    //const char* fontPath1 = "data/droid_sans.ttf";
    //const char* fontPath2 = "../data/droid_sans.ttf";
    //const char* fontPath = nullptr;
    //FILE* file1 = fopen(fontPath1, "rb");
    //FILE* file2 = fopen(fontPath2, "rb");
    //if (file1)
    //{
    //    fontPath = fontPath1;
    //    fclose(file1);
    //}

    //if (file2)
    //{
    //    fontPath = fontPath2;
    //    fclose(file2);
    //}

    //if (fontPath)
    //{
    //    ImGui::GetIO().Fonts->AddFontFromFileTTF(fontPath, 13.0f);
    //}


    // @TODO glfwPollEvents 위치
    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    //glfwPollEvents();
}

void updateUI()
{

}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}

void errorCallback(int error, const char* description)
{
    fprintf(stderr, "GLFW error occured. Code: %d. Description: %s\n", error, description);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    // @TODO screen coordinate변환을 위해서 depth설정도 필요한데 (viewport포함)
    //glDepthRange(n, f);

    // @TODO 아래를 렌더루프에서 glfwSetFrameBufferSizeCallback 대신에 실행하는 것이 동치인가?
    //int bufferWidth, bufferHeight;
    //glfwGetFramebufferSize(g_mainWindow, &bufferWidth, &bufferHeight);
    //glViewport(0, 0, bufferWidth, bufferHeight);
}

#endif // MAIN_H
