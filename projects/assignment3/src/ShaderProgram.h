#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "GL/glew.h"
#include "Shader.h"

class ShaderProgram {
	GLuint _programId;
	Shader *_vertexShader;
	Shader *_fragmentShader;
	std::map<std::string,GLuint> _blockBindings;

	ShaderProgram(Shader *vertexShader, Shader *fragmentShader);

	void  bindAttribLocation(GLuint channel, const GLchar *attribName);
	void  linkProgram();
	

public:
	static const GLuint POSITION_CHANNEL = 0;
	static const GLuint COLOR_CHANNEL = 1;
	
	~ShaderProgram();

	static ShaderProgram *buildShaderProgram(Shader *vertexShader, Shader *fragmentShader);

	GLuint getId();
	GLint getUniformLocation(const GLchar *name);
	GLint getUniformBlockIndex(const GLchar * name);
	GLint getUniformBlockBiding(const GLchar * name);

	void use();
	void unUse();
};

#endif
