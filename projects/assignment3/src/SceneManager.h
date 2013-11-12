#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include <list>
#include "SceneNode.h"
#include "ShaderProgram.h"

class SceneManager 
{
public:
	void addNode (SceneNode * node);
	void drawScene ();
	SceneManager (_shaderProgram shaderProgram);
	std::list _nodes;
	ShaderProgram * _shaderProgram;
};

#endif