#include "MovementController.h"
#include <algorithm>

MovementController::MovementController(std::vector<Ghost*> *ghosts, Character *chara){
	_ghosts = ghosts;
	_chara = chara;
	_validDirections = new vector<char>;
}
MovementController::MovementController(Graph * graph){
	_graph = graph;
	_ghosts = new vector<Ghost*>;
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
char MovementController::getGhostNextDirection(Ghost *ghost, Character *chara){
	//return getGhostValidDirections(ghost)->at(0);
	std::vector<GraphVertex*> adjacentVerts;
	int i = 0;
	char direction = '-';
	GraphVertex *vertex = new GraphVertex(); 
	GraphVertex *chosenVertex = NULL;
	double auxDistance = 0.0;
	double minDistance = 0.0;
	double difX = chara->getGraphVertex()->getData().getPosition().x - ghost->getGraphVertex()->getData().getPosition().x;
	double difY = chara->getGraphVertex()->getData().getPosition().y - ghost->getGraphVertex()->getData().getPosition().y;
	auxDistance = sqrt(abs(difX) * abs(difX) + abs(difY) * abs(difY));
	minDistance = auxDistance;
	adjacentVerts = _graph->adjacents(ghost->getGraphVertex()->getData().getIndex());
	for(i=0;i<adjacentVerts.size();i++){
		vertex = adjacentVerts.at(i);
		difX = chara->getGraphVertex()->getData().getPosition().x - vertex->getData().getPosition().x;
		difY = chara->getGraphVertex()->getData().getPosition().y - vertex->getData().getPosition().y;
		auxDistance = sqrt(abs(difX) * abs(difX) + abs(difY) * abs(difY));
		if(minDistance > auxDistance){
			minDistance = auxDistance;
			chosenVertex = vertex;
		}
	}

	if(chosenVertex != NULL){
		if((ghost->getGraphVertex()->getData().getPosition().x - chosenVertex->getData().getPosition().x)<0){
			direction = 'L';
		}
		else if((ghost->getGraphVertex()->getData().getPosition().x - chosenVertex->getData().getPosition().x)>0){
			direction = 'R';
		}
		else if((ghost->getGraphVertex()->getData().getPosition().y - chosenVertex->getData().getPosition().y)<0){
			direction = 'U';
		}
		else{
			direction = 'D';
		}
	}
	//cout << "DIR GHOST 0: "<<direction << "\n";
	return direction;
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

bool MovementController::isGhostValidDirection(Ghost *ghost){
	bool res = false;
	_validDirections = getGhostValidDirections(ghost);
	if (std::find(_validDirections->begin(), _validDirections->end(), ghost->getDirection()) != _validDirections->end()){
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
GraphVertex * MovementController::getVertexByDirection(Ghost *ghost){
	std::vector<GraphVertex*> adjacentVertices; 
	GraphVertex *aux = ghost->getGraphVertex(); // si no tiene vecinos en la direccion deseada, te devuelve a ti mismo
	Ogre::Vector3 auxPosition;
	Ogre::Vector3 ghostPosition = ghost->getGraphVertex()->getData().getPosition();
	unsigned int i = 0;
	if(_graph != NULL){
	 	adjacentVertices = _graph->adjacents(ghost->getGraphVertex()->getData().getIndex());
	 	for(i=0; i<adjacentVertices.size(); i++){
	 		aux = adjacentVertices.at(i);
	 		auxPosition = aux->getData().getPosition();
	 		if((ghostPosition.x > auxPosition.x) && ghost->getDirection()=='R') {
	 			break;
	 		}
	 		else if((ghostPosition.x < auxPosition.x) && ghost->getDirection()=='L'){
	 			break;
	 		}
	 		if((ghostPosition.y < auxPosition.y) && ghost->getDirection()=='U'){
	 			break;
	 		}
	 		else if((ghostPosition.y > auxPosition.y) && ghost->getDirection()=='D'){
	 			break;
	 		}
	 		aux = ghost->getGraphVertex();
	 	}
	}
	return aux;
}

void MovementController::setGhosts(std::vector<Ghost*> *ghosts){
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