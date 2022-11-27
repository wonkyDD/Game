#include <learnopengl/main.h>

int main()
{
    // @TODO Enum 
    if (init() == 0) return -1;

    Shader mainShader("main_vs.hlsl", "main_fs.hlsl");
    Model ourBackpack("../resources/objects/backpack/backpack.obj");

    // @TODO pbr텍스쳐 (AO, roughness, metalic)
    Model ourGun("../resources/objects/fn-spr-a3g/spr_a3g.obj");


    while (!glfwWindowShouldClose(g_mainWindow))
    {
        float currentTime = static_cast<float>(glfwGetTime());
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        processInput(g_mainWindow);
        glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mainShader.use();

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        mainShader.setMat4("projection", projection);
        mainShader.setMat4("view", view);

        glm::mat4 backModel = glm::mat4(1.0f);
        // @TODO 중앙에 위치, scale down
        backModel = glm::translate(backModel, glm::vec3(0.0f, 0.0f, 0.0f));
        backModel = glm::scale(backModel, glm::vec3(1.0f, 1.0f, 1.0f));
        backModel = glm::rotate(backModel, currentTime, glm::vec3(0.0f, 1.0f, 0.0f));
        mainShader.setMat4("model", backModel);
        ourBackpack.Draw(mainShader);


        glm::mat4 gunModel = glm::mat4(1.0f);
        gunModel = glm::translate(gunModel, glm::vec3(7.0f, 0.0f, 0.0f));
        gunModel = glm::scale(gunModel, glm::vec3(1.0f, 1.0f, 1.0f));
        gunModel = glm::rotate(gunModel, currentTime, glm::vec3(0.5f, 1.0f, 0.0f));
        mainShader.setMat4("model", gunModel);
        ourGun.Draw(mainShader);

        glfwSwapBuffers(g_mainWindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}