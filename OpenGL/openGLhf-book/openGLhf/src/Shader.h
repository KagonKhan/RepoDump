#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>


class Shader {
	GLuint m_Program;
public:
	Shader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath);
	void Use() const;
	GLuint GetProgram() const;
};

Shader::Shader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath) {
	std::string shaderCode[2];
	std::ifstream shaderFile[2];
	std::stringstream shaderStream[2];

	shaderFile[0].exceptions(std::ifstream::badbit);
	shaderFile[1].exceptions(std::ifstream::badbit);

	shaderFile[0].open(vertexSourcePath);
	shaderFile[1].open(fragmentSourcePath);

	try {
		for (int i = 0; i < 2; ++i) {
			shaderStream[i] << shaderFile[i].rdbuf();
			shaderFile[i].close();

			shaderCode[i] = shaderStream[i].str();
		}
	}
	catch (const std::ifstream::failure& e) {
		std::cout << "[ERROR][SHADER] FILE_READ_FAIL\n";
	}

	GLuint vertex, fragment;
	GLint success;
	GLchar infolog[512];

	const GLchar* vShaderCode = shaderCode[0].c_str();
	const GLchar* fShaderCode = shaderCode[1].c_str();

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	/*TODO: Check if behavior consistent*/
	if (glGetShaderiv(vertex, GL_COMPILE_STATUS, &success); !success) {
		glGetShaderInfoLog(vertex, 512, NULL, infolog);
		std::cout << "[ERROR][SHADER][VERTEX] COMPILATION_FAILED\n" << infolog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);


	/*TODO: Check if behavior consistent*/
	if (glGetShaderiv(fragment, GL_COMPILE_STATUS, &success); !success) {
		glGetShaderInfoLog(fragment, 512, NULL, infolog);
		std::cout << "[ERROR][SHADER][FRAGMENT] COMPILATION_FAILED\n" << infolog << std::endl;
	}



	this->m_Program = glCreateProgram();
	glAttachShader(this->m_Program, vertex);
	glAttachShader(this->m_Program, fragment);
	glLinkProgram(this->m_Program);

	if (glGetProgramiv(this->m_Program, GL_LINK_STATUS, &success); !success) {
		glGetProgramInfoLog(this->m_Program, 512, NULL, infolog);
		std::cout << "[ERROR][SHADER][PROGRAM] LINKING_FAILED\n" << infolog << std::endl;

	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}


void Shader::Use() const {
	glUseProgram(this->m_Program);
}

GLuint Shader::GetProgram() const {
	return this->m_Program;
}