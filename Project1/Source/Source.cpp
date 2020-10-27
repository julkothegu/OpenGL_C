#include <fstream>
#include <sstream>

#include <iostream>
#include <string>
#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Shader.h" 
#include "Textures.h"
#include "Camera.h"
#include "Context.h"
#include "Renderer.h"
#include "DataDefs.h"
#include "Renderer.h"
#include "StaticDataDefs.h"
#include "VertexBuffer.h"
#include "Context.h"
#include "Model.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <tuple>
#include <array>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <stdio.h>
#include <map>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

float planeVertices[] = {
    // positions            // normals         // texcoords
     25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
    -25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
    -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

     25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
    -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
     25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 10.0f
};

const unsigned int scr_width = 800;
const unsigned int scr_height = 600;

float quadVertices[] = {
    // positions        // texture Coords
    -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
     1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
     1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
};

int main(void)
{
    //Setup all openGL stuff
    setProject init;
    GLFWwindow* window = init.returnWindow();

    Camera camera; 
    camera.setInputs(window, camera);

    glEnable(GL_DEPTH_TEST);

    Textures tex1;
    tex1.texSetUp("C:/Users/Julko/Documents/Cpp projects/Open_GL_1/Project_1 c/Project1/Resources/Images/box1.png", "png", false);

    Shader normal;
    normal.setUpShader("Resources/Shaders/lightObject.vs", "Resources/Shaders/lightObject.fs");
    Shader depthS;
    depthS.setUpShader("Resources/Shaders/depthS.vs", "Resources/Shaders/depthS.fs");
    Shader depthR;
    depthR.setUpShader("Resources/Shaders/depthR.vs", "Resources/Shaders/depthR.fs");

    Context va;
    VertexBuffer vb(vert3d.size() * sizeof(Def3), vert3d.data(), 's', "type3a", GL_FALSE, GL_FLOAT);
    va.addBuffer(vb, "VBO");
    GLCall(va.setVBOAttribs());

    Context va2;
    VertexBuffer vb2(sizeof(quadVertices), &quadVertices[0], 's', "type2a", GL_FALSE, GL_FLOAT);
    va2.addBuffer(vb2, "VBO");
    GLCall(va2.setVBOAttribs());
    
    Context plane;
    VertexBuffer planevb(sizeof(planeVertices), &planeVertices[0], 's', "type3a", GL_FALSE, GL_FLOAT);
    plane.addBuffer(planevb, "VBO");
    GLCall(plane.setVBOAttribs());
    
    /*
    Textures texo;
    unsigned int t1 = texo.addTex("Resources/Images/box1.png", "png", true);
    unsigned int t2 = texo.addTex("Resources/Images/specmap.png", "png", true);
    */

    const unsigned int d_width = 1024, d_height = 1024;

    unsigned int depthFBO;
    glGenFramebuffers(1, &depthFBO);
    glBindBuffer(GL_FRAMEBUFFER, depthFBO);

    unsigned int depthMap;
    glGenTextures(1, &depthMap);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, d_width, d_height, 0, GL_DEPTH_ATTACHMENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glReadBuffer(GL_NONE);
    glDrawBuffer(GL_NONE);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Incomplete stuff!" << std::endl;

    glBindBuffer(GL_FRAMEBUFFER, 0);

    depthR.use();
    depthR.setInt("depthMap", 0);

    glm::vec3 lightPos(-2.0f, 4.0f, 1.0f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
     
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        //set up scene, draw objects, etc.

        camera.processInput(window);
        camera.calcDelta();

        float fov = camera.return_fov();

        float near_plane = 1.0f, far_plane = 8.0f;
        glm::mat4 lightProj = glm::ortho(-10.0f, 10.0f, 10.0f, 10.0f, near_plane, far_plane);
        glm::mat4 lightView = glm::lookAt(lightPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 lightSpaceMat = lightProj * lightView;

        glViewport(0, 0, d_width, d_height);
        glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
        glClear(GL_DEPTH_BUFFER_BIT);

        depthS.use();
        depthS.setUniformMat4("lightSpaceMat", lightSpaceMat);
        glm::mat4 model = glm::mat4(1.0f);
        depthS.setUniformMat4("model", model);        

        depthS.use();

        plane.bind();
        model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
        depthS.setUniformMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        va.bind();
        model = glm::translate(model, glm::vec3(1.0f, 1.0f, -2.0f));
        model = glm::scale(model, glm::vec3(0.6f));
        depthS.setUniformMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        model = glm::translate(model, glm::vec3(2.0f, 1.0f, -1.0f));
        depthS.setUniformMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, scr_width, scr_height);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        
        va2.bind();
        depthR.use();
        depthR.setFloat("near_plane", near_plane);
        depthR.setFloat("far_plane", far_plane);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
