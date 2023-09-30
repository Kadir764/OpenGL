#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include "ShaderUtil.h"
#include <chrono>
#include <SOIL/SOIL.h> 
#include </home/kadir/Documents/OpenGL_Start/OpenGL_Start/source/glm/glm/gtc/matrix_transform.hpp>
#include </home/kadir/Documents/OpenGL_Start/OpenGL_Start/source/glm/glm/gtc/type_ptr.hpp>
#include <thread>
#include </home/kadir/Documents/OpenGL_Start/OpenGL_Start/source/glm/glm/glm.hpp>
int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(1112, 906, "Window", NULL, NULL);
    glfwMakeContextCurrent(window);

    glViewport(0, 0, 1112, 906);

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
        shaderUtil.Load("/home/kadir/Documents/Sampler2D_Copy/OpenGL_Start/OpenGL_Start/shaders/vs.shader", "/home/kadir/Documents/Sampler2D_Copy/OpenGL_Start/OpenGL_Start/shaders/fs.shader");

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
        float textureCoordinates[] = {
            0.5f, 1.0f, // top vertex
            0.0f, 0.0f, // bottom-left vertex
            1.0f, 0.0f  // bottom-right vertex
        };



        unsigned int vao, vbo, ibo, texCoordVBO;

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

        glGenBuffers(1, &texCoordVBO);
        glBindBuffer(GL_ARRAY_BUFFER, texCoordVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoordinates), textureCoordinates, GL_STATIC_DRAW);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);

        glBindAttribLocation(shaderUtil.GetProgramId(), 0, "inPosition");
        glBindAttribLocation(shaderUtil.GetProgramId(), 1, "inTexCoord");
        

        shaderUtil.LinkProgram();
        shaderUtil.Use();



        
        GLuint textureLocation = glGetUniformLocation(shaderUtil.GetProgramId(), "u_texture");
        


        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        
        int width, height;
        unsigned char* image = SOIL_load_image("/home/kadir/Documents/OpenGL_Start/OpenGL_Start/XLk5y.jpg", &width, &height, 0, SOIL_LOAD_RGB);

                
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

        SOIL_free_image_data(image);   
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Horizontal wrapping
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Vertical wrapping
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Minification filter
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Magnification filter

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(textureLocation, 0);   


        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT);
            float time = glfwGetTime();
            
            GLint colorLoc = glGetUniformLocation(shaderUtil.GetProgramId(), "u_color");

            glm::vec3 currentColor = glm::vec3(sin(time), cos(time), 0.5f);
            shaderUtil.Use();
            glUniform1f(glGetUniformLocation(shaderUtil.GetProgramId(), "u_time"), time);
            glUniform2f(glGetUniformLocation(shaderUtil.GetProgramId(), "u_resolution"), 1112.0f, 906.0f);
            glUniform3fv(colorLoc, 1, glm::value_ptr(currentColor));
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
            currentColor = glm::vec3(sin(time), cos(time), 0.5);
            shaderUtil.Use();
            glUniform3fv(colorLoc, 1, glm::value_ptr(currentColor));
            




            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
            glfwSwapBuffers(window);
            glfwPollEvents();
            

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
