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
#include <cmath>

using namespace std;

class MovementController
{
	public:
		MovementController(std::vector<Ghost*> *ghosts, Character *chara);
		MovementController(Graph *graph);
		~MovementController();
		
		std::vector<char> *getGhostValidDirections(Ghost *ghost);
		std::vector<char> *getCharaValidDirections(Character *chara);
		char getGhostNextDirection(Ghost *ghost, Character *chara);
		bool isCharValidDirection(Character *chara);
		bool isGhostValidDirection(Ghost *ghost);
		GraphVertex * getVertexByDirection(Character *chara);
		GraphVertex * getVertexByDirection(Ghost * ghost);
		
		void setGhosts(std::vector<Ghost*> *ghosts);
		void setChara(Character *chara);
		void setGraph(Graph *graph);
		void printVecinos(GraphVertex *vertex);
		int ** setAdjListGraph(Graph *graph);
		void printAdjList(Graph *graph);

	private:
		Graph *_graph;
		std::vector<Ghost*> *_ghosts;
		Character *_chara;
		std::vector<char> *_validDirections;
		//int _adjListGraph[N_VERTICES][N_VERTICES];
		//int **_adjListGraph;
};

#endif