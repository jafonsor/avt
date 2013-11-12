#ifndef _SCENE_NODE_H_
#define _SCENE_NODE_H_

#include "Matrix.h"
#include "SceneManager.h"

class SceneNode 
{
public:
	void setZRotation (float angle);
	void setPosition (float x,
	                  float y,
	                  float z);
	SceneNode (SceneManager * manager);
	void transverse ();
	SceneManager * _manager;
	Matrix _modelMatrix;
	Matrix _translationMatrix;
	Matrix _rotationMatrix;
	Mesh * _mesh;
};

#endif