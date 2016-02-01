#include "MovementController.h"
#include <algorithm>

MovementController::MovementController(std::vector<Ghost> *ghosts, Character *chara){
	_ghosts = ghosts;
	_chara = chara;
	_validDirections = new vector<char>;
}
MovementController::MovementController(Graph * graph){
	_graph = graph;
	_ghosts = new vector<Ghost>;
	_chara = new Character();
	_validDirections = new vector<char>;
}
MovementController::~MovementController(){
	
}
		
std::vector<char> * MovementController::getGhostValidDirections(Ghost *ghost){
	std::vector<GraphVertex*> adjacentVertices; 
	GraphVertex *aux;
	Ogre::Vector3 auxPosition;
	Ogre::Vector3 ghostPosition = ghost->getGraphVertex()->getData().getPosition();
	int i = 0;
	if(_graph != NULL){
	 	adjacentVertices = _graph->adjacents(ghost->getGraphVertex()->getData().getIndex());
	 	for(i=0; i<adjacentVertices.size(); i++){
	 		aux = adjacentVertices.at(i);
	 		auxPosition = aux->getData().getPosition();
	 		if(ghostPosition.x > auxPosition.x){
	 			_validDirections->push_back('R');  //Hay un vecino a la derecha
	 		}
	 		else if(ghostPosition.x < auxPosition.x){
	 			_validDirections->push_back('L');  //Hay un vecino a la izquierda
	 		}
	 		if(ghostPosition.y < auxPosition.y){
	 			_validDirections->push_back('U');  //Hay un vecino arriba
	 		}
	 		else if(ghostPosition.y > auxPosition.y){
	 			_validDirections->push_back('D');  //Hay un vecino abajo
	 		}
	 	}
	}
	return _validDirections;
}
std::vector<char> * MovementController::getCharaValidDirections(Character *chara){
	std::vector<GraphVertex*> adjacentVertices; 
	GraphVertex *aux;
	Ogre::Vector3 auxPosition;
	Ogre::Vector3 charaPosition = chara->getGraphVertex()->getData().getPosition();
	int i = 0;
	if(_graph != NULL){
	 	adjacentVertices = _graph->adjacents(chara->getGraphVertex()->getData().getIndex());
	 	for(i=0; i<adjacentVertices.size(); i++){
	 		aux = adjacentVertices.at(i);
	 		auxPosition = aux->getData().getPosition();
	 		if(charaPosition.x > auxPosition.x){
	 			_validDirections->push_back('R');  //Hay un vecino a la derecha
	 			//cout << "R ";
	 		}
	 		else if(charaPosition.x < auxPosition.x){
	 			_validDirections->push_back('L');  //Hay un vecino a la izquierda
	 			//cout << "L ";
	 		}
	 		if(charaPosition.y < auxPosition.y){
	 			_validDirections->push_back('U');  //Hay un vecino arriba
	 			//cout << "U ";
	 		}
	 		else if(charaPosition.y > auxPosition.y){
	 			_validDirections->push_back('D');  //Hay un vecino abajo
	 			//cout << "D ";
	 		}
	 	}
	}
	return _validDirections;	
}
char MovementController::getGhostNextDirection(Ghost *ghost){
	return getGhostValidDirections(ghost)->at(0);
	//return '-';
	//TO_DO
}

bool MovementController::isCharValidDirection(Character *chara){
	bool res = false;
	_validDirections = getCharaValidDirections(chara);
	if (std::find(_validDirections->begin(), _validDirections->end(), chara->getDirection()) != _validDirections->end()){
  		res = true;
	}
	return res;
}
		
GraphVertex * MovementController::getVertexByDirection(Character *chara){
	std::vector<GraphVertex*> adjacentVertices; 
	GraphVertex *aux;
	Ogre::Vector3 auxPosition;
	Ogre::Vector3 charaPosition = chara->getGraphVertex()->getData().getPosition();
	int i = 0;
	if(_graph != NULL){
	 	adjacentVertices = _graph->adjacents(chara->getGraphVertex()->getData().getIndex());
	 	for(i=0; i<adjacentVertices.size(); i++){
	 		aux = adjacentVertices.at(i);
	 		auxPosition = aux->getData().getPosition();
	 		if((charaPosition.x > auxPosition.x) && chara->getDirection()=='R') {
	 			break;
	 		}
	 		else if((charaPosition.x < auxPosition.x) && chara->getDirection()=='L'){
	 			break;
	 		}
	 		if((charaPosition.y < auxPosition.y) && chara->getDirection()=='U'){
	 			break;
	 		}
	 		else if((charaPosition.y > auxPosition.y) && chara->getDirection()=='D'){
	 			break;
	 		}
	 	}
	}
	return aux;
}

void MovementController::setGhosts(std::vector<Ghost> *ghosts){
	_ghosts = ghosts;
}
void MovementController::setChara(Character *chara){
	_chara = chara;
}
void MovementController::setGraph(Graph *graph){
	_graph = graph;
}