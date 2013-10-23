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
	int _verticesSize;
	int _indicesSize;

public:
	Polygon(int vertexChannel, int colorChannel);
	~Polygon();
	
	GLuint getVaoId();
	GLuint* getVboId();

	void setVertices(const Vertex *vertices, int verticesSize);
	void setIndices(const GLubyte *indice, int indicesSize);
	void createBuffers();
	void draw();
};

#endif
