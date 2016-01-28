#include "Ghost.h"

Ghost::Ghost(Ogre::SceneNode * node){
	_node = node;
	_health = 1; //por ejemplo
	_direction = '-';
	_positionX = 0.0;
	_positionY = 0.0;
	_type = '-'
	_weak = false;
}
Ghost::Ghost(){
	_node = NULL;
	_health = 1; //por ejemplo
	_direction = '-';
	_positionX = 0.0;
	_positionY = 0.0;
	_type = '-'
	_weak = false;
}
Ghost::~Ghost(){

}
		
Ogre::SceneNode * Ghost::getSceneNode(){
	return _node;
}
int Ghost::getHealth(){
	return _health;
}
char Ghost::getDirection(){
	return _direction;
}
double Ghost::getPositionX(){
	return _positionX;
}
double Ghost::getPositionY(){
	return _positionY;
}
char Ghost::getType(){
	return _type;
}
bool Ghost::isWeak(){
	return _weak;
}
		
void Ghost::setSceneNode(Ogre::SceneNode * node){
	_node = node;
}
void Ghost::setHealth(int hp){
	_health = hp;
}
void Ghost::setDirection(char direction){
	_direction = direction;
}
void Ghost::setPositionX(double posX){
	_positionX = posX;
}
void Ghost::setPositionY(double posY){
	_positionY = posY;
}
void Ghost::setType(char type){
	_type = type;
}
void Ghost::setWeak(char weak){
	_weak = weak;
}