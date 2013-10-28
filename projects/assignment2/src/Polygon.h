#ifndef POLYGON_H
#define POLYGON_H

#include "GL/glew.h"
#include "SceneManager.h"

typedef struct {
	GLfloat XYZW[4];
	GLfloat RGBA[4];
} Vertex;

class Polygon {
	SceneManager *_manager;
	GLfloat *_color;
	GLuint _vaoId;
	GLuint _vboId[2];
	int _vertexChannel;
	const Vertex  *_vertices;
	const GLubyte *_indices;
	int _verticesSize;
	int _indicesSize;
	int _numberOfIndices;

public:
	Polygon(SceneManager *manager, GLfloat color[4]);
	~Polygon();
	
	GLuint getVaoId();
	GLuint* getVboId();

	void setVertices(const Vertex *vertices, int verticesSize);
	void setIndices(const GLubyte *indice, int indicesSize, int numberOfIndices);
	void createBuffers();
	void draw();
};

#endif
