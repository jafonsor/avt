#include "ShaderProgram.h"

#include <iostream>
#include <string>

ShaderProgram::ShaderProgram(Shader *vertexShader, Shader *fragmentShader):
	_programId(0), _vertexShader(vertexShader), _fragmentShader(fragmentShader),
	_blockBindings()
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
	
	shProg->bindAttribLocation(POSITION_CHANNEL, "in_Position");
	shProg->bindAttribLocation(COLOR_CHANNEL,    "in_Color");
	shProg->linkProgram();

	return shProg;
}


GLint ShaderProgram::getUniformLocation(const GLchar *name) {
	return glGetUniformLocation(_programId, name);
}

GLint ShaderProgram::getUniformBlockIndex(const GLchar *name) {
	return glGetUniformBlockIndex(_programId, name);
}
GLint ShaderProgram::getUniformBlockBiding(const GLchar *name) {
	std::string strName(name);
	if(_blockBindings.count(strName) == 0) {
		_blockBindings[strName] = _blockBindings.size();
		glUniformBlockBinding(
			_programId,
			getUniformBlockIndex(name),
			_blockBindings[strName]
		);
	}
	return _blockBindings[strName];
}

GLuint ShaderProgram::getId() {
	return _programId;
}

void ShaderProgram::use() {
	glUseProgram(_programId);
}

void ShaderProgram::unUse() {
	glUseProgram(0);
}
