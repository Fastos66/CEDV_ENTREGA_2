#include "Character.h"

Character::Character(Ogre::SceneNode * node){
	_node = node;
	_health = 3;
	_direction = '-';
	_positionX = 0.0;
	_positionY = 0.0;
}
Character::Character(){
	_node = NULL;
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
		
void Character::setSceneNode(Ogre::SceneNode * node){
	_node = node;
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