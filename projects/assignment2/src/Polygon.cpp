#include "Polygon.h"

Polygon::Polygon(int vertexChannel, int colorChannel):
	_vertexChannel(vertexChannel), _colorChannel(colorChannel), _vertices(0), _indices(0)
{
	// empty
}

Polygon::~Polygon() {
	// empty
}

void Polygon::setVertices(const Vertex *vertices) {
	_vertices = vertices;
}

void Polygon::setIndices(const GLubyte *indice) {
	_indices = indice;
}

void Polygon::createBuffers() {
	glGenVertexArrays(1, &_vaoId);
	glBindVertexArray(_vaoId);

	glGenBuffers(2, _vboId);

	glBindBuffer(GL_ARRAY_BUFFER, _vboId[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(_vertexChannel);
	glVertexAttribPointer(_vertexChannel, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(_colorChannel);
	glVertexAttribPointer(_colorChannel, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)sizeof(_vertices[0].XYZW));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vboId[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(_vertexChannel);
	glDisableVertexAttribArray(_colorChannel);
}
