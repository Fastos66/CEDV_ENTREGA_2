#ifndef GHOST_H
#define GHOST_H

#include <iostream>
#include <sstream>
#include <string> 
#include <OGRE/Ogre.h>

using namespace std;

class Ghost
{
	public:
		Ghost(Ogre::SceneNode * node);
		Ghost();
		~Ghost();
		
		Ogre::SceneNode * getSceneNode();
		int getHealth();
		char getDirection();
		double getPositionX();
		double getPositionY();
		char getType();
		bool isWeak();
		
		void setSceneNode(Ogre::SceneNode * node);
		void setHealth(int hp);
		void setDirection(char direction);
		void setPositionX(double posX);
		void setPositionY(double posY);
		void setType(char type);
		void setWeak(char weak);

	private:
		Ogre::SceneNode * _node;	
		int _health;
		char _direction; // U-> up, R-> right, D-> down, L-> left
		double _positionX;
		double _positionY;
		char _type;
    	bool _weak;

};

#endif