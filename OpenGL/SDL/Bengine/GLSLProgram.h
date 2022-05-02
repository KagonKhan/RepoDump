#pragma once
#include <string>
#include "glew.h"

class GLSLProgram {
	GLuint _programID, _vertexShaderID, _fragmentShaderID ;

	int _numberOfAttributes;

	void compileShader(const std::string& filePath, GLuint id);


public:
	GLSLProgram();
	~GLSLProgram();


	void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

	void linkShaders();

	void addAttribute(const std::string& attributeName);

	GLint getUniformLocation(const std::string& uniformName);


	void use();
	void unuse();
};

