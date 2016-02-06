#include "Character.h"

Character::Character(Ogre::SceneNode * node, GraphVertex * vertex){
	_node = node;
	_vertex = vertex;
	_target = NULL;
	_health = 3;
	_direction = '-';
	_invincibleSteps = 0;
}
Character::Character(){
	_node = NULL;
	_vertex = NULL;
	_target = NULL;
	_health = 3;
	_direction = '-';
	_invincibleSteps = 0;
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
double Character::getSpeed(){
	return _speed;
}
int Character::getInvincibleSteps(){
	return _invincibleSteps;
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
void Character::setSpeed(double speed){
	_speed = speed;
}
void Character::setInvincibleSteps(int invincibleSteps){
	_invincibleSteps += invincibleSteps;
}