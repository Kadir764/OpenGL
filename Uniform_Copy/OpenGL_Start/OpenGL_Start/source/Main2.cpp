//////Uniform !!!!
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include "ShaderUtil.h"
#include <chrono>

#include </home/kadir/Documents/OpenGL_Start/OpenGL_Start/source/glm/glm/gtc/matrix_transform.hpp>
#include </home/kadir/Documents/OpenGL_Start/OpenGL_Start/source/glm/glm/gtc/type_ptr.hpp>
#include <thread>
#include </home/kadir/Documents/OpenGL_Start/OpenGL_Start/source/glm/glm/glm.hpp>
int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Window", NULL, NULL);
    glfwMakeContextCurrent(window);

    glViewport(0, 0, 640, 480);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    else
    {
        fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
        glfwSwapInterval(1);

        ShaderUtil shaderUtil;
        shaderUtil.Load("/home/kadir/Documents/Uniform_Copy/OpenGL_Start/OpenGL_Start/shaders/vs.shader", "/home/kadir/Documents/Uniform_Copy/OpenGL_Start/OpenGL_Start/shaders/fs.shader");

        float triangleVertices[] = {
            0.0f,  0.5f, 0.0f,
           -0.5f, -0.5f, 0.0f,
            0.0f, -0.5f, 0.0f
        };

        float squareVertices[] = {
            -0.2f,  0.2f, 0.0f,
            -0.2f, -0.2f, 0.0f,
             0.2f, -0.2f, 0.0f,
             0.2f,  0.2f, 0.0f
        };
		unsigned int indices[] = {
            0, 1, 2,
            0, 2, 3
        };



        unsigned int vao, vbo, ibo;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glBindAttribLocation(shaderUtil.GetProgramId(), 0, "inPosition");

        shaderUtil.LinkProgram();
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
        shaderUtil.Use();

        //GLuint colorLoc = glGetUniformLocation(shaderUtil.GetProgramId(), "u_time");
        //GLuint colorRes = glGetUniformLocation(shaderUtil.GetProgramId(), "u_resolution");
        //glm::vec3 currentColor = glm::vec3(1.0f, 0.0f, 0.0f); // Initial color (red)
        GLenum renderError = glGetError();
        if (renderError != GL_NO_ERROR) {
            std::cerr << "OpenGL Render Error: " << renderError << std::endl;
        }

        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT);
            float time = glfwGetTime();
            
            
            //currentColor = glm::vec3(sin(time), cos(time), 0.5);
            shaderUtil.Use();
            glUniform1f(glGetUniformLocation(shaderUtil.GetProgramId(), "u_time"), time);
            glUniform2f(glGetUniformLocation(shaderUtil.GetProgramId(), "u_resolution"), 640.0f, 480.0f);
            //glUniform3fv(colorLoc, 1, glm::value_ptr(currentColor));
            glBindVertexArray(vao);

            GLuint modelMatrixLoc = glGetUniformLocation(shaderUtil.GetProgramId(), "u_modelMatrix");
            GLuint viewMatrixLoc = glGetUniformLocation(shaderUtil.GetProgramId(), "u_viewMatrix");
            GLuint projMatrixLoc = glGetUniformLocation(shaderUtil.GetProgramId(), "u_projMatrix");

            glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
            glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
            glm::vec3 cameraUp = glm::vec3(sin(time), cos(time), 0.0f);
            glm::mat4 viewMatrix = glm::lookAt(cameraPosition, cameraTarget, cameraUp);

            glm::mat4 modelMatrix = glm::mat4(1.0f);  // Identity matrix
            

            float fov = glm::radians(45.0f);
            float aspectRatio = 640.0f / 480.0f; // Adjust based on your window dimensions
            float nearPlane = 0.1f;
            float farPlane = 100.0f;
            glm::mat4 projMatrix = glm::perspective(fov, aspectRatio, nearPlane, farPlane);

            glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
            glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
            glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE, glm::value_ptr(projMatrix));
            //currentColor = glm::vec3(sin(time), cos(time), 0.5);
            shaderUtil.Use();
            //glUniform3fv(colorLoc, 1, glm::value_ptr(currentColor));

            glDrawArrays(GL_TRIANGLES, 0, 3);
            glfwSwapBuffers(window);
            glfwPollEvents();
            GLenum error = glGetError();

            std::this_thread::sleep_for(std::chrono::milliseconds(0));

            glClear(GL_COLOR_BUFFER_BIT);

            modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(1.0, 0.0f, 0.0f));  // Identity matrix + translation
            glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));


            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            glfwSwapBuffers(window);
            glfwPollEvents();
          

            std::this_thread::sleep_for(std::chrono::milliseconds(0));
        }

        shaderUtil.Delete();
    }

    glfwTerminate();
    return 0;
}
