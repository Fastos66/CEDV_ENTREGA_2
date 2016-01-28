#ifndef MOVEMENTCONTROLLER_H
#define MOVEMENTCONTROLLER_H

#include <iostream>
#include <sstream>
#include <string> 
#include <OGRE/Ogre.h>
#include <vector>
#include "Ghost.h"
#include "Character.h"
#include "Graph.h"
#include <OgreVector3.h>

using namespace std;

class MovementController
{
	public:
		MovementController(std::vector<Ghost> *ghosts, Character *chara);
		MovementController(Graph *graph);
		~MovementController();
		
		std::vector<char> *getGhostValidDirections(Ghost *ghost);
		std::vector<char> *getCharaValidDirections(Character *chara);
		char getGhostNextDirection(Ghost *ghost);
		
		void setGhosts(std::vector<Ghost> *ghosts);
		void setChara(Character *chara);
		void setGraph(Graph *graph);

	private:
		Graph *_graph;
		std::vector<Ghost> *_ghosts;
		Character *_chara;
		std::vector<char> *_validDirections;
		
};

#endif