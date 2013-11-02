#ifndef POLYGON_NODE_H
#define POLYGON_NODE_H

#include "SingleNode.h"
#include "../Polygon.h"

class PolygonNode : public SingleNode {
	Polygon *_polygon;

public:
	PolygonNode(Polygon *Polygon);
	~PolygonNode();

	inline void apply();
	inline void clear();
};

#endif