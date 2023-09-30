# OpenGL
OpenGL Internship
# OpenGL ES Shading Language 1.0 Functions

This project demonstrates a simple OpenGL program for rendering a textured cube.

## Getting Started

### Prerequisites

- [OpenGL](https://www.opengl.org/)
- [GLFW](https://www.glfw.org/)
- [GLEW](http://glew.sourceforge.net/)
- [SOIL](https://www.lonesock.net/soil.html)
- [GLM](https://github.com/g-truc/glm)

### Installing

1. Clone the repository:

   ```bash
   git clone https://github.com/Kadir764/OpenGL.git
   ```

2. Navigate to the project directory:

    ```bash
    cd OpenGL_Internship/..
    ```
There are different directories to run different examples. You can go directory according to what you want to run.

3. Compiler code:
g++ -o Main2 Main2.cpp ShaderUtil.cpp -lGL -lGLEW -lglfw -I/home/kadir/Documents/OpenGL_Start/OpenGL_Start/source/glm/glm -lSOIL
After compiling it you can directly call the Main2 to see output. For some examples there is no need for the SOIL library thus you can delete it.
Also do not forget to change Main2 and Main2.cpp according to .cpp file's name.


4. There are a file named openegl.docx which explain in detail all functions using example. Also I will put short explanation for the visualizable functions.

5. Uniform qualifier:
![image](https://github.com/Kadir764/OpenGL/assets/132132455/9ea75e74-7143-47e4-bcd1-df498038190c)

These objects created by uniform qualifier. They are rotating and color of them are changing. This rotation and color changing show how uniform usage. Our uniform variable is time and time is same for all shaders and other files as time after running the code is the same. As uniform means does not change between shaders and other code this shows how  uniform works. Code part for unifrom can be found below:

glUniform1f(glGetUniformLocation(shaderUtil.GetProgramId(), "u_time"), time); --> to pass time data to the shaders.

glm::vec3 cameraUp = glm::vec3(sin(time), cos(time), 0.0f); --> to make objects rotate

float waveFactor = sin(st.x * 10.0 + u_time) * 0.1; --> to give a wavy color effect

6. Sampler2D type:
![image](https://github.com/Kadir764/OpenGL/assets/132132455/07189810-ac08-4ae4-9adc-81d634a3ea14)

The type Sampler2D is used to upload a texture and use it on the objects. As can be seen in the picture we have same objects given above but this time we have textured version of it. Also color effect can also be adopted to this as well. Code part for Sampler2D can be found below:

GLuint textureLocation = glGetUniformLocation(shaderUtil.GetProgramId(), "u_texture"); --> This variable stores the location (index) of the u_texture uniform variable in the shader program. glGetUniformLocation retrieves this location.

GLuint texture;
glGenTextures(1, &texture); --> This variable is used to store the ID of the generated texture. glGenTextures generates texture names and stores them in the texture variable.

glBindTexture(GL_TEXTURE_2D, texture); -->This line binds the texture object texture to the target GL_TEXTURE_2D. Subsequent texture-related operations will affect this texture.

int width, height; --> width and height store the dimensions of the loaded image.
 
unsigned char* image = SOIL_load_image("/home/kadir/Documents/OpenGL_Start/OpenGL_Start/XLk5y.jpg", &width, &height, 0, SOIL_LOAD_RGB);  --> SOIL_load_image is used to load the image from the specified file path. The image data is stored in the image variable.

glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image); --> glTexImage2D specifies the 2D texture image. It sets various parameters such as format (GL_RGB), data type (GL_UNSIGNED_BYTE), and the actual image data.

SOIL_free_image_data(image); --> Frees the memory allocated by SOIL for storing image data.

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); --> GL_TEXTURE_WRAP_S set the wrapping behavior for texture coordinates in the S (horizontal) direction. GL_REPEAT means the texture will repeat.

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT --> GL_TEXTURE_WRAP_T set the wrapping behavior for texture coordinates in the T (vertical) direction. GL_REPEAT means the texture will repeat.
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); --> GL_TEXTURE_MIN_FILTER set the filtering parameters for minifying the texture, respectively. GL_LINEAR uses linear interpolation. 

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); --> GL_TEXTURE_MAG_FILTER set the filtering parameters for magnifying the texture, respectively. GL_LINEAR uses linear interpolation.

glActiveTexture(GL_TEXTURE0); --> Activates texture unit GL_TEXTURE0. Subsequent texture binding operations will affect this texture unit.

glBindTexture(GL_TEXTURE_2D, texture); --> Binds the texture (texture) to the currently active texture unit (GL_TEXTURE0).

glUniform1i(textureLocation, 0); --> Sets the value of the u_texture uniform variable in the shader to 0 (the index of the texture unit). This connects the texture unit to the shader variable

7. SamplerCube type:
![image](https://github.com/Kadir764/OpenGL/assets/132132455/281f4917-1645-4700-b3cb-df53e92c5942)

The type SamplerCube is quite similar to Sampler2D. This time we upload 6 images for 6 faces of the cube. Code part for Sampler2D can be found below as codes are also similar to previous part there will be only different part of codes:
To upload all images:
![image](https://github.com/Kadir764/OpenGL/assets/132132455/1ad11be4-deef-40a7-952c-cf12671da607)
 unsigned int cubemapTexture; --> This variable stores the ID of the generated cube map texture.
 
 glGenTextures(1, &cubemapTexture); --> Generates texture names and stores them in the cubemapTexture variable.
 
 glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture); --> Binds the cube map texture object (cubemapTexture) to the target GL_TEXTURE_CUBE_MAP. Subsequent texture-related operations will affect this cube map.
 
 glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR); --> GL_TEXTURE_MIN_FILTER set the filtering parameters for minifying the texture. GL_LINEAR uses linear interpolation.
 
 glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR); --> GL_TEXTURE_MAG_FILTER set the filtering parameters for magnifying the texture. GL_LINEAR uses linear interpolation.
 
 glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); --> GL_TEXTURE_WRAP_S set the wrapping behavior for texture coordinates in the S (horizontal) direction. GL_CLAMP_TO_EDGE means the texture coordinates are clamped between 0 and 1.
 
 glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); --> GL_TEXTURE_WRAP_T set the wrapping behavior for texture coordinates in the T (vertical) direction. GL_CLAMP_TO_EDGE means the texture coordinates are clamped between 0 and 1.
 
 glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE); --> GL_TEXTURE_WRAP_R set the wrapping behavior for texture coordinates in the R (depth) direction. GL_CLAMP_TO_EDGE means the texture coordinates are clamped between 0 and 1.

8. Math Functions:
There are several math functions and to visualize them I firslt plot the function as known in math and what can be done by using them. For the values that function takes 1 the output should be red for 0 and negative values output should be black. I will give two examples but there are much more in the opengl.docx file.

8.1 Step Function:

![image](https://github.com/Kadir764/OpenGL/assets/132132455/e883fafd-9c87-4bac-9448-a06be68beadb)
As can be seen from the image function value and color change sharply.

float y =  step(0 , x); --> This function returns 0.0 if x is less than 0, and 1.0 otherwise. It's essentially creating a step function that "steps" from 0 to 1 when x is non-negative.

float yNormalized = (y - 0.0) / (1.0 - 0.0); --> This variable is created to normalize the value of y from the range [0, 1] to [0, 1]. Since y is already in the range [0, 1], this step is not strictly necessary in this specific case.

vec3 color = vec3(yNormalized, 0.0, 0.0); --> This creates a 3D vector where the red component (r) is set to yNormalized, and the green and blue components are set to 0.0. It results in a shade of red determined by the normalized value of y.

FragColor = vec4(color, 1.0); --> This sets the output color of the fragment shader. It's a 4D vector where the RGB components are taken from the color vector, and the alpha component is set to 1.0, making it fully opaque.

8.2 Smoothstep Function:

![image](https://github.com/Kadir764/OpenGL/assets/132132455/b142f1f0-3db2-41f7-b936-a3e79efe65e5)
As can be seen from the image function value and color change paralelly.

float y =  smoothstep(-3 ,3, x); -->  This function returns a smooth interpolation between 0 and 1 based on the input x. It's commonly used to create smooth transitions. In this case, it's smoothing the step function, so it will smoothly transition from 0 to 1 as x goes from less than -3 to greater than 3.

float yNormalized = (y - 0.0) / (1.0 - 0.0); --> This variable is created to normalize the value of y from the range [0, 1] to [0, 1]. Since y is already in the range [0, 1], this step is not strictly necessary in this specific case.

vec3 color = vec3(yNormalized, 0.0, 0.0); --> This creates a 3D vector where the red component (r) is set to yNormalized, and the green and blue components are set to 0.0. It results in a shade of red determined by the normalized value of y.

FragColor = vec4(color, 1.0); --> This sets the output color of the fragment shader. It's a 4D vector where the RGB components are taken from the color vector, and the alpha component is set to 1.0, making it fully opaque.

9. Distance function
Distance function is calculates distance between two point. To visualize that I draw two objects and connect them with a line. When distance is changing color is also changing. This is a way to show how distance works.

![image](https://github.com/Kadir764/OpenGL/assets/132132455/97cfd9aa-bc38-4103-adc1-2e13282a357e)

As can be seen color is changing according to distance.

Shader:
   float dist = distance(triangle1Position, triangle2Position); --> This calculates the Euclidean distance between triangle1Position and triangle2Position.
   
   FragColor = vec4(1.0 - dist/2.0, dist/2.0, 0.5, 1.0); --> This sets the output color of the fragment shader. It's a 4D vector where the red (r) component is set to 1.0 - dist/2.0, green (g) is set to dist/2.0, blue (b) is set to 0.5, and alpha (a) is set to 1.0.

Cpp:
   glm::vec3 triangle1Position = glm::vec3(xloc1, yloc1, zloc1); --> This creates a 3D vector representing the position of triangle 1.
      
   glm::vec3 triangle2Position = glm::vec3(xloc2, yloc2, zloc2); --> This creates a 3D vector representing the position of triangle 2.
   
   GLint triangle1PositionLocation = glGetUniformLocation(shaderUtil.GetProgramId(), "triangle1Position"); --> This gets the location of the triangle1Position uniform variable in the shader.
   
   GLint triangle2PositionLocation = glGetUniformLocation(shaderUtil.GetProgramId(), "triangle2Position"); --> This gets the location of the triangle2Position uniform variable in the shader.
   
   glUniform3fv(triangle1PositionLocation, 1, glm::value_ptr(triangle1Position)); -->  This sets the value of the triangle1Position uniform variable in the shader.
   
   glUniform3fv(triangle2PositionLocation, 1, glm::value_ptr(triangle2Position)); -->  This sets the value of the triangle2Position uniform variable in the shader.
   






