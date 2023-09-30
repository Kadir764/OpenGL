#ifndef SHADERUTIL_H
#define SHADERUTIL_H

#include <GL/glew.h>
#include <string>
#include <unordered_map>

// Utitlity class to load, compile and attach a vertex- and fragment shader to a program
class ShaderUtil
{

private: 
    GLuint vertexShaderId;
    GLuint fragmentShaderId;
	unsigned int mProgramId;
	unsigned int GetCompiledShader(unsigned int shader_type, const std::string& shader_source);
	std::unordered_map<std::string, GLint> m_UniformLocations;
public:
	ShaderUtil() {}
	~ShaderUtil() {}



	// Load a vertex and a fragment shader from file
	bool Load(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	GLint GetUniformLocation(const std::string& uniformName) const;


	unsigned int GetProgramId() const;
	void LinkProgram();
	void SetUniformInt(const std::string& name, int value) const;
	void SetUniformSampler(const std::string& name, int unit) const;
	void SetUniformFloat(const std::string& uniformName, float value);
	
	GLuint GetVertexShaderId() const;
    GLuint GetFragmentShaderId() const;

	std::string GetShaderInfoLog(GLuint shaderId) const;
	bool GetCompileStatus(GLuint shaderId) const;
	void Use();

	// Delete the program
	void Delete();



};

#endif //SHADERUTIL_H