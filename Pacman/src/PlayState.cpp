#include "PlayState.h"
#include "PauseState.h"
#include "MyScenePlay.h"
#define EPSILON 0.02

template<> PlayState* Ogre::Singleton<PlayState>::msSingleton = 0;

void
PlayState::enter ()
{
  _root = Ogre::Root::getSingletonPtr();

  // Se recupera el gestor de escena y la cámara.
  _sceneMgr = _root->getSceneManager("SceneManager");
  _camera = _sceneMgr->getCamera("IntroCamera");
  _viewport = _root->getAutoCreatedWindow()->addViewport(_camera);
  // Nuevo background colour.
  _viewport->setBackgroundColour(Ogre::ColourValue(0.0,0.0,0.0));
  //Ogre::SceneNode* sn = _sceneMgr->getSceneNode("ground");
  printf("Estado:Play\n"); 
  try {
    _importer = new Importer;
    _scene = new Scene;
    _importer->parseScene("./data/grafo.xml",_scene);
  }catch (...){
    cerr << "Unexpected exception!" << endl;
  }
  CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setVisible(false);
  //cout << "\t#Vertexes: " << _scene->getGraph()->getVertexes().size() << endl;
  //cout << "\t#Edges: " << _scene->getGraph()->getEdges().size() << endl;
  
  _splay = new MyScenePlay(_sceneMgr,_scene,_camera);
  _splay -> cargarscenainicial();
  _splay -> creacionMapa();
  _splay -> crearmenuCEGUI();
  _exitGame = false;
  _inMovement = false;

  _ghosts = new std::vector<Ghost*>;
  _movementController = new MovementController(_ghosts, _chara);
  _movementController->setGraph(_scene->getGraph());
  createCharacter();
  createGhosts();
  _lanzaranimationPG = true;
}

void
PlayState::exit ()
{
  //_sceneMgr->clearScene();
  _root->getAutoCreatedWindow()->removeAllViewports();
}

void
PlayState::pause()
{
}

void
PlayState::resume()
{
  // Se restaura el background colour.
  _viewport->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 1.0));
}

bool
PlayState::frameStarted
(const Ogre::FrameEvent& evt)
{
  if((_ghosts->at(0)->getSceneNode()->getPosition() == _ghosts->at(0)->getGraphVertex()->getData().getPosition()) || (_ghosts->at(0)->getSceneNode()->getPosition() == _ghosts->at(0)->getTarget()->getData().getPosition())){
    //si se encuentra en un nodo, calcular la direccion
    _ghosts->at(0)->setDirection(_movementController->getGhostNextDirection(_ghosts->at(0)));
  }
  moveCharacter();
  moveGhosts();
  Ogre::Real deltaT = evt.timeSinceLastFrame;
  if (_lanzaranimationPG){
    _animStatePacmanG = _sceneMgr->getEntity("character")->getAnimationState("moveMouth");
    _animStatePacmanG->setTimePosition(0.0);
    _animStatePacmanG->setEnabled(true);
    _animStatePacmanG->setLoop(true);
    _lanzaranimationPG = false;
  }
  if (_animStatePacmanG != NULL) {
     if (_animStatePacmanG->hasEnded()) {
       _animStatePacmanG->setTimePosition(0.0);
       _animStatePacmanG->setEnabled(false);
     }
     else {
       _animStatePacmanG->addTime(deltaT);
     }
  }
  return true;
}

bool
PlayState::frameEnded
(const Ogre::FrameEvent& evt)
{
  if (_exitGame)
    return false;
  
  return true;
}

void
PlayState::keyPressed
(const OIS::KeyEvent &e)
{
  //char previousDirection = _chara->getDirection();
  if (e.key == OIS::KC_W && !_inMovement) { // para arriba
    _chara->setDirection('U');
    _chara->setTarget(_movementController->getVertexByDirection(_chara));
    _inMovement = true;
  }
  if (e.key == OIS::KC_A && !_inMovement) { // para izquierda
    _chara->setDirection('L');
    _chara->setTarget(_movementController->getVertexByDirection(_chara));
    _inMovement = true;
  }
  if (e.key == OIS::KC_S && !_inMovement) { // para abajo
    _chara->setDirection('D');
    _chara->setTarget(_movementController->getVertexByDirection(_chara));
    _inMovement = true;
  }
  if (e.key == OIS::KC_D && !_inMovement) { // para derecha
    _chara->setDirection('R');
    _chara->setTarget(_movementController->getVertexByDirection(_chara));
    _inMovement = true;
  }
  if (e.key == OIS::KC_P) {
    Ogre::Vector3 charaSNPosition = _chara->getSceneNode()->getPosition();
    Ogre::Vector3 charaTargetPosition;
    Ogre::Vector3 charaVertexPosition;
    convertCoordinates(charaSNPosition, 0.0);
    charaVertexPosition = _chara->getGraphVertex()->getData().getPosition();
    if(_chara->getTarget()!= NULL){
      charaTargetPosition = _chara->getTarget()->getData().getPosition();
      cout<< "DIRECTION: " << _chara->getDirection();
      cout<< "\nSCENE NODE: X "<< charaSNPosition.x <<"Y " << charaSNPosition.y <<"Z " << charaSNPosition.z << " \nMI TARGET ES: "<<_chara->getTarget()->getData().getIndex()<<" X= "<< charaTargetPosition.x <<" Y= " << charaTargetPosition.y <<" Z=" << charaTargetPosition.z << "\n";
      cout<< "VERTEX: "<<_chara->getGraphVertex()->getData().getIndex()<<" X= "<< charaVertexPosition.x <<" Y= " << charaVertexPosition.y <<" Z= " << charaVertexPosition.z << "\n";
      _movementController->printVecinos(_chara->getGraphVertex());
    }
    else{
      cout<< "MI TARGET ES NULL\n";
    }
  }
  if (e.key == OIS::KC_V) {
    _sceneMgr->getSceneNode("MapaM")->setVisible(true);
    _movementController->printVecinos(_chara->getGraphVertex());
  }
  if (e.key == OIS::KC_B) {
    _sceneMgr->getSceneNode("MapaM")->setVisible(false);
  }
  if (e.key == OIS::KC_G) {
     Graph *myGraph = _scene->getGraph();
    _movementController->printAdjList(myGraph);
  }
  // Tecla p --> PauseState.
  //if (e.key == OIS::KC_P) {
  //  pushState(PauseState::getSingletonPtr());
  //}
}

void
PlayState::keyReleased
(const OIS::KeyEvent &e)
{
  if (e.key == OIS::KC_ESCAPE) {
    _exitGame = true;
  }
}

void
PlayState::mouseMoved
(const OIS::MouseEvent &e)
{
}

void
PlayState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void
PlayState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

PlayState*
PlayState::getSingletonPtr ()
{
return msSingleton;
}

PlayState&
PlayState::getSingleton ()
{ 
  assert(msSingleton);
  return *msSingleton;
}

MovementController * PlayState::getMovementController(){
  return _movementController;
}
void PlayState::setMovementController(MovementController* movementController){
  _movementController = movementController;
}


void PlayState::createCharacter(){
  Graph *myGraph = _scene->getGraph();
  Ogre::Entity *myEntity = _sceneMgr->createEntity("character","PacmanP.mesh");
  Ogre::SceneNode *myNode = _sceneMgr->createSceneNode("character");
  myNode->setScale(0.75,0.75,0.75);
  myNode->attachObject(myEntity); 
  Character *character = new Character(myNode, myGraph->getVertexes().at(57));
  _chara = character;
  _chara->setSpeed(0.015);
  _chara->setDirection('-');
  _chara->setTarget(myGraph->getVertexes().at(57));
  _sceneMgr->getRootSceneNode()->addChild(myNode);
  Ogre::Vector3 vectAux = myGraph->getVertexes().at(57)->getData().getPosition();
  convertCoordinates(vectAux,0.0);
  //Coordenadas cambiadas. El grafo sigue mal
  _chara->getSceneNode()->setPosition(vectAux);
  cout <<"CREADO CHARACTER \n";
}

void PlayState::createGhosts(){
  Graph *myGraph = _scene->getGraph();
  //CREACION FANTASMAS
  int verticesf[4] = {13,27,28,29};
  string nombresfantasma[4] = {"Cebolla","Tomate","Berenjena","Guisante"};
  string nombresfantasmamesh[4] = {"FantasmaJCebolla","FantasmaJTomate",
                                    "FantasmaJBerenjena","FantasmaJGuisante"};
  for (int i = 0; i < 4; ++i){
      ostringstream os;
      os << "fantasma" << nombresfantasma[i];
      ostringstream osA;
      osA << nombresfantasmamesh[i]<<".mesh";

      Ogre::Entity *myEntityG = _sceneMgr->createEntity(os.str(),osA.str());
      Ogre::SceneNode *myNodeG = _sceneMgr->createSceneNode(os.str());
      myNodeG->setScale(0.75,0.75,0.75);
      myNodeG->attachObject(myEntityG);
      Ghost *ghost = new Ghost(myNodeG, myGraph->getVertexes().at(verticesf[i]));
      ghost->setSpeed(0.015);
      ghost->setDirection('-');
      ghost->setTarget(myGraph->getVertexes().at(verticesf[i]));
      if (nombresfantasma[i].compare("Tomate")==0 ||nombresfantasma[i].compare("Guisante")==0){
           myNodeG->yaw(Ogre::Degree(82.5)); 
      }else{
           myNodeG->yaw(Ogre::Degree(-180));   
      }
      _sceneMgr->getRootSceneNode()->addChild(myNodeG);
      Ogre::Vector3 vectAux = myGraph->getVertexes().at(verticesf[i])->getData().getPosition();
      convertCoordinates(vectAux,0.0);
      //Coordenadas cambiadas. El grafo sigue mal
      ghost->getSceneNode()->setPosition(vectAux);
      _ghosts->push_back(ghost);
      cout <<"CREADO GHOST: " << os.str() << endl;
  }
  
}

//meter el codigo de mover las cositas en estas funciones
void PlayState::moveCharacter(){
  Ogre::Vector3 charaSNPosition = _chara->getSceneNode()->getPosition();
  Ogre::Vector3 charaTargetPosition;
  convertCoordinates(charaSNPosition, 0.0);
  
  charaTargetPosition = _chara->getTarget()->getData().getPosition();
  if(std::abs(charaSNPosition.x - charaTargetPosition.x) <= EPSILON){
    if(std::abs(charaSNPosition.y - charaTargetPosition.y) <= EPSILON){
      // si el personaje esta muy cerca del nodo target
      //cout<<"ESTOY EN TARGET\n";
      Ogre::Vector3 vecPos = _chara->getTarget()->getData().getPosition();
      convertCoordinates(vecPos,0.0);
      _chara->getSceneNode()->setPosition(vecPos);
      _inMovement = false;
      _chara->setGraphVertex(_chara->getTarget());
      if(_movementController->isCharValidDirection(_chara)){
         _chara->setTarget(_movementController->getVertexByDirection(_chara));
      }
      _chara->setDirection('-');
      _chara->setTarget(_chara->getGraphVertex());
      //recalculo target
    }
  }
  if(_chara->getGraphVertex()->getData().getIndex()!=_chara->getTarget()->getData().getIndex()){
    if(_movementController->isCharValidDirection(_chara)){
      if(_chara->getDirection() == 'R'){
      _chara->getSceneNode()->setPosition(_chara->getSceneNode()->getPosition() + Ogre::Vector3(-_chara->getSpeed(),0,0));
      }
      else if(_chara->getDirection() == 'D'){
        _chara->getSceneNode()->setPosition(_chara->getSceneNode()->getPosition() + Ogre::Vector3(0,0,-_chara->getSpeed()));
      }
      else if(_chara->getDirection() == 'L'){
        _chara->getSceneNode()->setPosition(_chara->getSceneNode()->getPosition() + Ogre::Vector3(_chara->getSpeed(),0,0));
      }
      else if(_chara->getDirection() == 'U'){
        _chara->getSceneNode()->setPosition(_chara->getSceneNode()->getPosition() + Ogre::Vector3(0,0,_chara->getSpeed()));
      }
      //cout<< "ESTOY EN EL VERTICE " << _chara->getGraphVertex()->getData().getIndex() << "\n";
      /*if(_chara->getTarget()!= NULL){
        cout<< "X "<< charaSNPosition.x <<"Y " << charaSNPosition.y <<"Z " << charaSNPosition.z << " MI TARGET ES X "<< charaTargetPosition.x <<"Y " << charaTargetPosition.y <<"Z " << charaTargetPosition.z << "\n";
      }
      else{
        cout<< "MI TARGET ES NULL\n";
      }*/
    }
  }
}

void PlayState::moveGhosts(){
  Ogre::Vector3 ghostSNPosition = _ghosts->at(0)->getSceneNode()->getPosition();
  Ogre::Vector3 ghostTargetPosition;
  convertCoordinates(ghostSNPosition, 0.0);
  
  ghostTargetPosition = _ghosts->at(0)->getTarget()->getData().getPosition();
  if(std::abs(ghostSNPosition.x - ghostTargetPosition.x) <= EPSILON){
    if(std::abs(ghostSNPosition.y - ghostTargetPosition.y) <= EPSILON){
      // si el personaje esta muy cerca del nodo target
      //cout<<"ESTOY EN TARGET\n";
      Ogre::Vector3 vecPos = _ghosts->at(0)->getTarget()->getData().getPosition();
      convertCoordinates(vecPos,0.0);
      _ghosts->at(0)->getSceneNode()->setPosition(vecPos);
      _inMovement = false;
      _ghosts->at(0)->setGraphVertex(_ghosts->at(0)->getTarget());
      if(_movementController->isGhostValidDirection(_ghosts->at(0))){
         _ghosts->at(0)->setTarget(_movementController->getVertexByDirection(_ghosts->at(0)));
      }
      _ghosts->at(0)->setDirection('-');
      _ghosts->at(0)->setTarget(_ghosts->at(0)->getGraphVertex());
      //recalculo target
    }
  }
  if(_ghosts->at(0)->getGraphVertex()->getData().getIndex()!=_ghosts->at(0)->getTarget()->getData().getIndex()){
    if(_movementController->isGhostValidDirection(_ghosts->at(0))){
      if(_ghosts->at(0)->getDirection() == 'R'){
      _ghosts->at(0)->getSceneNode()->setPosition(_ghosts->at(0)->getSceneNode()->getPosition() + Ogre::Vector3(-_ghosts->at(0)->getSpeed(),0,0));
      }
      else if(_ghosts->at(0)->getDirection() == 'D'){
        _ghosts->at(0)->getSceneNode()->setPosition(_ghosts->at(0)->getSceneNode()->getPosition() + Ogre::Vector3(0,0,-_ghosts->at(0)->getSpeed()));
      }
      else if(_ghosts->at(0)->getDirection() == 'L'){
        _ghosts->at(0)->getSceneNode()->setPosition(_ghosts->at(0)->getSceneNode()->getPosition() + Ogre::Vector3(_ghosts->at(0)->getSpeed(),0,0));
      }
      else if(_ghosts->at(0)->getDirection() == 'U'){
        _ghosts->at(0)->getSceneNode()->setPosition(_ghosts->at(0)->getSceneNode()->getPosition() + Ogre::Vector3(0,0,_ghosts->at(0)->getSpeed()));
      }
      //cout<< "ESTOY EN EL VERTICE " << _chara->getGraphVertex()->getData().getIndex() << "\n";
      /*if(_chara->getTarget()!= NULL){
        cout<< "X "<< charaSNPosition.x <<"Y " << charaSNPosition.y <<"Z " << charaSNPosition.z << " MI TARGET ES X "<< charaTargetPosition.x <<"Y " << charaTargetPosition.y <<"Z " << charaTargetPosition.z << "\n";
      }
      else{
        cout<< "MI TARGET ES NULL\n";
      }*/
    }
  }
}

void PlayState::convertCoordinates(Ogre::Vector3 &vect, double offset){
  double aux = vect.y;
  vect.y = vect.z + offset;
  vect.z = aux;
}

void PlayState::changeCharaFacing(Character *chara){
  //Ogre::SceneNode *sceneNode = chara->getSceneNode();
  char direction = chara->getDirection();
  switch(direction){
    case 'R':
      break;
    case 'L':
      break;
    case 'U':
      break;
    case 'D':
      break;
  }
}

