#ifndef GROUP_NODE_H
#define GROUP_NODE_H

#include "SceneNode.h"
#include <list>

class GroupNode : public SceneNode {
	std::list<SceneNode*> _children;

public:
	GroupNode();
	~GroupNode();

	void add(SceneNode *node);

	// SceneNode methods
	void transverse();

	void apply();
	void clear();

};

#endif