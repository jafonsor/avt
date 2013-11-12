#include "ShaderProgram.h"

#include <iostream>

ShaderProgram::ShaderProgram(Shader *vertexShader, Shader *fragmentShader):
	_programId(0), _vertexShader(vertexShader), _fragmentShader(fragmentShader)
{
	_programId = glCreateProgram();
	glAttachShader(_programId, _vertexShader->getId());
	glAttachShader(_programId, _fragmentShader->getId());
}

ShaderProgram::~ShaderProgram() {
	glUseProgram(0);
	glDetachShader(_programId, _vertexShader->getId());
	glDetachShader(_programId, _fragmentShader->getId());

	delete _fragmentShader;
	delete _vertexShader;
	glDeleteProgram(_programId);
}


GLuint ShaderProgram::getPositionChannel() {
	return POSITION_CHANNEL;
}

GLuint ShaderProgram::getColorChannel() {
	return COLOR_CHANNEL;
}

void ShaderProgram::bindAttribLocation(GLuint channel, const GLchar *attribName) {
	glBindAttribLocation(_programId, channel, attribName);
}

void ShaderProgram::linkProgram() {
	GLint programSatus = 0;
	GLint logLength = 0;
	const int LOG_MAX_SIZE = 500;
	GLchar linkingLog[LOG_MAX_SIZE];
	
	glLinkProgram(_programId);

	// check errors on linking
	glGetProgramiv(_programId, GL_LINK_STATUS, &programSatus);
	if(programSatus == GL_FALSE) {
		std::cerr << "Linking shader program " << _programId << ":" << std::endl;
		glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &logLength);
		if(logLength < LOG_MAX_SIZE) {
			glGetProgramInfoLog(_programId, LOG_MAX_SIZE, &logLength, linkingLog);
			std::cerr << linkingLog;
		} else {
			std::cerr << "Log is bigger than the log array. Increase the size at ShaderProgram.cpp";
		}

	}
}

ShaderProgram *ShaderProgram::buildShaderProgram(Shader *vertexShader, Shader *fragmentShader) {
	ShaderProgram *shProg = new ShaderProgram(vertexShader, fragmentShader);
	
	bindAttribLocation(POSITION_CHANNEL, "in_Position");
	bindAttribLocation(COLOR_CHANNEL,    "in_Color");
	shProg->linkProgram();
}


GLint ShaderProgram::getUniformLocation(const GLchar *name) {
	return glGetUniformLocation(_programId, name);
}

GLuint ShaderProgram::getId() {
	return _programId;
}

GLint ShaderProgram::getModelMatrixUniformId() {
	return getUniformLocation("Matrix");
}

void ShaderProgram::use() {
	glUseProgram(_programId);
}

void ShaderProgram::unUse() {
	glUseProgram(0);
}