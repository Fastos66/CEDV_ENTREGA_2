#include "Character.h"

Character::Character(Ogre::SceneNode * node, GraphVertex * vertex){
	_node = node;
	_vertex = vertex;
	_health = 3;
	_direction = '-';
	_positionX = 0.0;
	_positionY = 0.0;
}
Character::Character(){
	_node = NULL;
	_vertex = NULL;
	_health = 3;
	_direction = '-';
	_positionX = 0.0;
	_positionY = 0.0;
}
Character::~Character(){

}
		
Ogre::SceneNode * Character::getSceneNode(){
	return _node;
}
GraphVertex * Character::getGraphVertex(){
	return _vertex;
}
GraphVertex * Character::getTarget(){
	return _target;
}
int Character::getHealth(){
	return _health;
}
char Character::getDirection(){
	return _direction;
}
double Character::getPositionX(){
	return _positionX;
}
double Character::getPositionY(){
	return _positionY;
}
double Character::getSpeed(){
	return _speed;
}
		
void Character::setSceneNode(Ogre::SceneNode * node){
	_node = node;
}
void Character::setGraphVertex(GraphVertex * vertex){
	_vertex = vertex;
}
void Character::setTarget(GraphVertex * target){
	_target = target;
}
void Character::setHealth(int hp){
	_health = hp;
}
void Character::setDirection(char direction){
	_direction = direction;
}
void Character::setPositionX(double posX){
	_positionX = posX;
}
void Character::setPositionY(double posY){
	_positionY = posY;
}
void Character::setSpeed(double speed){
	_speed = speed;
}