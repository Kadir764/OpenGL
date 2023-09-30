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
#include <random>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>


const int WINDOW_WIDTH = 1112;
const int WINDOW_HEIGHT = 906;

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Window", NULL, NULL);
    glfwMakeContextCurrent(window);

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

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
        shaderUtil.Load("/home/kadir/Documents/Sine/OpenGL_Start/OpenGL_Start/shaders/vs_distance.shader", "/home/kadir/Documents/Sine/OpenGL_Start/OpenGL_Start/shaders/fs_distance.shader");

        shaderUtil.Use();
        shaderUtil.LinkProgram();

        // Define vertices for two triangles
        float triangle1Vertices[] = {
            -0.1f, -0.1f, 0.0f,
             0.1f, -0.1f, 0.0f,
             0.0f,   0.1f, 0.0f
        };

        float triangle2Vertices[] = {
            -0.1f, -0.1f, 0.0f,
             0.1f, -0.1f, 0.0f,
             0.0f,   0.1f, 0.0f
        };

        // Define vertices for the line


        // Define the indices for rendering the triangles
        unsigned int indices[] = {
            0, 1, 2
        };

        GLuint vao[3], vbo[3], ebo;

        glGenVertexArrays(3, vao);
        glGenBuffers(3, vbo);
        glGenBuffers(1, &ebo);

        // Bind and set up VAO, VBO, and EBO for the first triangle
        glBindVertexArray(vao[0]);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1Vertices), triangle1Vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Bind and set up VAO, VBO for the second triangle
        glBindVertexArray(vao[1]);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2Vertices), triangle2Vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Bind and set up VAO, VBO for the line
        glBindVertexArray(vao[2]);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Unbind VAO to avoid accidental changes
        glBindVertexArray(0);

        // Projection matrix
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(WINDOW_WIDTH) / WINDOW_HEIGHT, 0.1f, 100.0f);
        
        // View matrix
        
        float xloc1, yloc1, zloc1, xloc2,yloc2,zloc2;
        xloc1=0.0f;
        yloc1=0.0f;
        zloc1=0.0f;
        xloc2=-0.0f;
        yloc2=-0.0f;
        zloc2=0.0f;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(0, 7);
        
        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



            float time = glfwGetTime();
            glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            int randomInt = distribution(gen);
            //std::this_thread::sleep_for(std::chrono::milliseconds(50));

            if (randomInt==0){
                xloc1+=0.03f;

            }else if (randomInt==1){
                xloc1+=0.00f;


            }else if (randomInt==2){
                xloc1+=-0.03f;

            }
            if (randomInt==0){
                yloc1+=-0.03f;


            }else if (randomInt==1){
                yloc1+=0.0f;

            }else if (randomInt==2){
                yloc1+=0.03f;


            }
            if (randomInt==0){
                zloc1+=-0.03f;

            }else if (randomInt==1){
                zloc1+=0.03f;

            }else if (randomInt==2){
                zloc1+=0.0f;

            }
            if (randomInt==0){
                xloc2+=0.00f;


            }else if (randomInt==1){
                xloc2+=-0.03f;

            }else if (randomInt==2){
                xloc2+=0.03f;


            }
            if (randomInt==0){
                yloc2+=0.0f;

            }else if (randomInt==1){
                yloc2+=0.03f;


            }else if (randomInt==2){
                yloc2+=-0.03f;

            }
            if (randomInt==0){
                zloc2+=0.03f;


            }else if (randomInt==1){
                zloc2+=0.0f;

            }else if (randomInt==2){
                zloc2+=-0.03f;

            }

            glm::vec3 triangle1Position = glm::vec3(xloc1, yloc1, zloc1);
            glm::vec3 triangle2Position = glm::vec3(xloc2, yloc2, zloc2);

            

            GLint triangle1PositionLocation = glGetUniformLocation(shaderUtil.GetProgramId(), "triangle1Position");
            GLint triangle2PositionLocation = glGetUniformLocation(shaderUtil.GetProgramId(), "triangle2Position");
            glUniform3fv(triangle1PositionLocation, 1, glm::value_ptr(triangle1Position));
            glUniform3fv(triangle2PositionLocation, 1, glm::value_ptr(triangle2Position));

            GLint resultLocation = glGetUniformLocation(shaderUtil.GetProgramId(), "result");
            float distance =glm::length(triangle2Position - triangle1Position);
            glGetUniformfv(shaderUtil.GetProgramId(), resultLocation, &distance); 
            glUniform1f(resultLocation, distance);

            
           

            // Print the distance to the terminal
            std::cout << "Distance: " << distance << std::endl;



            glm::mat4 model1 = glm::translate(glm::mat4(1.0f),triangle1Position);
            glm::mat4 model2 = glm::translate(glm::mat4(1.0f), triangle2Position);
            glm::vec3 lineDirection = glm::normalize(triangle2Position - triangle1Position);

            // Scale the line to unit length (e.g., 1.0)
            float lineLength = glm::length(triangle2Position - triangle1Position);
            float lineScaleFactor = 1.0f;
            glm::mat4 modelLine = glm::scale(glm::mat4(1.0f), glm::vec3(lineScaleFactor, lineScaleFactor, lineScaleFactor));

            // Translate the line to the start position
            modelLine = glm::translate(modelLine, triangle1Position);
        //    glm::vec3 lineStart = glm::vec3(xloc1, yloc1, zloc1); // Take the translation part of the first triangle's model matrix as the start point
        //    glm::vec3 lineEnd = glm::vec3(xloc2 , yloc2, zloc2);    // Take the translation part of the second triangle's model matrix as the end point
//
        //    std::cout << "Model1[3]: x = " <<lineStart.x << ", y = " << lineStart.y << ", z = " << lineStart.z << std::endl;
        //    std::cout << "Model2[3]: x = " << model1[3].x << ", y = " << model1[3].y << ", z = " << model1[3].z << std::endl;
        //    std::cout << "Model3[3]: x = " << model2[3].x << ", y = " << model2[3].y << ", z = " << model2[3].z << std::endl;
//
//
        //    // Update the line's vertex positions
        //    float updatedLineVertices[] = {
        //        lineStart.x, lineStart.y, lineStart.z,
        //        lineEnd.x, lineEnd.y, lineEnd.z
        //    };


            float updatedLineVertices[] = {
            xloc2-xloc1, yloc2-yloc1, zloc2-zloc1,                  // Start of the line
            0.0f, 0.0f, 0.0f  // End of the line
            };
            glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(updatedLineVertices), updatedLineVertices, GL_STATIC_DRAW);
            // Use the shader program
            shaderUtil.Use();

            // Set the uniform matrices
            GLint modelLoc = glGetUniformLocation(shaderUtil.GetProgramId(), "model");
            GLint viewLoc = glGetUniformLocation(shaderUtil.GetProgramId(), "view");
            GLint projectionLoc = glGetUniformLocation(shaderUtil.GetProgramId(), "projection");
            

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

            // Draw the first triangle
            glBindVertexArray(vao[0]);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

            // Update the model matrix for the second triangle
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

            // Draw the second triangle
            glBindVertexArray(vao[1]);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelLine));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelLine));
            glBindVertexArray(vao[2]);
            glDrawArrays(GL_LINES, 0, 2);

            glBindVertexArray(0);
            

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        // Clean up
        glDeleteVertexArrays(3, vao);
        glDeleteBuffers(3, vbo);
        glDeleteBuffers(1, &ebo);

        glfwTerminate();
    }

    return 0;
}