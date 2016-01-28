#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <sstream>
#include <string> 
#include <OGRE/Ogre.h>
#include "GraphVertex.h"

using namespace std;

class Character
{
	public:
		Character(Ogre::SceneNode * node, GraphVertex * vertex);
		Character();
		~Character();
		
		Ogre::SceneNode * getSceneNode();
		GraphVertex * getGraphVertex();
		int getHealth();
		char getDirection();
		double getPositionX();
		double getPositionY();
		
		void setSceneNode(Ogre::SceneNode * node);
		void setGraphVertex(GraphVertex * vertex);
		void setHealth(int hp);
		void setDirection(char direction);
		void setPositionX(double posX);
		void setPositionY(double posY);

	private:
		Ogre::SceneNode * _node;
		GraphVertex	* _vertex;
		int _health;
		char _direction; // U-> up, R-> right, D-> down, L-> left
		double _positionX;
		double _positionY;
};

#endif