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






