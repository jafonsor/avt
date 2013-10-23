#include "Shader.h"

#include <iostream>
#include <fstream>

Shader::Shader(GLuint shaderId, std::string shaderFileName):
	_shaderId(shaderId), _shaderFileName(shaderFileName)
{
	// empty
}

Shader::~Shader() {
	glDeleteShader(_shaderId);
}

GLuint Shader::getId() {
	return _shaderId;
}

void Shader::compile() {
	std::ifstream shaderFile(_shaderFileName.c_str());
	std::string shaderCode;
	const int MAX_LINE_SIZE = 300;
	char line[MAX_LINE_SIZE];
	const int MAX_LOG_SIZE = 1000;
	int log_size;
	char compiler_log[MAX_LOG_SIZE];

	// read shader code from file
	if(shaderFile.is_open()) {
		do {
			shaderFile.getline(line, MAX_LINE_SIZE);
			shaderCode.append(line);
			shaderCode.append("\n");
		} while( !shaderFile.eof() );
		shaderFile.close();
	} else {
		std::cerr << "Unable to open shader file " << _shaderFileName << "." << std::endl;
	}

	// compile shader
	GLint compileSatus;
	const char* codePointer = shaderCode.c_str();
	int codeLength = shaderCode.length() + 1;
	glShaderSource(_shaderId, 1, &codePointer, &codeLength);
	glCompileShader(_shaderId);
	glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &compileSatus);
	if( compileSatus == GL_FALSE ) {
		glGetShaderInfoLog(_shaderId, MAX_LOG_SIZE, &log_size, compiler_log);
		compiler_log[log_size] = '\0';
		std::cerr << "Compiling " << _shaderFileName << std::endl 
		          << "Shader code: " << std::endl << shaderCode
		          << compiler_log;
	}
}