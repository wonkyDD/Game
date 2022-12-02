#include <gomoku/main.h>


int main()
{
    if (init() == 0) return -1;

    Shader mainShader("main_vs.hlsl", "main_fs.hlsl");

    float vertices[] = {
        -1.0f, 1.0f,  0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f,  -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f
    };

    unsigned int indices[] = {
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

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    while (!glfwWindowShouldClose(g_mainWindow))
    {
        processInput(g_mainWindow);
        glClear(GL_COLOR_BUFFER_BIT);

        mainShader.use();
        glBindVertexArray(VAO);

        float timeValue = static_cast<float>(glfwGetTime());
        int timeLocation = glGetUniformLocation(mainShader.ID, "time");
        glUniform1f(timeLocation, timeValue);

        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(g_mainWindow);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, & EBO);

    glfwTerminate();
    return 0;
}
