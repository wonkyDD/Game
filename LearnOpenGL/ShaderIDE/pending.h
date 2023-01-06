#pragma once
#include "main.h"
#include "shader.h"

namespace Pending
{
    int gradation()
    {
        // @TODO set enum for each of error codes
        if (init() == 0) return -1;
        Shader mainShader("gradation_vs.hlsl", "gradation_fs.hlsl");

        float vertices[] =
        {
            -1.0f, 1.0f,  0.0f,
            -1.0f, -1.0f, 0.0f,
            1.0f,  -1.0f, 0.0f,
            1.0f, 1.0f, 0.0f
        };
        unsigned int indices[] =
        {
            0, 1, 2,
            2, 0, 3
        };
        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        while (!glfwWindowShouldClose(g_mainWindow))
        {
            processInput(g_mainWindow);
            glClear(GL_COLOR_BUFFER_BIT);

            mainShader.use();
            float timeValue = static_cast<float>(glfwGetTime());
            int timeLocation = glGetUniformLocation(mainShader.ID, "time");
            glUniform1f(timeLocation, timeValue);
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            glfwSwapBuffers(g_mainWindow);
            glfwPollEvents();
        }

        glfwTerminate();
        return 0;
    }

    int smoothCircle()
    {
        return 0;
    }

    int glassMorphism()
    {
        return 0;
    }
}
