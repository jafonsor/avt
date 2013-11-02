#ifndef COLOR_NODE_H
#define COLOR_NODE_H

#include "GL/glew.h"
#include "SingleNode.h"
#include "../SceneManager.h"

class ColorNode : public SingleNode {
	GLfloat *_color;
	SceneManager *_manager;

public:
	ColorNode(GLfloat color[4], SceneManager *manager);

	void apply();
	void clear();
};

#endif