#ifndef POLYGON_H
#define POLYGON_H

#include "GL/glew.h"

typedef struct {
	GLfloat XYZW[4];
	GLfloat RGBA[4];
} Vertex;

class Polygon {
	GLuint _vaoId;
	GLuint _vboId[2];
	int _vertexChannel;
	int _colorChannel;
	const Vertex  *_vertices;
	const GLubyte *_indices;

public:
	Polygon(int vertexChannel, int colorChannel);
	~Polygon();

	void setVertices(const Vertex *vertices);
	void setIndices(const GLubyte *indice);
	void createBuffers();
};

#endif