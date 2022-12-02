#include "main.h"


int main()
{
    // @TODO Enum ºÐ·ù
    if (init() == 0) return -1;

    Shader gridShader("grid_vs.hlsl", "grid_fs.hlsl");
    Shader circleShader("circle_vs.hlsl", "circle_fs.hlsl");

    gridShader.use();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    gridShader.setMat4("projection", projection);
    gridShader.setMat4("view", view);

    float r = (float)110 / (float)255;
    float g = (float)124 / (float)255;
    float b = (float)116 / (float)255;
    float a = 1.0f;
    glClearColor(r, g, b, a);


    // @TODO screen space -> clip/view/world(?) space
    // https://stackoverflow.com/questions/7692988/opengl-math-projecting-screen-space-to-world-space-coords


    Grid grid(gridShader);

    while (!glfwWindowShouldClose(g_mainWindow))
    {
        processInput(g_mainWindow);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        grid.Draw(gridShader);

        glfwSwapBuffers(g_mainWindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
