#ifndef DRAW_H
#define DRAW_H

#include <vector>
#include "shader.h"


class Grid
{
private:
    GLuint vao, vbo, ibo;
    GLuint length;
    Shader& gridShader;
public:
    // https ://en.wikipedia.org/wiki/Gomoku
    const int Slices = 15;

	Grid(Shader& _gridShader) : gridShader(_gridShader)
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
        //float r = (float)198 / (float)255;
        //float g = (float)53 / (float)255;
        //float b = (float)1 / (float)255;
        //float a = 1.0f;
        gridShader.setFloat("color.r", 0.0f);
        gridShader.setFloat("color.g", 0.0f);
        gridShader.setFloat("color.b", 0.0f);
        gridShader.setFloat("color.a", 1.0f);
    }

    // @TODO 구현위치
    ~Grid()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ibo);
    }

	void Draw()
	{
        gridShader.use();
        glBindVertexArray(vao);
        glDrawElements(GL_LINES, length, GL_UNSIGNED_INT, NULL);
        glBindVertexArray(0);
	}
};

class RegularPolygon
{
private:
    GLuint vao, vbo;
    Shader& rpShader;
    int num;
    // @TODO
    //GLuint ibo;
public:
    // https://blog.lapingames.com/draw-circle-glsl-shader/
    RegularPolygon(Shader& _rpShader, int _num) : rpShader(_rpShader), num(_num)
    {
        std::vector<glm::vec3> vertices;
        vertices.reserve(num);
        
        float radius = 1.0f / 15 * 0.5f;

        double diff = (2 * glm::pi<double>()) / num;
        for (double i = 0; i < 2 * glm::pi<double>(); i += diff)
        {
            vertices.push_back(glm::vec3(cos(i) * radius, 0.0f, sin(i) * radius));
        }

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), glm::value_ptr(vertices[0]), GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        // @TODO 초기화 안해도되나?
        glBindVertexArray(0);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    // @TODO 구현위치
    ~RegularPolygon()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);

        // @TODO
        //glDeleteBuffers(1, &ibo);
    }

    void Draw(glm::vec3 translate = glm::vec3(0.0f), GLenum e = GL_LINE_LOOP)
    {
        rpShader.use();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(translate.x, translate.y, translate.z));
        rpShader.setMat4("model", model);

        glBindVertexArray(vao);
        glDrawArrays(e, 0, num);
        glBindVertexArray(0);
    }
};

#endif // DRAW_H 