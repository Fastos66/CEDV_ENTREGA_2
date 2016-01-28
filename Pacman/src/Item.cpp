#include "Item.h"

Item::Item(Ogre::SceneNode * node, bool melon){
	_node = node;
	_melon = melon;
	_positionX = 0.0;
	_positionY = 0.0;
	if(_melon)
		_score = 500; //por ejemplo
	else
		_score = 100; //por ejemplo
}
Item::Item(bool melon){
	_node = NULL;
	_melon = melon;
	_positionX = 0.0;
	_positionY = 0.0;
	if(_melon)
		_score = 500; //por ejemplo
	else
		_score = 100; //por ejemplo
}
Item::~Item(){
	
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
double Item::getPositionX(){
	return _positionX;
}
double Item::getPositionY(){
	return _positionY;
}
		
void Item::setSceneNode(Ogre::SceneNode * node){
	_node = node;
}
void Item::setMelon(bool melon){
	_melon = melon;
}
void Item::setScore(int score){
	_score = score;
}
void Item::setPositionX(double posX){
	_positionX = posX;
}
void Item::setPositionY(double posY){
	_positionY = posY;
}