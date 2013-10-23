#include "Polygon.h"

#include <iostream>

Polygon::Polygon(int vertexChannel, int colorChannel):
	_vertexChannel(vertexChannel), _colorChannel(colorChannel),
	_vertices(0), _indices(0), _verticesSize(0), _indicesSize(0)
{
	// empty
}

Polygon::~Polygon() {
	// empty
}

void Polygon::setVertices(const Vertex *vertices, int verticesSize) {
	_vertices = vertices;
	_verticesSize = verticesSize;
}

void Polygon::setIndices(const GLubyte *indice, int indicesSize) {
	_indices = indice;
	_indicesSize = indicesSize;
}

void Polygon::createBuffers() {
	glGenVertexArrays(1, &_vaoId);
	glBindVertexArray(_vaoId);

	glGenBuffers(2, _vboId);

	glBindBuffer(GL_ARRAY_BUFFER, _vboId[0]);
	std::cout << "sizeof(_vertices): " << _verticesSize << std::endl;
	std::cout << "sizeof(_indices):  " << _indicesSize  << std::endl;
	std::cout << "sizeof(Vertex): " << sizeof(Vertex) << std::endl;
	std::cout << "sizeof(_vertices[0].XYZW): " << sizeof(_vertices[0].XYZW) << std::endl;
	glBufferData(GL_ARRAY_BUFFER, _verticesSize, _vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(_vertexChannel);
	glVertexAttribPointer(_vertexChannel, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(_colorChannel);
	glVertexAttribPointer(_colorChannel,  4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)sizeof(_vertices[0].XYZW));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vboId[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indicesSize, _indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(_vertexChannel);
	glDisableVertexAttribArray(_colorChannel);
}
