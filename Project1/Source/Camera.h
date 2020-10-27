#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Camera {
public:

    float yaw;
    float pitch;
    float lastX;
    float lastY;
    float fov;
    bool firstMouse;
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    float deltaTime;
    float lastFrame;
    float currentFrame;

     Camera(
         float Yaw = -90.0f,
         float Pitch = 0.0f,

         float LastX = 400,
         float LastY = 300,
         float Fov = 90.f,

         bool FirstMouse = true,

         glm::vec3 CameraPos = glm::vec3(0.0f, 0.0f, 3.0f),
         glm::vec3 CameraFront = glm::vec3(0.0f, 0.0f, -1.0f),
         glm::vec3 CameraUp = glm::vec3(0.0f, 1.0f, 0.0f),

         float DeltaTime = 0.0f,
         float LastFrame = 0.0f,

         float CurrentFrame = glfwGetTime())
        ;

    void setInputs(GLFWwindow* window, Camera &camera);

    void mouse_callback(GLFWwindow* window, double xpos, double ypos);

    void scroll_callback(GLFWwindow* window, double xpos, double ypos);

    void processInput(GLFWwindow* window);

    glm::mat4 GetViewMatrix();

    float return_fov();
    void calcDelta();

    glm::mat4 LookAtFunc();

private:
};