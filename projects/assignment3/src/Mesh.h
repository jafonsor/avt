#ifndef _MESH_H_
#define _MESH_H_

#include <vector>

class Mesh {

	std::vector _vertices;
	std::vector _indices;


private:
	Mesh (std::vector _vertices);

public:
	void draw ();
	Mesh extrude (float vx,
	              float vy,
	              float vz);

};

#endif