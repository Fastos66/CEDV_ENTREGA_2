#include "Ghost.h"

Ghost::Ghost(Ogre::SceneNode * node, GraphVertex * vertex){
	_vertex = vertex;
	_node = node;
	_level = 1;
	_health = 1; //por ejemplo
	_direction = '-';
	_type = '-';
	_mode = 'S'; // W-> Weak, C -> Chasing, S -> Scattering
	_speed = 1.0;
	_weaknessDuration = 5.0;  //que tambien sirva como tiempo de respawn?
	_points = 200;
}
Ghost::Ghost(){
	_node = NULL;
	_vertex = NULL;
	_level = 1;
	_health = 1; //por ejemplo
	_direction = '-';
	_type = '-';
	_mode = 'S'; // W-> Weak, C -> Chasing, S -> Scattering
	_speed = 1.0;
	_weaknessDuration = 5.0;  //que tambien sirva como tiempo de respawn?
	_points = 200;
}
Ghost::~Ghost(){

}
		
Ogre::SceneNode * Ghost::getSceneNode(){
	return _node;
}
GraphVertex * Ghost::getGraphVertex(){
	return _vertex;
}
GraphVertex * Ghost::getTarget(){
	return _target;
}
int Ghost::getHealth(){
	return _health;
}
char Ghost::getDirection(){
	return _direction;
}
char Ghost::getType(){
	return _type;
}
char Ghost::getMode(){
	return _mode;
}
double Ghost::getSpeed(){
	return _speed;
}
double Ghost::getWeaknessDuration(){
	return _weaknessDuration;
}
int Ghost::getPoints(){
	return _points;
}		
int Ghost::getLevel(){
	return _level;
}

void Ghost::setSceneNode(Ogre::SceneNode * node){
	_node = node;
}
void Ghost::setGraphVertex(GraphVertex * vertex){
	_vertex = vertex;
}
void Ghost::setTarget(GraphVertex * vertex){
	_target = vertex;
}
void Ghost::setHealth(int hp){
	_health = hp;
}
void Ghost::setDirection(char direction){
	_direction = direction;
}
void Ghost::setType(char type){
	_type = type;
}
void Ghost::setMode(char mode){
	_mode = mode;
}
void Ghost::setSpeed(double speed){
	_speed = speed;
}
void Ghost::setWeaknessDuration(double duration){
	_weaknessDuration = duration;
}
void Ghost::setPoints(int points){
	_points = points;
}
void Ghost::setLevel(int level){
	_level = level;
	_speed = 1.0 + 0.05*(_level - 1);
	_weaknessDuration = 5.0 - 0.25*(_level - 1);  //que tambien sirva como tiempo de respawn?
	if (_level >= 10){
		_mode = 'C';
	}
}