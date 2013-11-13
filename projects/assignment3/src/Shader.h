#ifndef SHADER_H
#define SHADER_H 

#include <map>
#include <string>
#include "GL/glew.h"
#include "GL/freeglut.h"

class Shader {
	GLuint      _shaderId;
	std::string _shaderFileName;

	Shader(GLuint shaderId, std::string shaderFileName);
	void compile();

public:
	static Shader *buildFromFile(GLenum shaderType, std::string shaderFileName);


	~Shader();

	GLuint getId();

};

#endif