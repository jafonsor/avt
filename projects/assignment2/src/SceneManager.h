#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "scenenode/GroupNode.h"
#include "ShaderProgram.h"

class SceneManager {
	ShaderProgram *_shaderProgram;
	GroupNode _sceneRoot;

public:
	SceneManager();

	void setShaderProgram(ShaderProgram *program);
	ShaderProgram *getShaderProgram();
	GroupNode* getSceneRoot();
	void renderScene();
};

#endif