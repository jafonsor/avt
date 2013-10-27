#include "SingleNode.h"

#ifndef NULL
#define NULL 0
#endif

SingleNode::SingleNode(SceneNode *next) :
	_next(next)
{
	// empty
}

SingleNode::~SingleNode() {
	if(_next != NULL)
		delete _next;
}

void SingleNode::transverse() {
	apply();
	if(_next != NULL) {
		_next->transverse();
	}
	clear();
}