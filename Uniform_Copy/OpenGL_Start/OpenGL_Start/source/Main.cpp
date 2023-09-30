#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include "ShaderUtil.h"
#include <chrono>
#include <thread>//








int main (void)

{



	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	///* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Window", NULL, NULL);
	//if (!window)
	//{
	//	glfwTerminate();
	//	return -1;
	//}
//
	///* Make the window's context current */
	glfwMakeContextCurrent(window);
	

	glViewport(0, 0, 640, 480);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	else
	{
		fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
		glfwSwapInterval(1);
		// TODO: Create and compile shaders here (vertex and fragment shaders)
		// and finally draw something with modern OpenGL!
		ShaderUtil shaderUtil;
		shaderUtil.Load("/home/kadir/Documents/OpenGL_Start/OpenGL_Start/shaders/vs.shader", "/home/kadir/Documents/OpenGL_Start/OpenGL_Start/shaders/fs.shader");

		// Points for triangle
		float points[12] = {

            -0.5f, -0.5f, 0.0f, // Vertex 1
            0.5f, -0.5f, 0.0f, // Vertex 2
            0.5f,  0.5f, 0.0f, // Vertex 3
            -0.5f,  0.5f, 0.0f  // Vertex 4
		};
		// Include headers and set up OpenGL context

		// Create shader program and link uniforms

		// Render the scene

		//unsigned int buffer;
        float triangleVertices[] = {
            0.0f,  0.5f, 0.0f,
           -0.5f, -0.5f, 0.0f,
            1.0f, -0.5f, 0.0f
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
		// Create a buffer
		glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // Create and bind VBO for triangle
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

        // Set vertex attribute pointers for triangle
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Create and bind IBO for triangle
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindAttribLocation(shaderUtil.GetProgramId(), 0, "inPosition");

// Link the shader program
		shaderUtil.LinkProgram();
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3,(void*) 0);
		shaderUtil.Use();
		




//		glUniform1f(timeLocation, currentTime);
		
		
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{	

			
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);
			float time = glfwGetTime(); // Get current time
 	   		shaderUtil.Use();
    		shaderUtil.SetUniformFloat("u_time", time);

			// Draw triangle

			glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glfwSwapBuffers(window);
            glfwPollEvents();

            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            /* Render square for 2 seconds */
            glClear(GL_COLOR_BUFFER_BIT);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

            glfwSwapBuffers(window);
            glfwPollEvents();

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		shaderUtil.Delete();

	}

	glfwTerminate();
	return 0;
}

