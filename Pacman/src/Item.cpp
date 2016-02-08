#include "Item.h"

Item::Item(Ogre::SceneNode * node, bool melon){
	_node = node;
	_melon = melon;
	_active = true;
	_vertex = NULL;
	if(_melon)
		_score = 25; //por ejemplo
	else
		_score = 5; //por ejemplo
}
GraphVertex * Item::getGraphVertex(){
	return _vertex;
}

Item::Item(bool melon){
	_node = NULL;
	_active = true;
	_vertex = NULL;
	_melon = melon;
	if(_melon)
		_score = 25; //por ejemplo
	else
		_score = 5; //por ejemplo
}
Item::~Item(){
	delete _node;
	delete _vertex;
}
		
Ogre::SceneNode * Item::getSceneNode(){
	return _node;
}
bool Item::isMelon(){
	return _melon;
}
int Item::getScore(){
	return _score;
}

bool Item::isActive(){
	return _active;
}

		
void Item::setSceneNode(Ogre::SceneNode * node){
	_node = node;
}
void Item::setGraphVertex(GraphVertex * vertex){
	_vertex = vertex;
}
void Item::setMelon(bool melon){
	_melon = melon;
}
void Item::setScore(int score){
	_score = score;
}
void Item::setActive(bool active){
	_active = active;
}
