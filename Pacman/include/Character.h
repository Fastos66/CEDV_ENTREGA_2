#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <sstream>
#include <string> 
#include <OGRE/Ogre.h>

using namespace std;

class Character
{
	public:
		Character(Ogre::SceneNode * node);
		Character();
		~Character();
		
		Ogre::SceneNode * getSceneNode();
		int getHealth();
		char getDirection();
		double getPositionX();
		double getPositionY();
		
		void setSceneNode(Ogre::SceneNode * node);
		void setHealth(int hp);
		void setDirection(char direction);
		double setPositionX(double posX);
		double setPositionY(double posY);

	private:
		Ogre::SceneNode * _node;	
		int _health;
		char _direction; // U-> up, R-> right, D-> down, L-> left
		double _positionX;
		double _positionY;
};

#endif