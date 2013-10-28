#include "ColorNode.h"

#ifndef NULL
#define NULL 0
#endif

ColorNode::ColorNode(GLfloat color[4], SceneManager *manager) :
	SingleNode(NULL), _color(color), _manager(manager)
{
	// empty
}

void ColorNode::apply() {
	GLint colorUniforId = _manager->getShaderProgram()->getUniformLocation("Color");
	glUniform4fv(colorUniforId, 1, _color);
}

void ColorNode::clear() {
	// empty
}