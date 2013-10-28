#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "GL/glew.h"
#include "Shader.h"

class ShaderProgram {
	static const GLuint POSITION_CHANNEL = 0;
	static const GLuint COLOR_CHANNEL = 1;
	GLuint _programId;
	Shader *_vertexShader;
	Shader *_fragmentShader;

public:
	ShaderProgram(Shader *vertexShader, Shader *fragmentShader);
	~ShaderProgram();

	GLuint getId();

	GLint  getModelMatrixUniformId();
	GLuint getPositionChannel();
	GLuint getColorChannel();

	void setPositionAttribName(const char *attribName);
	void setColorAttribName(const char *attribName);

	void  bindAttribLocation(GLuint channel, const GLchar *attribName);
	void  linkProgram();
	GLint getUniformLocation(const GLchar *name);
	void  use();
};

#endif
