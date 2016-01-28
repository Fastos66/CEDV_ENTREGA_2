#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <sstream>
#include <string> 
#include <OGRE/Ogre.h>

using namespace std;

class Item
{
	public:
		Item(Ogre::SceneNode * node,bool melon);
		Item(bool melon);
		~Item();
		
		Ogre::SceneNode * getSceneNode();
		bool isMelon();
		int getScore();
		double getPositionX();
		double getPositionY();
		
		void setSceneNode(Ogre::SceneNode * node);
		void setMelon(bool melon);
		void setScore(int score);
		void setPositionX(double posX);
		void setPositionY(double posY);

	private:
		Ogre::SceneNode * _node;	
		bool _melon;
		int _score;
		double _positionX;
		double _positionY;
};

#endif