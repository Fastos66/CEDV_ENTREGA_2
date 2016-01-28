#include "MovementController.h"

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
	 		if(ghostPosition.x < auxPosition.x){
	 			_validDirections->push_back('R');  //Hay un vecino a la derecha
	 		}
	 		else if(ghostPosition.x > auxPosition.x){
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
	 		if(charaPosition.x < auxPosition.x){
	 			_validDirections->push_back('R');  //Hay un vecino a la derecha
	 		}
	 		else if(charaPosition.x > auxPosition.x){
	 			_validDirections->push_back('L');  //Hay un vecino a la izquierda
	 		}
	 		if(charaPosition.y < auxPosition.y){
	 			_validDirections->push_back('U');  //Hay un vecino arriba
	 		}
	 		else if(charaPosition.y > auxPosition.y){
	 			_validDirections->push_back('D');  //Hay un vecino abajo
	 		}
	 	}
	}
	return _validDirections;	
}
char MovementController::getGhostNextDirection(Ghost *ghost){
	return '-';
	//TO_DO
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