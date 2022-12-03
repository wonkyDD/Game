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
        
        float radius = 0.5;
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

        rpShader.use();
        glm::mat4 model = glm::mat4(1.0f);
        rpShader.setMat4("model", model);
    }

    // @TODO 구현위치
    ~RegularPolygon()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);

        // @TODO
        //glDeleteBuffers(1, &ibo);
    }

    void DrawLoop()
    {
        rpShader.use();
        glBindVertexArray(vao);
        glDrawArrays(GL_LINE_LOOP, 0, num);
        glBindVertexArray(0);
    }

    void DrawFan()
    {
        rpShader.use();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLE_FAN, 0, num);
        glBindVertexArray(0);
    }
};

class Circle
{
private:
    GLuint vao, vbo;
    Shader& circleShader;
    // @TODO
    //GLuint ibo;
public:
    // https://blog.lapingames.com/draw-circle-glsl-shader/
    Circle(Shader& _circleShader) : circleShader(_circleShader)
    {
        float right = 0.5;
        float bottom = -0.5;
        float left = -0.5;
        float top = 0.5;
        float quad[20] = 
        {
            //x, y, z,          // lx, ly
            right, 0, bottom,   1.0, -1.0,
            right, 0, top,      1.0, 1.0,
            left, 0, top,       -1.0, 1.0,
            left, 0, bottom,    -1.0, -1.0,
        };

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 20, quad, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 20, 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 20, (void*)(sizeof(float) * 3));
        // @NOTE
        //#define BUFFER_OFFSET(i) ((char *)NULL + (i))
        //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 20, BUFFER_OFFSET(12));


        // @TODO 초기화 안해도되나?
        glBindVertexArray(0);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        circleShader.use();
        glm::mat4 model = glm::mat4(1.0f);
        circleShader.setMat4("model", model);
    }

    void Draw()
    {
        circleShader.use();
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }
};

#endif // DRAW_H 