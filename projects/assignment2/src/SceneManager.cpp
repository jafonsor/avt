#include "SceneManager.h"

#ifndef NULL
#define NULL 0
#endif

SceneManager::SceneManager() :
	_shaderProgram(NULL), _sceneRoot()
{
	// empty
}

void SceneManager::setShaderProgram(ShaderProgram *program) {
	_shaderProgram = program;
}

ShaderProgram *SceneManager::getShaderProgram() {
	return _shaderProgram;
}

GroupNode *SceneManager::getSceneRoot() {
	return &_sceneRoot;
}

void SceneManager::renderScene() {
	_shaderProgram->use();
	_sceneRoot.transverse();
}