#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "GL/glew.h"
#include "Shader.h"

class ShaderProgram {
	GLuint _programId;
	Shader *_vertexShader;
	Shader *_fragmentShader;

	ShaderProgram(Shader *vertexShader, Shader *fragmentShader);

	void  bindAttribLocation(GLuint channel, const GLchar *attribName);
	void  linkProgram();
	GLint getUniformLocation(const GLchar *name);

public:
	static const GLuint POSITION_CHANNEL = 0;
	static const GLuint COLOR_CHANNEL = 1;
	
	~ShaderProgram();

	static ShaderProgram *buildShaderProgram(Shader *vertexShader, Shader *fragmentShader);

	GLuint getId();
	GLint  getModelMatrixUniformId();


	void  use();
};

#endif
