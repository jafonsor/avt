#include "GroupNode.h"

GroupNode::GroupNode() :
	_children()
{
	// empty
}

GroupNode::~GroupNode() {
	std::list<SceneNode*>::iterator childIt;
	for(childIt = _children.begin();
	    childIt != _children.end(); 
	    childIt++)
	{
		delete *childIt;
	}
}

void GroupNode::add(SceneNode *node) {
	_children.push_back(node);
}

void GroupNode::transverse() {
	std::list<SceneNode*>::iterator childIt;
	for(childIt = _children.begin();
	    childIt != _children.end(); 
	    childIt++)
	{
		(*childIt)->transverse();
	}
}

void GroupNode::apply() {
	// empty
}

void GroupNode::clear() {
	// empty
}