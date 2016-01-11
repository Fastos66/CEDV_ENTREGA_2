#include "Player.h"
Player::Player(string name,string puntos){
	_name = name;
	_puntos = puntos;
}

Player::~Player(){}

string Player::getname(){
	return _name;
}
string Player::getpuntos(){
	return _puntos;
}