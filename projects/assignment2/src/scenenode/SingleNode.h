#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

#include "SceneNode.h"

class SingleNode : public SceneNode {
	SceneNode *_next;

public:
	SingleNode(SceneNode *next);
	~SingleNode();

	inline void transverse();

	virtual void apply() = 0;
	virtual void clear()  = 0;
};

#endif