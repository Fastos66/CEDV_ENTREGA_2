//ControlState.h
#ifndef ControlState_H
#define ControlState_H

#include <Ogre.h>
#include <OIS/OIS.h>
#include "MyScene.h"
#include "GameState.h"

class ControlState : public Ogre::Singleton<ControlState>, public GameState
{
 public:
  ControlState () { }

  void enter ();
  void exit ();
  void pause ();
  void resume ();

  void keyPressed (const OIS::KeyEvent &e);
  void keyReleased (const OIS::KeyEvent &e);

  void mouseMoved (const OIS::MouseEvent &e);
  void mousePressed (const OIS::MouseEvent &e, OIS::MouseButtonID id);
  void mouseReleased (const OIS::MouseEvent &e, OIS::MouseButtonID id);

  bool frameStarted (const Ogre::FrameEvent& evt);
  bool frameEnded (const Ogre::FrameEvent& evt);

  // Heredados de Ogre::Singleton.
  static ControlState& getSingleton ();
  static ControlState* getSingletonPtr ();

 protected:
  Ogre::Root* _root;
  Ogre::SceneManager* _sceneMgr;
  Ogre::Viewport* _viewport;
  Ogre::Camera* _camera;
  bool _exitGame;
  bool _lanzaranimacion;
  MyScene* _scena;
  Ogre::AnimationState *_animState;
};

#endif
