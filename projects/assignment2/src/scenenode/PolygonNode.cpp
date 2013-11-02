#include "PolygonNode.h"

PolygonNode::PolygonNode(Polygon *polygon) :
	SingleNode(NULL), _polygon(polygon)
{
	// empty
}

PolygonNode::~PolygonNode() {
	if(_polygon != NULL)
		delete _polygon;
}

void PolygonNode::apply() {
	_polygon->draw();
}

void PolygonNode::clear() {
	// empty
}