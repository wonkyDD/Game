#include "main.h"


int main()
{
    if (init() == 0) return -1;

    Shader mainShader("main_vs.hlsl", "main_fs.hlsl");

    std::vector<glm::vec3> vertices;
    std::vector<glm::uvec4> indices;

    // https://stackoverflow.com/questions/7692988/opengl-math-projecting-screen-space-to-world-space-coords

    // https://stackoverflow.com/questions/58494179/how-to-create-a-grid-in-opengl-and-drawing-it-with-lines
    // https://en.wikipedia.org/wiki/Gomoku
    const int slices = 15;
    for (int j = 0; j <= slices; ++j) 
    {
        for (int i = 0; i <= slices; ++i) 
        {
            float x = (float)i / (float)slices;
            float y = 0;
            float z = (float)j / (float)slices;
            vertices.push_back(glm::vec3(x, y, z));
        }
    }

    for (int j = 0; j < slices; ++j) 
    {
        for (int i = 0; i < slices; ++i) 
        {
            int row1 = j * (slices + 1);
            int row2 = (j + 1) * (slices + 1);

            // upper-left 부터 counter-clock 방향으로 GL_LINE 렌더링 (2개씩 읽어들임)
            indices.push_back(glm::uvec4(row1 + i, row1 + i + 1, row1 + i + 1, row2 + i + 1));
            indices.push_back(glm::uvec4(row2 + i + 1, row2 + i, row2 + i, row1 + i));
        }
    }

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), glm::value_ptr(vertices[0]), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(glm::uvec4), glm::value_ptr(indices[0]), GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint length = (GLuint)indices.size() * 4;

    mainShader.use();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    mainShader.setMat4("projection", projection);
    mainShader.setMat4("view", view);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!glfwWindowShouldClose(g_mainWindow))
    {
        processInput(g_mainWindow);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
        glBindVertexArray(vao);

        mainShader.use();
        glm::mat4 model = glm::mat4(1.0f);
        // @TODO 0.5로 되는 이유
        model = glm::translate(model, glm::vec3(-0.5f, 0.0f, -0.5f));
        mainShader.setMat4("model", model);
        
        
        glDrawElements(GL_LINES, length, GL_UNSIGNED_INT, NULL);

        glBindVertexArray(0);
        glDisable(GL_DEPTH_TEST);

        glfwSwapBuffers(g_mainWindow);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);

    glfwTerminate();
    return 0;
}
