#include "main.h"


int main()
{
    // @TODO Enum ºÐ·ù
    if (init() == 0) return -1;

    Shader gridShader("grid_vs.hlsl", "grid_fs.hlsl");
    Shader rpShader("regular_polygon_vs.hlsl", "regular_polygon_fs.hlsl");
    //Shader circleShader("circle_vs.hlsl", "circle_fs.hlsl");


    gridShader.use();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    gridShader.setMat4("projection", projection);
    gridShader.setMat4("view", view);

    rpShader.use();
    rpShader.setMat4("projection", projection);
    rpShader.setMat4("view", view);
    //circleShader.use();
    //circleShader.setMat4("projection", projection);
    //circleShader.setMat4("view", view);

    float r = (float)110 / (float)255;
    float g = (float)124 / (float)255;
    float b = (float)116 / (float)255;
    float a = 1.0f;
    glClearColor(r, g, b, a);


    // @TODO screen space -> clip/view/world(?) space
    // https://stackoverflow.com/questions/7692988/opengl-math-projecting-screen-space-to-world-space-coords
    // https://www.songho.ca/opengl/gl_projectionmatrix.html


    Grid grid(gridShader);
    RegularPolygon rp(rpShader, 40);
    //Circle circle(circleShader);
    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(g_mainWindow))
    {
        processInput(g_mainWindow);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        grid.Draw();
        rp.DrawLoop();
        //circle.Draw();


        glfwSwapBuffers(g_mainWindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
