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
        shaderUtil.Load("/home/kadir/Documents/Sine/OpenGL_Start/OpenGL_Start/shaders/vs.shader", "/home/kadir/Documents/Sine/OpenGL_Start/OpenGL_Start/shaders/fs.shader");

        shaderUtil.Use();
        shaderUtil.LinkProgram();


        std::vector<float> vertices;

        // Define the parameters of the sine wave
        float amplitude = 0.5f;
        float frequency = 5.0f;
        float phaseShift = 0.0f;

        // Generate vertices for the sine wave
        for (float x = -1.0f; x <= 1.0f; x += 0.01f) {
            float y = amplitude * cos(2 * M_PI * frequency * x + phaseShift);
            vertices.push_back(x);
            vertices.push_back(y);
        }

        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);

        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);
            glBindVertexArray(vao);
            glDrawArrays(GL_LINE_STRIP, 0, vertices.size() / 2);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();
        return 0;
    }
}