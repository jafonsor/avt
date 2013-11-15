#ifndef _MESH_BUILDER_H_
#define _MESH_BUILDER_H_

#include "Mesh.h"

class MeshBuilder 
{
	_verticies;
	_indices;

public:
	void beginMesh ();
	Mesh endMesh() ();
	void position (float x, float y, float z);
	void color (float r, float g, float b, float a);
	void index (int ind);


};

#endif