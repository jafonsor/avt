#ifndef SCENE_NODE_H
#define SCENE_NODE_H

class SceneNode {
public:
	virtual ~SceneNode();
	virtual void transverse() = 0;
	virtual void apply() = 0;
	virtual void clear() = 0;
};

#endif
