#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <sstream>
#include <string> 
using namespace std;

class Player
{
	public:
		Player(string name, string puntos);
		~Player();
		string getname();
		string getpuntos();
	private:
		string _name;
		string _puntos;	
};

#endif