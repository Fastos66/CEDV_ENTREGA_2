#include "FinalGameState.h"
#include "Ranking.h"

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
  // Tecla p --> Estado anterior.
  if (e.key == OIS::KC_ESCAPE) {
    _exitGame = true;
  }
  if (e.key == OIS::KC_X) {
    if(actualizarranking()){
        _exitGame = true;
    }    
  }
}

void
FinalGameState::keyReleased
(const OIS::KeyEvent &e)
{
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