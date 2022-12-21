/** 
* v0.1.0 : feat-game (gameover + renzurule(33, 6))
* 
* 
* @TODO
* - refactor:   main.cpp
* - fix:        test GLFW resolution, (primary) monitor
* - feat:       glassmorphism on background when game-over
* - feat:       setup UI flow using imgui-GLFW
* - feat:       add textures(grid, circle, mouse) using stb_image
* - feat:       `gameover + ~ win` image with text using stb_image
* - feat:       multiplay (chat, room) using WinSock2
* - feat:       timer
* - feat:       sound features (bgm, circle-placed sound, timer sound) using OpenAL or FMOD
*/

#include "main.h"
// @TODO class for game manager?
#define GRID_SLICES 15

// @TODO class for game manager?
struct Circle
{
    bool placed = false;
    bool isBlack = true;
};


int main()
{
    // @TODO set enum for each of error codes
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
    RegularPolygon rp(rpShader);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // @TODO class for game manager?
    Circle placed[GRID_SLICES][GRID_SLICES];

    while (!glfwWindowShouldClose(g_mainWindow))
    {
        processInput(g_mainWindow);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float xpos = -0.5f, zpos = -0.5f;
        // @TODO change 1.0f with grid width or height length
        const float step = 1.0f / grid.Slices;
        const float radius = rp.Radius;

        int x, z;
        bool b = true;

        for (x = 0; x <= grid.Slices; ++x)
        {
            if (mousePos.x >= (xpos + step*x) - radius && mousePos.x <= (xpos + step * x) + radius)
            {
                mousePos.x = xpos + step * x;
                break;
            }
        }

        if (x == grid.Slices + 1) b = false;

        for (z = 0; z <= grid.Slices; ++z)
        {
            if (mousePos.z >= (zpos + step * z) - radius && mousePos.z <= (zpos + step * z) + radius)
            {
                mousePos.z = zpos + step * z;
                break;
            }
        }

        if (z == grid.Slices + 1) b = false;

        mousePos.x = Math::clamp<float>(mousePos.x, -0.5f, 0.5f);
        mousePos.z = Math::clamp<float>(mousePos.z, -0.5f, 0.5f);

        grid.Draw();
        // @TODO i==15 but pass clamp test area (float-type issue?)
        // @HACK not render in this case
        if (b)
        {
            if (isLeftReleased && !placed[x][z].placed)
            {
                placed[x][z].placed = true;
                placed[x][z].isBlack = rp.isBlack;
                rp.isBlack = !rp.isBlack;
                isLeftReleased = false;
            }

            if (!placed[x][z].placed)
            {
                rp.alpha = 0.5f;
                rp.Draw(glm::vec3(mousePos.x, 0.0f, mousePos.z), GL_TRIANGLE_FAN);
            }
        }

        for (int i = 0; i <= grid.Slices; ++i)
        {
            for (int j = 0; j <= grid.Slices; ++j)
            {
                if (placed[i][j].placed)
                {
                    bool btemp = rp.isBlack;
                    float ftemp = rp.alpha;

                    rp.isBlack = placed[i][j].isBlack;
                    rp.alpha = 1.0f;
                    rp.Draw(glm::vec3(-0.5f + step*i, 0.0f, -0.5f + step * j), GL_TRIANGLE_FAN);
                    
                    rp.isBlack = btemp;
                    rp.alpha = ftemp;
                }
            }
        }

        /*
        * @TODO
        * 
        */

        glfwSwapBuffers(g_mainWindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
