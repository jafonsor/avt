#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "GL/glew.h"
#include "Shader.h"

class ShaderProgram {
	GLuint _programId;
	Shader *_vertexShader;
	Shader *_fragmentShader;

public:
	ShaderProgram(Shader *vertexShader, Shader *fragmentShader);
	~ShaderProgram();

	GLuint getId();

	void bindAttribLocation(GLuint channel, const GLchar *attribName);
	void linkProgram();
	GLint getUniformLocation(const GLchar *name);
};

#endif