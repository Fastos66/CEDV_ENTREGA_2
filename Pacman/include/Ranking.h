#ifndef RANKING_H
#define RANKING_H

#include <iostream>
#include <fstream>
#include <string>
#include <CEGUI.h>
#include <RendererModules/Ogre/Renderer.h>
#include <vector>
#include <stack>
#include "Player.h"
using namespace std;

class Ranking
{
public:
	Ranking();
	~Ranking();
	void leerPlayeryPuntos();
	void acturanking();
	void crearvectorPlayers(string s);
	void colocarJugadoresPILA();
private:
	std::vector<Player>* _pl;
	std::stack<Player>* _plcolocados;
	
};

#endif