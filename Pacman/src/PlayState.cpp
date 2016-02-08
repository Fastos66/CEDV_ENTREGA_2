#include "PlayState.h"
#include "PauseState.h"
#include "FinalGameState.h"
#include "MyScenePlay.h"
#define EPSILON 0.02
#define OMICRON 0.4
#define INVSTEPS 9

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
  _vItem = new std::vector<Item*>;

  _splay = new MyScenePlay(_sceneMgr,_scene,_camera);
  _splay -> cargarscenainicial();
  _splay -> creacionMapa(_vItem);
  _splay -> crearmenuCEGUI();
  _splay -> cargarlives();
  
  _exitGame = false;
  _inMovement = false;
  _isOver = true;

  _contadorItems = 0;
  _finalgame = false;
  _caught = false;
  _justTeleported = false;

  _ghosts = new std::vector<Ghost*>;
  _movementController = new MovementController(_ghosts, _chara);
  _movementController->setGraph(_scene->getGraph());
  createCharacter();
  createGhosts();
  _vector_anims_gum = new std::vector<Ogre::AnimationState*>;
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
  CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setVisible(false);
  _viewport->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 1.0));
}

bool
PlayState::frameStarted
(const Ogre::FrameEvent& evt)
{
  moveCharacter();
  moveGhosts();
  Ogre::Real deltaT = evt.timeSinceLastFrame;
  if (_lanzaranimationPG){
    _animStatePacmanG = _sceneMgr->getEntity("character")->getAnimationState("moveMouth");
    _animStatePacmanG->setTimePosition(0.0);
    _animStatePacmanG->setEnabled(true);
    _animStatePacmanG->setLoop(true);
    int posGum[4] = {0,9,71,80};
    for (int i = 0; i < 4; ++i){
        ostringstream os;
        os << "Gum" << posGum[i];  
        Ogre::AnimationState* animStateMelonG = _sceneMgr->getEntity(os.str())-> getAnimationState("FlotarMelon");
        animStateMelonG->setTimePosition(0.0);
        animStateMelonG->setEnabled(true);
        animStateMelonG->setLoop(true);
        _vector_anims_gum -> push_back(animStateMelonG);
    }
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
  for (int i = 0; i < 4; ++i){
      Ogre::AnimationState* animStateMelon = _vector_anims_gum->at(i);
      if (animStateMelon != NULL){
        if (animStateMelon->hasEnded()){
          animStateMelon->setTimePosition(0.0);
          animStateMelon->setEnabled(false);
        }else{
          animStateMelon->addTime(deltaT);
        }
      }
  }
  if (_finalgame){
     pushState(FinalGameState::getSingletonPtr());
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
  Ogre::Vector3 vectAux;
  //char previousDirection = _chara->getDirection();
  if (e.key == OIS::KC_W && !_inMovement) { // para arriba
    _chara->setDirection('U');
    _chara->setTarget(_movementController->getVertexByDirection(_chara));
    changeCharaFacing();
    _inMovement = true;
  }
  if (e.key == OIS::KC_A && !_inMovement) { // para izquierda
    _chara->setDirection('L');
    _chara->setTarget(_movementController->getVertexByDirection(_chara));
    changeCharaFacing();
    _inMovement = true;
    if(_chara->getGraphVertex()->getData().getIndex()<81){
      _justTeleported = false;
    }
  }
  if (e.key == OIS::KC_S && !_inMovement) { // para abajo
    _chara->setDirection('D');
    _chara->setTarget(_movementController->getVertexByDirection(_chara));
    changeCharaFacing();
    _inMovement = true;
     if(_chara->getGraphVertex()->getData().getIndex()<81){
      _justTeleported = false;
    }
  }
  if (e.key == OIS::KC_D && !_inMovement) { // para derecha
    _chara->setDirection('R');
    _chara->setTarget(_movementController->getVertexByDirection(_chara));
    changeCharaFacing();
    _inMovement = true;
  }
  // Tecla p --> PauseState.
  if (e.key == OIS::KC_P) {
      pushState(PauseState::getSingletonPtr());
  }
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
      cout << "NOMBRE DEL SN: " << myNodeG->getName() << endl;
      myNodeG->setScale(0.75,0.75,0.75);
      myNodeG->attachObject(myEntityG);
      Ghost *ghost = new Ghost(myNodeG, myGraph->getVertexes().at(verticesf[i]));
      ghost->setSpeed(0.01);
      ghost->setDirection('-');
      ghost->setTarget(myGraph->getVertexes().at(verticesf[i]));
      if (nombresfantasma[i].compare("Tomate")==0 ||nombresfantasma[i].compare("Guisante")==0){
           myNodeG->yaw(Ogre::Degree(82.5));
           ghost->setType('R'); //random movement
      }else{
           myNodeG->yaw(Ogre::Degree(-180)); 
           ghost->setType('I'); //intelligent movement  
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
  Graph *myGraph = _scene->getGraph();
  Ogre::Vector3 charaSNPosition = _chara->getSceneNode()->getPosition();
  Ogre::Vector3 charaTargetPosition;
  convertCoordinates(charaSNPosition, 0.0);
  unsigned int i = 0;
  int verticesm[4] = {0,9,71,80};
  Ogre::Vector3 auxPosition;
  int indexAux = _chara->getGraphVertex()->getData().getIndex();
  if((indexAux > 80)&& !_justTeleported){
    if(indexAux == 81){
      GameManager::getSingletonPtr()->_soundEffect = GameManager::getSingletonPtr()->_pSoundFXManager->load("s_teleport2.aiff");
      GameManager::getSingletonPtr()->_soundEffect->play();
      auxPosition = myGraph->getVertex(82)->getData().getPosition();
      _chara->setGraphVertex(myGraph->getVertex(82));
      _chara->setTarget(myGraph->getVertex(82));
      convertCoordinates(auxPosition,0.0);
      _chara->getSceneNode()->setPosition(auxPosition);
    }
    else{
      GameManager::getSingletonPtr()->_soundEffect = GameManager::getSingletonPtr()->_pSoundFXManager->load("s_teleport2.aiff");
      GameManager::getSingletonPtr()->_soundEffect->play();
      auxPosition = myGraph->getVertex(81)->getData().getPosition();
      _chara->setGraphVertex(myGraph->getVertex(81));
      _chara->setTarget(myGraph->getVertex(81));
      convertCoordinates(auxPosition,0.0);
      _chara->getSceneNode()->setPosition(auxPosition);
    }
    _justTeleported = true;
  }
  else{
    for(i=0;i<4;i++){
      auxPosition = myGraph->getVertex(verticesm[i])->getData().getPosition();
      if(abs(charaSNPosition.x - auxPosition.x) <= OMICRON){
        if(abs(charaSNPosition.y - auxPosition.y) <= OMICRON){
          if(_vItem->at(verticesm[i])->isActive()){  
            GameManager::getSingletonPtr()->_soundEffect = GameManager::getSingletonPtr()->_pSoundFXManager->load("s_melon.wav");
            GameManager::getSingletonPtr()->_soundEffect->play();
            _chara->setInvincibleSteps(INVSTEPS);
            cout << "I ON" <<endl;
          //cambiar color?
            Ogre::Entity *ent = static_cast<Ogre::Entity*>(_chara->getSceneNode()->getAttachedObject(0));
            for (unsigned int i=0; i<ent->getNumSubEntities(); i++) {
              Ogre::SubEntity *aux = ent->getSubEntity(i);
              if (aux->getMaterialName() == "CuerpoPacmanP"){
                aux->setMaterialName("CuerpoPacmanPower");
              } 
            }  
          }
        }
      }
    }
    if(_chara->getInvincibleSteps()>0){
      //hacer fantasmas debiles
      for(i=0;i<_ghosts->size();i++){
        _ghosts->at(i)->setMode('W');
      }
    }
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
        //Pacman Come Items
        Item *item =  _vItem->at(_chara->getGraphVertex()->getData().getIndex());
        if( item->isActive()){
            item ->getSceneNode()->setVisible(false);
            item->setActive(false);
            _splay->actualizarPuntos(item->getScore());
            _contadorItems++;
            if (_contadorItems==83){
              GameManager::getSingletonPtr()->_mainTrack->pause();
              GameManager::getSingletonPtr()->_soundEffect = GameManager::getSingletonPtr()->_pSoundFXManager->load("s_win.wav");
              GameManager::getSingletonPtr()->_soundEffect->play();
              _finalgame = true;
            }
        }
        
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
      }
    }
    else{
      if(_chara->getInvincibleSteps()>0){
        //le quitamos 1 paso de invencibilidad
        _chara->setInvincibleSteps(-1);
        if(_chara->getInvincibleSteps() == 0){ //Si no quedan pasos de invencibilidad
          cout << "I OFF" <<endl;
          //poner fantasmas no debiles otra vez
          for(i=0;i<_ghosts->size();i++){
            _ghosts->at(i)->setMode('C');
          }
          //volver a color original
          Ogre::Entity *ent = static_cast<Ogre::Entity*>(_chara->getSceneNode()->getAttachedObject(0));
          for (unsigned int i=0; i<ent->getNumSubEntities(); i++) {
            Ogre::SubEntity *aux = ent->getSubEntity(i);
            cout<<aux->getMaterialName()<<endl;
            if (aux->getMaterialName() == "CuerpoPacmanPower"){
              aux->setMaterialName("CuerpoPacmanP");
            } 
          }  
        }
      }
    }
  }
}

void PlayState::moveGhosts(){
  unsigned int i=0;
  for(i=0;i<_ghosts->size();i++){
    Ogre::Vector3 ghostSNPosition = _ghosts->at(i)->getSceneNode()->getPosition();
    Ogre::Vector3 ghostTargetPosition;
    Ogre::Vector3 auxPosition;
    Ogre::Vector3 charaSNPosition = _chara->getSceneNode()->getPosition();
    convertCoordinates(ghostSNPosition, 0.0);
    convertCoordinates(charaSNPosition, 0.0);

    ghostTargetPosition = _ghosts->at(i)->getTarget()->getData().getPosition();
    
    if(abs(ghostSNPosition.x - charaSNPosition.x) <= OMICRON){
      if(abs(ghostSNPosition.y - charaSNPosition.y) <= OMICRON){
        if(_ghosts->at(i)->getMode()!='W'){
          loseLife();
        }
        else{
          //el fantasma ha sido comido
          //reproducir efecto de sonido
          GameManager::getSingletonPtr()->_soundEffect = GameManager::getSingletonPtr()->_pSoundFXManager->load("s_eat.wav");
          GameManager::getSingletonPtr()->_soundEffect->play();

          _splay->actualizarPuntos(_ghosts->at(i)->getPoints());
          Graph *myGraph = _scene->getGraph();
          int verticesf[4] = {13,27,28,29};
          _ghosts->at(i)->setGraphVertex(myGraph->getVertexes().at(verticesf[i]));
          _ghosts->at(i)->setTarget(myGraph->getVertexes().at(verticesf[i]));
          auxPosition = _ghosts->at(i)->getGraphVertex()->getData().getPosition();
          convertCoordinates(auxPosition, 0.0);
          _ghosts->at(i)->getSceneNode()->setPosition(auxPosition);
        }    
      }
    }
    

    if(std::abs(ghostSNPosition.x - ghostTargetPosition.x) <= EPSILON){
      if(std::abs(ghostSNPosition.y - ghostTargetPosition.y) <= EPSILON){
        Ogre::Vector3 vecPos = _ghosts->at(i)->getTarget()->getData().getPosition();
        convertCoordinates(vecPos,0.0);
        _ghosts->at(i)->getSceneNode()->setPosition(vecPos);
        _ghosts->at(i)->setGraphVertex(_ghosts->at(i)->getTarget());
        _ghosts->at(i)->setDirection(_movementController->getGhostNextDirection(_ghosts->at(i),_chara)); 
        if(_movementController->isGhostValidDirection(_ghosts->at(i))){
          _ghosts->at(i)->setTarget(_movementController->getVertexByDirection(_ghosts->at(i)));
        }  
      }
    }
        if(_ghosts->at(i)->getDirection() == 'R'){
          _ghosts->at(i)->getSceneNode()->setPosition(_ghosts->at(i)->getSceneNode()->getPosition() + Ogre::Vector3(-_ghosts->at(i)->getSpeed(),0,0));
        }
        else if(_ghosts->at(i)->getDirection() == 'D'){
          _ghosts->at(i)->getSceneNode()->setPosition(_ghosts->at(i)->getSceneNode()->getPosition() + Ogre::Vector3(0,0,-_ghosts->at(i)->getSpeed()));
        }
        else if(_ghosts->at(i)->getDirection() == 'L'){
          _ghosts->at(i)->getSceneNode()->setPosition(_ghosts->at(i)->getSceneNode()->getPosition() + Ogre::Vector3(_ghosts->at(i)->getSpeed(),0,0));
        }
        else if(_ghosts->at(i)->getDirection() == 'U'){
          _ghosts->at(i)->getSceneNode()->setPosition(_ghosts->at(i)->getSceneNode()->getPosition() + Ogre::Vector3(0,0,_ghosts->at(i)->getSpeed()));
        }
  }

  
}

void PlayState::convertCoordinates(Ogre::Vector3 &vect, double offset){
  double aux = vect.y;
  vect.y = vect.z + offset;
  vect.z = aux;
}

void PlayState::changeCharaFacing(){
  //Ogre::SceneNode *sceneNode = chara->getSceneNode();
  char direction = _chara->getDirection();
  switch(direction){
    case 'R':
      _chara ->getSceneNode()->setOrientation(1,0,0,0);
      break;
    case 'L':
      _chara ->getSceneNode()->setOrientation(0,0,1,0);
      break;
    case 'U':
      _chara ->getSceneNode()->setOrientation(1,0,1,0);
      break;
    case 'D':
      _chara ->getSceneNode()->setOrientation(1,0,-1,0);
      break;
  }
}

void PlayState::loseLife(){
  //le bajo la vida al personaje
  Graph *myGraph = _scene->getGraph();
  Ogre::Vector3 positionAux;
  if(!_caught){
    if(_chara->getHealth() > 0){
      _chara->setHealth(_chara->getHealth()-1);  
    }
  
    switch(_chara->getHealth()){
      case 2:
        _splay->perderlive(0);  //le quito la vida de la GUI
        break;
      case 1:
        _splay->perderlive(1);  //le quito la vida de la GUI
        break;
      case 0:
        _splay->perderlive(2);  //le quito la vida de la GUI
        break;
    }
  
    if(_chara->getHealth() > 0){
      //Devuelvo al personaje a su posicion inicial
      _chara->setGraphVertex(myGraph->getVertexes().at(57));
      _chara->setTarget(myGraph->getVertexes().at(57));
      positionAux = _chara->getGraphVertex()->getData().getPosition();
      convertCoordinates(positionAux,0.0);
      _chara->getSceneNode()->setPosition(positionAux);
      //Devuelvo los fantasmas a sus posiciones iniciales
      int verticesf[4] = {13,27,28,29};
      unsigned int i = 0;
      for(i=0;i<_ghosts->size();i++){
        _ghosts->at(i)->setGraphVertex(myGraph->getVertexes().at(verticesf[i]));
        _ghosts->at(i)->setTarget(myGraph->getVertexes().at(verticesf[i]));
        positionAux = _ghosts->at(i)->getGraphVertex()->getData().getPosition();
        convertCoordinates(positionAux,0.0);
        _ghosts->at(i)->getSceneNode()->setPosition(positionAux);
      }
      _caught = false;
    }
    else{
      //GAMEOVER
      _chara->getSceneNode()->setVisible(false);
      GameManager::getSingletonPtr()->_mainTrack->stop();
      GameManager::getSingletonPtr()->_soundEffect = GameManager::getSingletonPtr()->_pSoundFXManager->load("s_gameOver.wav");
      GameManager::getSingletonPtr()->_soundEffect->play();
      _finalgame = true;

    }  
  }
}