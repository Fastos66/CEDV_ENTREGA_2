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

  std::vector<Ghost> *ghosts;
  _movementController = new MovementController(ghosts, _chara);
  _movementController->setGraph(_scene->getGraph());
  pruebaCharacter();
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
  char previousDirection = _chara->getDirection();
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
    _sceneMgr->getSceneNode("MapaM")->setVisible(false);
    Ogre::Vector3 charaSNPosition = _chara->getSceneNode()->getPosition();
    Ogre::Vector3 charaTargetPosition;
    Ogre::Vector3 charaVertexPosition;
    convertCoordinates(charaSNPosition, 0.0);
    charaVertexPosition = _chara->getGraphVertex()->getData().getPosition();
    if(_chara->getTarget()!= NULL){
      charaTargetPosition = _chara->getTarget()->getData().getPosition();
      cout<< "DIRECTION: " << _chara->getDirection();
      cout<< "\nSCENE NODE: X "<< charaSNPosition.x <<"Y " << charaSNPosition.y <<"Z " << charaSNPosition.z << " \nMI TARGET ES X "<< charaTargetPosition.x <<"Y " << charaTargetPosition.y <<"Z " << charaTargetPosition.z << "\n";
      cout<< "VERTEX: X "<< charaVertexPosition.x <<"Y " << charaVertexPosition.y <<"Z " << charaVertexPosition.z << "\n";
    }
    else{
      cout<< "MI TARGET ES NULL\n";
    }
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


void PlayState::pruebaCharacter(){
  Graph *myGraph = _scene->getGraph();
  Ogre::Entity *myEntity = _sceneMgr->createEntity("character","Melon.mesh");
  Ogre::SceneNode *myNode = _sceneMgr->createSceneNode("character");
  myNode->setScale(0.75,0.75,0.75);
  myNode->attachObject(myEntity); 
  Character *character = new Character(myNode, myGraph->getVertexes().at(2));
  _chara = character;
  _chara->setSpeed(0.005);
  _chara->setDirection('-');
  _chara->setTarget(myGraph->getVertexes().at(2));
  _sceneMgr->getRootSceneNode()->addChild(myNode);
  Ogre::Vector3 vectAux = myGraph->getVertexes().at(2)->getData().getPosition();
  convertCoordinates(vectAux,0.0);
  //Coordenadas cambiadas. El grafo sigue mal
  _chara->getSceneNode()->setPosition(vectAux);
  cout <<"CREADO CHARACTER \n";
}

void PlayState::pruebaGhost(){
  Graph *myGraph = _scene->getGraph();
  Ogre::Entity *myEntity = _sceneMgr->createEntity("fantasmaQ","Melon.mesh");
  Ogre::SceneNode *myNode = _sceneMgr->createSceneNode("fantasmaQ");
  myNode->attachObject(myEntity); 
  Ghost *ghost = new Ghost(myNode, myGraph->getVertexes().at(0));
  _sceneMgr->getRootSceneNode()->addChild(myNode);
  cout <<"CREADO GHOST \n";
}

void PlayState::convertCoordinates(Ogre::Vector3 &vect, double offset){
  double aux = vect.y;
  vect.y = vect.z + offset;
  vect.z = aux;
}


