#include "Polygon.h"

#include <iostream>

Polygon::Polygon(SceneManager *manager):
	_manager(manager),
	_vertexChannel(manager->getShaderProgram()->getPositionChannel()),
	_vertices(0), _indices(0), _verticesSize(0), _indicesSize(0),
	_numberOfIndices(0)
{
	// empty
}

Polygon::~Polygon() {
	/*
	glDisableVertexAttribArray(_vertexChannel);
	glDisableVertexAttribArray(_colorChannel);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteBuffers(2, _vboId);
	glDeleteVertexArrays(1, &_vaoId);
	*/
}

GLuint Polygon::getVaoId() {
	return _vaoId;
}

GLuint* Polygon::getVboId() {
	return _vboId;
}

void Polygon::setVertices(const Vertex *vertices, int verticesSize) {
	_vertices = vertices;
	_verticesSize = verticesSize;
}

void Polygon::setIndices(const GLubyte *indice, int indicesSize, int numberOfIndices) {
	_indices = indice;
	_indicesSize = indicesSize;
	_numberOfIndices = numberOfIndices;
}

void Polygon::createBuffers() {
	glGenVertexArrays(1, &_vaoId);
	glBindVertexArray(_vaoId);

	glGenBuffers(2, _vboId);
	
	glBindBuffer(GL_ARRAY_BUFFER, _vboId[0]);
	glBufferData(GL_ARRAY_BUFFER, _verticesSize, _vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(_vertexChannel);
	glVertexAttribPointer(_vertexChannel, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vboId[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indicesSize, _indices, GL_STATIC_DRAW);
	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(_vertexChannel);
}

void Polygon::draw() {
	glBindVertexArray(_vaoId);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, (GLvoid*)0);
	glBindVertexArray(0);
}
