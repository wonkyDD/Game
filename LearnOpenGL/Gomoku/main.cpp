#include "main.h"


int main()
{
    // @TODO Enum ºÐ·ù
    if (init() == 0) return -1;

    Shader gridShader("grid_vs.hlsl", "grid_fs.hlsl");
    Shader rpShader("regular_polygon_vs.hlsl", "regular_polygon_fs.hlsl");


    gridShader.use();
    gridShader.setMat4("projection", projection);
    gridShader.setMat4("view", camera.GetViewMatrix());

    rpShader.use();
    rpShader.setMat4("projection", projection);
    rpShader.setMat4("view", camera.GetViewMatrix());

    float r = (float)110 / (float)255;
    float g = (float)124 / (float)255;
    float b = (float)116 / (float)255;
    float a = 1.0f;
    glClearColor(r, g, b, a);


    Grid grid(gridShader);
    RegularPolygon rp(rpShader, 1000);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(g_mainWindow))
    {
        processInput(g_mainWindow);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        grid.Draw();
        rp.Draw(glm::vec3(mousePos.x, 0.0f, mousePos.z), GL_TRIANGLE_FAN);

        glfwSwapBuffers(g_mainWindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
