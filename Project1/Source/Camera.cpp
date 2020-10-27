#include "Camera.h"

Camera::Camera(float Yaw, float Pitch, float LastX, float LastY, float Fov, bool FirstMouse, glm::vec3 CameraPos, glm::vec3 CameraFront, glm::vec3 CameraUp, float DeltaTime, float LastFrame, float CurrentFrame)
{
    yaw = Yaw;
    pitch = Pitch;
    lastX = LastX;
    lastY = LastY;
    fov = Fov;
    firstMouse = FirstMouse;
    cameraPos = CameraPos;
    cameraFront = CameraFront;
    cameraUp = CameraUp;
    deltaTime = DeltaTime;
    lastFrame = LastFrame;
    currentFrame = LastFrame;
}


void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

void Camera::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (fov > 1.0f && fov <= 90.0f)
        fov -= yoffset;
    else if (fov <= 1.0f)
        fov = 1.0f;
    else if (fov >= 90.0f)
        fov = 45.0f;
}

void Camera::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    const float cameraSpeed = 2.5 * deltaTime; // adjust accordingly
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

float Camera::return_fov()
{
    return fov;
}

void Camera::calcDelta()
{
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

glm::mat4 Camera::LookAtFunc()
{
    glm::vec3 posZ = glm::normalize(cameraPos - (cameraPos + cameraFront));
    glm::vec3 posX = glm::normalize(glm::cross(normalize(cameraUp), posZ));
    glm::vec3 posY = glm::cross(posX, posZ);

    glm::mat4 translation = glm::mat4(1.0f);
    translation[3][0] = -cameraPos.x;
    translation[3][1] = -cameraPos.y;
    translation[3][2] = -cameraPos.z;

    glm::mat4 rotation = glm::mat4(1.0f);
    rotation[0][0] = posX.x;
    rotation[1][0] = posX.y;
    rotation[2][0] = posX.z;
    rotation[0][1] = posY.x;
    rotation[1][1] = posY.y;
    rotation[2][1] = posY.z;
    rotation[0][2] = posZ.x;
    rotation[1][2] = posZ.y;
    rotation[2][2] = posZ.z;

    return rotation * translation;
}

void Camera::setInputs(GLFWwindow* window, Camera &camera)
{
    glfwSetWindowUserPointer(window, &camera);

    auto mouse_cb = [](GLFWwindow* w, double xpos, double ypos)
    {
        static_cast<Camera*>(glfwGetWindowUserPointer(w))->mouse_callback(w, xpos, ypos);
    };

    auto scroll_cb = [](GLFWwindow* w, double xoffset, double yoffset)
    {
        static_cast<Camera*>(glfwGetWindowUserPointer(w))->scroll_callback(w, xoffset, yoffset);
    };

    glfwSetCursorPosCallback(window, mouse_cb);
    glfwSetScrollCallback(window, scroll_cb);
}
