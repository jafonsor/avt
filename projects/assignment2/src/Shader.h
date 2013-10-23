#ifndef SHADER_H
#define SHADER_H 

#include <string>
#include "GL/glew.h"
#include "GL/freeglut.h"

class Shader {
	GLuint      _shaderId;
	std::string _shaderFileName;

public:
	Shader(GLuint shaderId, std::string shaderFileName);
	~Shader();

	GLuint getId();
	void compile();
};

#endif