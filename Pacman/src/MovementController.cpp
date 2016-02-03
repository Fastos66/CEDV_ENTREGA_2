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
	unsigned int i = 0;
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
	unsigned int i = 0;
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
	GraphVertex *aux = chara->getGraphVertex(); // si no tiene vecinos en la direccion deseada, te devuelve a ti mismo
	Ogre::Vector3 auxPosition;
	Ogre::Vector3 charaPosition = chara->getGraphVertex()->getData().getPosition();
	unsigned int i = 0;
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
	 		aux = chara->getGraphVertex();
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
void MovementController::printVecinos(GraphVertex *vertex){
	std::vector<GraphVertex*> adjacentVertices;
	unsigned int i = 0;
	adjacentVertices = _graph->adjacents(vertex->getData().getIndex());
	cout<<"VECINOS DE "<<vertex->getData().getIndex()<<": ";
	for(i=0; i<adjacentVertices.size(); i++){
		cout<<adjacentVertices.at(i)->getData().getIndex()<<" ";
	}
	cout<<"\n";
}
int ** MovementController::setAdjListGraph(Graph *graph){
	std::vector<GraphVertex*> graphVertices = graph->getVertexes(); 
	std::vector<GraphVertex*> adjacents;
	int adjListGraph[graphVertices.size()][graphVertices.size()];
	int * adjListGraphRows[graphVertices.size()]; 
	int ** result;
	unsigned int i = 0, j = 0;
	// inicializar la matriz de adyacencias a 0
	for(i=0;i<graphVertices.size();i++){
		for(j=0;j<graphVertices.size();j++){
			adjListGraph[i][j]=0;
		}
	}
	//poner 1 donde sean adyacentes
	for(i=0;i<graphVertices.size();i++){
		adjacents = graph->adjacents(graphVertices.at(i)->getData().getIndex()); //coger los vecinos de cada nodo
		for(j=0; j<adjacents.size();j++){
			adjListGraph[i][adjacents.at(j)->getData().getIndex()] = 1; //poner un 1 si son vecinos
		}
		adjListGraphRows[i]=adjListGraph[i];
	}

	result = adjListGraphRows;
	return result;
}
void MovementController::printAdjList(Graph* graph){
	unsigned int i = 0, j = 0;
	int ** adjList = setAdjListGraph(graph);
	std::vector<GraphVertex*> graphVertices = _graph->getVertexes();
	cout << "\n";
	for(i=0;i<graphVertices.size();i++){
		cout << "V " << graphVertices.at(i)->getData().getIndex()<< ": ";
		for(j=0; j<graphVertices.size();j++){
			cout << adjList[i][j] << " ";
			if(j%10==9)
				cout <<"|"<<j<<"|";
		}
		cout << "\n";
	}
	//cout << adjList[0][0] << " " << adjList[0][1] << " " << adjList[0][2] << " " << adjList[0][3] << " " << adjList[0][4] << " " << adjList[0][5] << " " << adjList[0][6] << " " << adjList[0][7] << " " << adjList[0][8] << " " << adjList[0][9]       << "\n";
}