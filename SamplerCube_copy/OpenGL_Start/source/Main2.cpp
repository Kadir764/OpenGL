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

unsigned int loadCubemap(std::vector<std::string> textures_faces) {
    
    unsigned int cubemapTexture;
    glGenTextures(1, &cubemapTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < textures_faces.size(); ++i) {
        
        unsigned char *data = SOIL_load_image(textures_faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                        0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            SOIL_free_image_data(data);
        } else {
            std::cout << "Cubemap texture failed to load at path: " << textures_faces[i] << std::endl;
            SOIL_free_image_data(data);
            
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    return cubemapTexture;
};



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
        shaderUtil.Load("/home/kadir/Documents/SamplerCube_copy/OpenGL_Start/shaders/cubevs.shader", "/home/kadir/Documents/SamplerCube_copy/OpenGL_Start/shaders/cubefs.shader");
        // Before linking the program in ShaderUtil.cpp


        shaderUtil.LinkProgram();


        unsigned int cubeIndices[] = {
            0, 1, 2, 2, 3, 0,   // Front Face
            1, 5, 6, 6, 2, 1,   // Right Face
            7, 6, 5, 5, 4, 7,   // Back Face
            4, 0, 3, 3, 7, 4,   // Left Face
            4, 5, 1, 1, 0, 4,   // Bottom Face
            3, 2, 6, 6, 7, 3    // Top Face
        };
        float cubeVertices[] = {
            // Positions           // Texture Coords
            -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,

            -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,
        };  



        std::vector<std::string> textures_faces = {
            "/home/kadir/Documents/OpenGL_Start/OpenGL_Start/right.jpg", "/home/kadir/Documents/OpenGL_Start/OpenGL_Start/left.jpg",
            "/home/kadir/Documents/OpenGL_Start/OpenGL_Start/top.jpg", "/home/kadir/Documents/OpenGL_Start/OpenGL_Start/bottom.jpg",
            "/home/kadir/Documents/OpenGL_Start/OpenGL_Start/front.jpg", "/home/kadir/Documents/OpenGL_Start/OpenGL_Start/back.jpg"
        };
        unsigned int cubemapTexture = loadCubemap(textures_faces); 
        
        unsigned int cubeVAO, cubeVBO, EBO;

        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &cubeVBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(cubeVAO);

        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);



        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

        // Vertex attribute pointers for cube
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);


        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        shaderUtil.Use();


        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            float time = glfwGetTime();
            
            
            glEnable(GL_DEPTH_TEST);

            
            shaderUtil.Use();
   
            GLuint modelMatrixLoc = glGetUniformLocation(shaderUtil.GetProgramId(), "u_modelMatrix");
            GLuint viewMatrixLoc = glGetUniformLocation(shaderUtil.GetProgramId(), "u_viewMatrix");
            GLuint projMatrixLoc = glGetUniformLocation(shaderUtil.GetProgramId(), "u_projMatrix");

            glm::vec3 cameraPosition = glm::vec3(tan(time/5),6*sin(time),3.0f);
            glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
            glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
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
            
            shaderUtil.Use();
            glUniform1i(glGetUniformLocation(shaderUtil.GetProgramId(), "u_texture"), 0);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
            glBindVertexArray(cubeVAO);


            
            
            
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            
            GLenum error = glGetError();
            if (error != GL_NO_ERROR)
            {
                std::cerr << "OpenGL Error: " << error << std::endl;
            }
                 
            glBindVertexArray(0);
            
            glfwSwapBuffers(window);
            glfwPollEvents();

            
        }

        shaderUtil.Delete();
    }

    glfwTerminate();
    return 0;
}
