#ifndef DRAW_H
#define DRAW_H

#include <vector>
#include "shader.h"


class Grid
{
private:
    GLuint vao, vbo, ibo;
    GLuint length;
public:
    // https ://en.wikipedia.org/wiki/Gomoku
    const int Slices = 15;

	Grid(Shader& gridShader)
    {
        std::vector<glm::vec3> vertices;
        std::vector<glm::uvec4> indices;

        for (int j = 0; j <= Slices; ++j)
        {
            for (int i = 0; i <= Slices; ++i)
            {
                float x = (float)i / (float)Slices;
                float y = 0;
                float z = (float)j / (float)Slices;
                vertices.push_back(glm::vec3(x, y, z));
            }
        }

        for (int j = 0; j < Slices; ++j)
        {
            for (int i = 0; i < Slices; ++i)
            {
                int row1 = j * (Slices + 1);
                int row2 = (j + 1) * (Slices + 1);

                // upper-left 부터 counter-clock 방향으로 GL_LINE 렌더링 (2개씩 읽어들임)
                indices.push_back(glm::uvec4(row1 + i, row1 + i + 1, row1 + i + 1, row2 + i + 1));
                indices.push_back(glm::uvec4(row2 + i + 1, row2 + i, row2 + i, row1 + i));
            }
        }

        length = (GLuint)indices.size() * 4;

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), glm::value_ptr(vertices[0]), GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(glm::uvec4), glm::value_ptr(indices[0]), GL_STATIC_DRAW);

        // 초기화
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);


        gridShader.use();
        glm::mat4 model = glm::mat4(1.0f);
        // @TODO 0.5로 되는 이유
        model = glm::translate(model, glm::vec3(-0.5f, 0.0f, -0.5f));
        gridShader.setMat4("model", model);

        // https://www.schemecolor.com/weird-rainbow.php
        float r = (float)198 / (float)255;
        float g = (float)53 / (float)255;
        float b = (float)1 / (float)255;
        float a = 1.0f;
        gridShader.setFloat("color.r", r);
        gridShader.setFloat("color.g", g);
        gridShader.setFloat("color.b", b);
        gridShader.setFloat("color.a", a);
    }

    // @TODO 구현위치
    ~Grid()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ibo);
    }

	void Draw(Shader& gridShader)
	{
        glBindVertexArray(vao);
        glDrawElements(GL_LINES, length, GL_UNSIGNED_INT, NULL);
        glBindVertexArray(0);
	}
};

// https://blog.lapingames.com/draw-circle-glsl-shader/
class Circle
{
private:
    GLuint vao, vbo;
public:
    Circle(Shader& circleShader)
    {

    }

    // @TODO 구현위치
    ~Circle()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        //glDeleteBuffers(1, &ibo);
    }
};

#endif // DRAW_H 