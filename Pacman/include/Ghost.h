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
		GraphVertex * getTarget();
		int getLevel();
		int getHealth();
		char getDirection();
		char getType();
		char getMode();
		double getSpeed();
		double getWeaknessDuration();
		int getPoints();

		
		void setSceneNode(Ogre::SceneNode * node);
		void setGraphVertex(GraphVertex * vertex);
		void setTarget(GraphVertex * vertex);
		void setLevel(int level);
		void setHealth(int hp);
		void setDirection(char direction);
		void setType(char type);
		void setMode(char mode);
		void setSpeed(double speed);
		void setWeaknessDuration(double duration);
		void setPoints(int points);


	private:
		Ogre::SceneNode * _node;
		GraphVertex * _vertex;	
		GraphVertex * _target;
		int _level;
		int _health;
		char _direction; // U-> up, R-> right, D-> down, L-> left
		char _type;
    	char _mode;  // W-> Weak, C -> Chasing, S -> Scattering
    	double _speed;
    	double _weaknessDuration;
    	int _points;

};

#endif