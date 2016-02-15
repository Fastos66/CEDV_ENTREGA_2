#include "FinalGameState.h"
#include "Ranking.h"
#include "IntroState.h"
#include <OgreEntity.h>

template<> FinalGameState* Ogre::Singleton<FinalGameState>::msSingleton = 0;

void
FinalGameState::enter ()
{
  _root = Ogre::Root::getSingletonPtr();

  // Se recupera el gestor de escena y la cámara.
  _sceneMgr = _root->getSceneManager("SceneManager");
  _camera = _sceneMgr->getCamera("IntroCamera");
  _viewport = _root->getAutoCreatedWindow()->getViewport(0);
  // Nuevo background colour.
  _viewport->setBackgroundColour(Ogre::ColourValue(0.0, 1.0, 0.0));
  CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setVisible(true);
  _scplay = new MyScenePlay(_sceneMgr,_camera);
  _scplay -> pedirelnombre_actualizar_ranking();
  _exitGame = false;
  
}

void
FinalGameState::exit ()
{
  _sceneMgr->destroyCamera("IntroCamera");
  CEGUI::Window* sheet = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
  Ogre::Node *node;
  Ogre::Entity *entity;
  Ogre::Node::ChildNodeIterator iter = _sceneMgr->getRootSceneNode()->getChildIterator();
  while (iter.hasMoreElements()){
      node = iter.getNext();
      //cout << node-> getName() << endl; 
      //entity = static_cast<Ogre::Entity*>(static_cast<Ogre::SceneNode*>(node)->getAttachedObject());
      //static_cast<Ogre::SceneNode*>(node)->removeAndDestroyAllChildren();
      DestroyAllAttachedMovableObjects(static_cast<Ogre::SceneNode*>(node));
      static_cast<Ogre::SceneNode*>(node)->removeAndDestroyAllChildren();
      //delete entity;
      _sceneMgr->getRootSceneNode()->removeAndDestroyChild(node->getName());
  }
  
  static_cast<Ogre::SceneNode*>(_sceneMgr->getRootSceneNode())->removeAndDestroyAllChildren();

  //sheet->destroyChild();

  //CEGUI::Window* sheet = CEGUI::WindowManager::getSingleton()->;
  actualizarranking();
  LimpiarTodo();
  _root->getAutoCreatedWindow()->removeAllViewports();

}

void
FinalGameState::pause ()
{
}

void
FinalGameState::resume ()
{
}

bool
FinalGameState::frameStarted
(const Ogre::FrameEvent& evt)
{
  
  return true;
}

bool
FinalGameState::frameEnded
(const Ogre::FrameEvent& evt)
{
  if (_exitGame)
    return false;
  
  return true;
}

void
FinalGameState::keyPressed
(const OIS::KeyEvent &e) {
  CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(static_cast<CEGUI::Key::Scan>(e.key));
  CEGUI::System::getSingleton().getDefaultGUIContext().injectChar(e.text);
  // Tecla p --> Estado anterior.
  if (e.key == OIS::KC_ESCAPE) {
    _exitGame = true;
  }
  if (e.key == OIS::KC_X) {
    if(actualizarranking()){
        _exitGame = true;
    }    
  }
   /*if (e.key == OIS::KC_C) {
      
     changeState(IntroState::getSingletonPtr());
  }*/
}

void
FinalGameState::keyReleased
(const OIS::KeyEvent &e)
{
  CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(static_cast<CEGUI::Key::Scan>(e.key));
}

void
FinalGameState::mouseMoved
(const OIS::MouseEvent &e)
{
  CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(e.state.X.rel, e.state.Y.rel);
}

void
FinalGameState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
  CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(convertMouseButton(id));
}

void
FinalGameState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
  CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(convertMouseButton(id));   
}

CEGUI::MouseButton FinalGameState::convertMouseButton(OIS::MouseButtonID id)
{
  CEGUI::MouseButton ceguiId;
  switch(id)
    {
    case OIS::MB_Left:
      ceguiId = CEGUI::LeftButton;
      break;
    case OIS::MB_Right:
      ceguiId = CEGUI::RightButton;
      break;
    case OIS::MB_Middle:
      ceguiId = CEGUI::MiddleButton;
      break;
    default:
      ceguiId = CEGUI::LeftButton;
    }
  return ceguiId;
}

bool FinalGameState::exitButtonC(const CEGUI::EventArgs& e){
    if (actualizarranking()){
      _exitGame = true;
    }
    return true; 
}

FinalGameState*
FinalGameState::getSingletonPtr ()
{
return msSingleton;
}

FinalGameState&
FinalGameState::getSingleton ()
{ 
  assert(msSingleton);
  return *msSingleton;
}

bool FinalGameState::actualizarranking(){
    Ranking* ran = new Ranking();
    string puntosplayer = _scplay->getpuntosjugador();
    string nameplayer = _scplay-> getnombrejugador();
    cout << nameplayer << ":" << puntosplayer << endl;
    ran -> setrankingtxt(nameplayer,puntosplayer);
    return true;
}

void FinalGameState::DestroyAllAttachedMovableObjects(Ogre::SceneNode* i_pSceneNode )
{
       // if ( !i_pSceneNode )
       // {
       //    ASSERT( false );
       //    return;
       // }

       // Destroy all the attached objects
       Ogre::SceneNode::ObjectIterator itObject = i_pSceneNode->getAttachedObjectIterator();

       while ( itObject.hasMoreElements() )
       {
          Ogre::MovableObject* pObject = static_cast<Ogre::MovableObject*>(itObject.getNext());
          i_pSceneNode->getCreator()->destroyMovableObject( pObject );
       }

       // Recurse to child SceneNodes
       Ogre::SceneNode::ChildNodeIterator itChild = i_pSceneNode->getChildIterator();

       while ( itChild.hasMoreElements() )
       {
          Ogre::SceneNode* pChildNode = static_cast<Ogre::SceneNode*>(itChild.getNext());
          DestroyAllAttachedMovableObjects( pChildNode );
       }
}
void FinalGameState::LimpiarTodo(){
  cout << "A BORRAR TODO"<< endl;
  CEGUI::Renderer * renderer = IntroState::getSingletonPtr()->getRenderer(); 
  //renderer->destroyAllTextures();
  renderer-> destroyTexture("ImagenLOGO");
  renderer-> destroyTexture("INameRanking");
  renderer-> destroyTexture("IPointRanking");
  
  renderer->destroyTexture("INameControles");
  renderer->destroyTexture("IControlesT");
  renderer->destroyTexture("INamePuntos");
  renderer->destroyTexture("INamePuntosPJ");
  
  LimpiarPlayState();
  renderer->destroyTexture("ImagenLivesPuntos");

  LimpiarPausaState();

  LimpiarFinalState();
  renderer->destroyTexture("ImagenLOGOTop");
  renderer->destroyTexture("ImagenOR");
  
  cout << "TODO BORRADO"<< endl;
}

void FinalGameState::LimpiarPlayState(){
  _scplay -> CEGUIinvPlay();
  _scplay -> limpiarCeguiPlay();
}

void FinalGameState::LimpiarFinalState(){
  _scplay -> CEGUIinvFinal();
  _scplay -> limpiarCeguiFinal();
}

void FinalGameState::LimpiarPausaState(){
  _scplay -> CEGUIinvPausa();
  _scplay -> limpiarCeguiPausa();
}

bool FinalGameState::menuPrincipalButtonC(const CEGUI::EventArgs& e){
    changeState(IntroState::getSingletonPtr());
    return true; 
}