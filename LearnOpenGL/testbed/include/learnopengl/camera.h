#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 10.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


class Camera
{
public:
    glm::vec3 Position;
    glm::vec3 WorldUp;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    float Yaw;
    float Pitch;
    /** @todo Roll�� �ʿ��� ��� */
    // float Roll;
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    /** @todo WorldUp ���� */
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        /** @todo ���ڷ� �Ѿ�°� �ȿ��� �Ҵ�? */
        Position = position;
        WorldUp = worldUp;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    Camera(float posX, float posY, float posZ, float worldUpX, float worldUpY, float worldUpZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        /** @todo ���ڷ� �Ѿ�°� �ȿ��� �Ҵ�? */
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(worldUpX, worldUpY, worldUpZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    glm::mat4 GetViewMatrix()
    {
        /** @todo �׻� target�� position���� ���⺤�͸� ���Ѱ�? */
        return glm::lookAt(Position, Position + Front, Up);

        /** @todo Orthogonal Bases and Gram-Schmidt ���� */
        // return calculateLookAtMatrix(Position, Position + Front, Up);
    }

    void ProcessKeyboard(CameraMovement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)   Position += Front * velocity;
        if (direction == BACKWARD)  Position -= Front * velocity;
        if (direction == LEFT)      Position -= Right * velocity;
        if (direction == RIGHT)     Position += Right * velocity;
        // Position.y = 0.0f;
    }

    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        /** @todo sensitivity */
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        /** @todo yaw, pitch, roll */
        Yaw += xoffset;
        Pitch += yoffset;

        /** @todo �� ���� 89.0f */
        if (constrainPitch)
        {
            if (Pitch > 89.0f) Pitch = 89.0f;
            if (Pitch < -89.0f) Pitch = -89.0f;
        }

        updateCameraVectors();
    }

    void ProcessMouseScroll(float yoffset)
    {
        /**
         * @note
         * 1. scroll�� �ø� (offset ���)
         * -> ��������⸦ ����ϹǷ�,
         * fov�� �������
         *
         * 2. scroll�� ���� (offset ����)
         * -> �־����⸦ ����ϹǷ�,
         * fov�� ��������
        */
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f) Zoom = 1.0f;
        if (Zoom > 45.0f) Zoom = 45.0f;
    }

private:
    void updateCameraVectors()
    {
        /** @todo ��ݾ��� ���ĵ��� �ٿ� */
        /** @todo Roll�� �ʿ��� ��� */
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }

    glm::mat4 calculateLookAtMatrix(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp)
    {
        // https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/7.6.camera_exercise2/camera_exercise2.cpp

        glm::vec3 zaxis = glm::normalize(glm::vec3(position - target));
        glm::vec3 xaxis = glm::normalize(glm::cross(glm::normalize(worldUp), zaxis));
        glm::vec3 yaxis = glm::cross(zaxis, xaxis);

        // In glm we access elements as mat[col][row] due to column-major layout
        glm::mat4 translation = glm::mat4(1.0f);
        translation[3][0] = -position.x; // Third column, first row
        translation[3][1] = -position.y;
        translation[3][2] = -position.z;

        glm::mat4 rotation = glm::mat4(1.0f);
        rotation[0][0] = xaxis.x; // First column, first row
        rotation[1][0] = xaxis.y;
        rotation[2][0] = xaxis.z;
        rotation[0][1] = yaxis.x; // First column, second row
        rotation[1][1] = yaxis.y;
        rotation[2][1] = yaxis.z;
        rotation[0][2] = zaxis.x; // First column, third row
        rotation[1][2] = zaxis.y;
        rotation[2][2] = zaxis.z;

        return rotation * translation;
    }
};
#endif