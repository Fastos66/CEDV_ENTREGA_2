//ControlState.cpp
#include "ControlState.h"
#include "PlayState.h"
#include "MyScene.h"
template<> ControlState* Ogre::Singleton<ControlState>::msSingleton = 0;

void
ControlState::enter ()
{
  _root = Ogre::Root::getSingletonPtr();

  // Se recupera el gestor de escena y la cámara.
  _sceneMgr = _root->getSceneManager("SceneManager");
  _camera = _sceneMgr->getCamera("IntroCamera");
  _viewport = _root->getAutoCreatedWindow()->addViewport(_camera);
  // Nuevo background colour.
  _viewport->setBackgroundColour(Ogre::ColourValue(0.0,0.0,0.0));
  printf("Estado:Control(PULSAR G PARA CAMBIAR A PLAYSTATE)\n");
  //Ogre::SceneNode* sn = _sceneMgr->getSceneNode("ground"); 
  _scena = new MyScene(_sceneMgr);
  _scena -> controles();
  _animState = NULL;
  _lanzaranimacion = true;
  _exitGame = false;
}

void
ControlState::exit ()
{
  //_sceneMgr->clearScene();
  _sceneMgr->getEntity("Pacman")->setVisible(false);
  _sceneMgr->getEntity("FantasmaP")->setVisible(false);	
  _root->getAutoCreatedWindow()->removeAllViewports();
}

void
ControlState::pause()
{
}

void
ControlState::resume()
{
  // Se restaura el background colour.
  _viewport->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 1.0));
}

bool
ControlState::frameStarted
(const Ogre::FrameEvent& evt)
{
  Ogre::Real deltaT = evt.timeSinceLastFrame;
  if (_lanzaranimacion){
    _animState = _sceneMgr->getEntity("Pacman")->getAnimationState("VerControles");
    _animState->setTimePosition(0.0);
    _animState->setEnabled(true);
    _animState->setLoop(true);
    _lanzaranimacion = false;
  }
  if (_animState != NULL) {
     if (_animState->hasEnded()) {
       _animState->setTimePosition(0.0);
       _animState->setEnabled(false);
     }
     else {
       _animState->addTime(deltaT);
     }
  }
  return true;

}

bool
ControlState::frameEnded
(const Ogre::FrameEvent& evt)
{
  if (_exitGame)
    return false;
  return true;
}

void
ControlState::keyPressed
(const OIS::KeyEvent &e)
{
  if (e.key == OIS::KC_G) {
    if(_scena->limpiarpantallaCEGUIControles()){
       changeState(PlayState::getSingletonPtr()); 
    }
  }
}
void
ControlState::keyReleased
(const OIS::KeyEvent &e)
{
  if (e.key == OIS::KC_ESCAPE) {
    _exitGame = true;
  }
}

void
ControlState::mouseMoved
(const OIS::MouseEvent &e)
{
}

void
ControlState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

void
ControlState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
}

ControlState*
ControlState::getSingletonPtr ()
{
return msSingleton;
}

ControlState&
ControlState::getSingleton ()
{ 
  assert(msSingleton);
  return *msSingleton;
}
