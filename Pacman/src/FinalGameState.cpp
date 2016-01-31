#include "FinalGameState.h"

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
  if (e.key == OIS::KC_P) {
    popState();
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
}

void
FinalGameState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void
FinalGameState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
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
