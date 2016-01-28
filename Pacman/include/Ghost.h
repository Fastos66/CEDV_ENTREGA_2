#ifndef GHOST_H
#define GHOST_H

#include <iostream>
#include <sstream>
#include <string> 
#include <OGRE/Ogre.h>
#include "GraphVertex.h"

using namespace std;

class Ghost
{
	public:
		Ghost(Ogre::SceneNode * node, GraphVertex * vertex);
		Ghost();
		~Ghost();
		
		Ogre::SceneNode * getSceneNode();
		GraphVertex * getGraphVertex();
		int getHealth();
		char getDirection();
		double getPositionX();
		double getPositionY();
		char getType();
		bool isWeak();

		
		void setSceneNode(Ogre::SceneNode * node);
		void setGraphVertex(GraphVertex * vertex);
		void setHealth(int hp);
		void setDirection(char direction);
		void setPositionX(double posX);
		void setPositionY(double posY);
		void setType(char type);
		void setWeak(char weak);


	private:
		Ogre::SceneNode * _node;
		GraphVertex * _vertex;	
		int _health;
		char _direction; // U-> up, R-> right, D-> down, L-> left
		double _positionX;
		double _positionY;
		char _type;
    	bool _weak;

};

#endif