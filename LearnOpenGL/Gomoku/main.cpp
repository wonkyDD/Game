/*
* @TODO
* - feat: google test & in-game logic error => dump to json or txt file
* - feat: STB ui reconstruct, add textures
* - feat: ImGui button-gamestart
* - feat: ImGui button-settings
* - feat: ImGui tab-chatbox
* - feat: ImGui tab-userinfo
* - feat: ImGui scene-gameover
* - feat: FMOD bgm
* - feat: FMOD place circle success or fail (by rule)
* - feat: FMOD button click
* 
* @NOTE
* - feat: multiplay
* - feat: timer
* - feat: FMOD timer
* - feat: AI (reinforced learning) gym + pygame => porting to c++, networking with python
*/
#include "main.h"

int main()
{
    // @TODO set enum for each of error codes
    if (init() == 0) return -1;

    /*
    * @TODO test (google test)
    * - pass fail => abort
    * - only test when debug mode
    * 
    */

    // @TODO reuse compiled shaders
    // @TODO copy into build folder
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
            if (isLeftReleased && !game.circles[z][x].placed)
            {
                 bool go = game.CheckGameOver(z, x);
                 bool rule = game.CheckRule(z, x);
                 
                 if (!rule)
                 {
                     game.circles[z][x].placed = true;
                     game.circles[z][x].isBlack = rp.isBlack;
                     rp.isBlack = !rp.isBlack;
                     isLeftReleased = false;
                 }
                 else
                 {
                     isLeftReleased = false;
                 }

                //game.circles[z][x].placed = true;
                //game.circles[z][x].isBlack = rp.isBlack;
                //rp.isBlack = !rp.isBlack;
                //isLeftReleased = false;
            }

            // after release set release status as false
            if (isLeftReleased && game.circles[z][x].placed)
            {
                isLeftReleased = false;
            }

            // draw hovering effect
            if (!game.circles[z][x].placed)
            {
                rp.alpha = rp.hoveringAlpha;
                rp.Draw(glm::vec3(mousePos.x, 0.0f, mousePos.z), GL_TRIANGLE_FAN);
            }
        }

        for (int i = 0; i <= grid.Slices; ++i)
        {
            for (int j = 0; j <= grid.Slices; ++j)
            {
                if (game.circles[i][j].placed)
                {
                    bool btemp = rp.isBlack;
                    float ftemp = rp.alpha;

                    rp.isBlack = game.circles[i][j].isBlack;
                    rp.alpha = rp.placedAlpha;
                    // @TODO circles[x][z] vs circles[z][x]
                    //rp.Draw(glm::vec3(-0.5f + step*i, 0.0f, -0.5f + step * j), GL_TRIANGLE_FAN);
                    rp.Draw(glm::vec3(-0.5f + step*j, 0.0f, -0.5f + step * i), GL_TRIANGLE_FAN);
                    
                    rp.isBlack = btemp;
                    rp.alpha = ftemp;
                }
            }
        }

        /*
        * @TODO
        * - feat: scene separation?
        * - feat: UI class
        * - feat: line debug drawing; gameover
        * - feat: line debug drawing; rule (33, 6)
        * - feat: tab key -> glassmorphism shader lerp
        */

        glfwSwapBuffers(g_mainWindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
