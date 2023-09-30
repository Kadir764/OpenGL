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
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>


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
        shaderUtil.Load("/home/kadir/Documents/Sine/OpenGL_Start/OpenGL_Start/shaders/vs.shader", "/home/kadir/Documents/Sine/OpenGL_Start/OpenGL_Start/shaders/fs_isqrt.shader");

        shaderUtil.Use();
        shaderUtil.LinkProgram();


            float vertices[] = {
        -1.0f, -1.0f,
        -1.0f,  1.0f,
         1.0f, -1.0f,
         1.0f,  1.0f,
        };

        GLuint VAO, VBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        // Clean up and exit

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glfwTerminate();
        return 0;
    }
}