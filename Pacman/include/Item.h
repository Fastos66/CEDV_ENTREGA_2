#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <sstream>
#include <string> 
#include <OGRE/Ogre.h>
#include "GraphVertex.h"

using namespace std;

class Item
{
	public:
		Item(Ogre::SceneNode * node,bool melon);
		Item(bool melon);
		~Item();
		
		Ogre::SceneNode * getSceneNode();
		GraphVertex * getGraphVertex();
		bool isMelon();
		int getScore();
		bool isActive();
		
		void setSceneNode(Ogre::SceneNode * node);
		void setGraphVertex(GraphVertex * vertex);
		void setMelon(bool melon);
		void setScore(int score);
		void setActive(bool active);

	private:
		Ogre::SceneNode * _node;	
		GraphVertex * _vertex;
		bool _melon;
		int _score;
		bool _active;
};

#endif