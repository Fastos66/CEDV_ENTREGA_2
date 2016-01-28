#include "Character.h"

Character(Ogre::SceneNode * node){
	_node = node;
	_health = 3;
	_direction = '-';
	_positionX = 0.0;
	_positionY = 0.0;
}
Character(){
	_node = NULL;
	_health = 3;
	_direction = '-';
	_positionX = 0.0;
	_positionY = 0.0;
}
~Character(){

}
		
Ogre::SceneNode * getSceneNode(){
	return _node;
}
int getHealth(){
	return _health;
}
char getDirection(){
	return _direction;
}
double getPositionX(){
	return _positionX;
}
double getPosition_Y){
	return _positionY;
}
		
void setSceneNode(Ogre::SceneNode * node){
	_node = node;
}
void setHealth(int hp){
	_health = hp;
}
void setDirection(char direction){
	_direction = direction;
}
double setPositionX(double posX){
	_positionX = posX;
}
double setPositionY(double posY){
	_positionY = posY;
}