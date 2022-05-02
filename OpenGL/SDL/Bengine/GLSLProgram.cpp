#include "GLSLProgram.h"
#include "Errors.h"
#include <vector>
#include <fstream>
#include <iostream>


GLSLProgram::GLSLProgram() :
	_numberOfAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0) {

}

GLSLProgram::~GLSLProgram() { };

void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {

	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (!_vertexShaderID) 
		fatalError("Vertex shader failed to be created!\n");
	
	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (!_fragmentShaderID) 
		fatalError("Fragment shader failed to be created!\n");

	compileShader(vertexShaderFilePath, _vertexShaderID);
	compileShader(fragmentShaderFilePath, _fragmentShaderID);

}


void GLSLProgram::compileShader(const std::string& filePath, GLuint id) {
	_programID = glCreateProgram();


	std::ifstream vertexFile(filePath);
	if (vertexFile.fail()) {
		perror(filePath.c_str());
		fatalError("Could not open \n" + filePath);
	}

	std::string fileContents = "", line;

	while (std::getline(vertexFile, line))
		fileContents += line + "\n";

	vertexFile.close();


	const char* contentsPTR = fileContents.c_str();
	glShaderSource(id, 1, &contentsPTR, nullptr);

	glCompileShader(id);



	GLint isCompiled = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);

	if (!isCompiled) {
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxlength includes the null character 
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);


		//Provide infolog in whatever manor you deem best;
		// Exit with failure
		glDeleteShader(id); // Dont leak the shader

		std::printf("%s\n", &(errorLog[0]));
		fatalError("Shader" + filePath + " failed to compile!\n");

		return;
	}
}


void GLSLProgram::linkShaders() {
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	glLinkProgram(_programID);

	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, &isLinked);

	if (!isLinked) {
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxlength includes the null character 
		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);


		//Provide infolog in whatever manor you deem best;
		// Exit with failure
		glDeleteProgram(_programID); // Dont leak the shader

		fatalError("Shaders failed link !\n");
		std::printf("%s\n", &(errorLog[0]));

		return;
	}



	//ALWAYS DETACH SHADERS AFTER A SUCCESSFUL LINK
	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);

}


void GLSLProgram::addAttribute(const std::string& attributeName) {
	glBindAttribLocation(_programID, _numberOfAttributes, attributeName.c_str());
		_numberOfAttributes++;
	
}


GLint GLSLProgram::getUniformLocation(const std::string& uniformName) {
	GLint location = glGetUniformLocation(_programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX)
		fatalError("Uniform " + uniformName + " not found in shader!");

	return location;
}

void GLSLProgram::use() {
	glUseProgram(_programID);

	for (int i = 0; i < _numberOfAttributes; i++) 
		glEnableVertexAttribArray(i);

}

void GLSLProgram::unuse() {
	glUseProgram(0);

	for (int i = 0; i < _numberOfAttributes; i++)
		glDisableVertexAttribArray(i);

}

