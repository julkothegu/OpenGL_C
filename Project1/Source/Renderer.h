#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#define ASSERT(x) if (!(x)) __debugbreak(); 
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);
void framebuffer_size_callback(GLFWwindow * window, int width, int height);

class setProject
{
public:
    GLFWwindow* returnWindow();
private:
    unsigned int setUpProgram();
    GLFWwindow* window;
};



