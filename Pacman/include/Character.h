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
		GraphVertex * getTarget();
		int getHealth();
		char getDirection();
		double getSpeed();
		
		void setSceneNode(Ogre::SceneNode * node);
		void setGraphVertex(GraphVertex * vertex);
		void setTarget(GraphVertex * target);
		void setHealth(int hp);
		void setDirection(char direction);
		void setSpeed(double speed);

	private:
		Ogre::SceneNode * _node;
		GraphVertex	* _vertex;
		GraphVertex * _target;
		int _health;
		char _direction; // U-> up, R-> right, D-> down, L-> left
		double _positionX;
		double _positionY;
		double _speed;
};

#endif