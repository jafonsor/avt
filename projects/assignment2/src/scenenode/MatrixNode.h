#ifndef MATRIX_NODE_H
#define MATRIX_NODE_H

#include "SingleNode.h"
#include "../Matrix.h"
#include "../SceneManager.h"

class MatrixNode : public SingleNode {
	Matrix *_matrix;
	SceneManager *_manager;

public:
	MatrixNode(SceneManager *manager, Matrix *matrix);
	~MatrixNode();

	void apply();
	void clear();
};

#endif