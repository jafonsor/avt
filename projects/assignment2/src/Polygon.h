#ifndef POLYGON_H
#define POLYGON_H

#include "GL/glew.h"
#include "../SceneManager.h"

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
	int _numberOfIndices;

public:
	Polygon(SceneManager *manager);
	~Polygon();
	
	GLuint getVaoId();
	GLuint* getVboId();

	void setVertices(const Vertex *vertices, int verticesSize);
	void setIndices(const GLubyte *indice, int indicesSize, int numberOfIndices);
	void createBuffers();
	void draw();
};

#endif
