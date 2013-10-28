#include "MatrixNode.h"

MatrixNode::MatrixNode(SceneManager *manager, Matrix *matrix) :
	SingleNode(NULL), _manager(manager), _matrix(matrix)
{
	// empty
}

MatrixNode::~MatrixNode() {
	// empty
}

void MatrixNode::apply() {
	GLint matrixUniformId = _manager->getShaderProgram()->getModelMatrixUniformId();
	glUniformMatrix4fv(matrixUniformId, 1, GL_TRUE, _matrix->getValues());
}

void MatrixNode::clear() {
	// empty
}