#ifndef IntroState_H
#define IntroState_H

#include <Ogre.h>
#include <OIS/OIS.h>

#include "GameState.h"
#include "MyScene.h"


class IntroState : public Ogre::Singleton<IntroState>, public GameState
{
 public:
  IntroState();

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
  static IntroState& getSingleton ();
  static IntroState* getSingletonPtr ();
  CEGUI::MouseButton convertMouseButton(OIS::MouseButtonID id);
  
  bool playButtonC(const CEGUI::EventArgs& e);
  bool creditsButtonC(const CEGUI::EventArgs& e);
  bool rankingButtonC(const CEGUI::EventArgs& e);
  bool exitButtonC(const CEGUI::EventArgs& e);
  bool atrasCreditsButtonC(const CEGUI::EventArgs& e);
  bool atrasRankingButtonC(const CEGUI::EventArgs& e);
  CEGUI::Renderer * getRenderer();



 protected:
  
  Ogre::Root* _root;
  Ogre::SceneManager* _sceneMgr;
  Ogre::Viewport* _viewport;
  Ogre::Camera* _camera;
  CEGUI::OgreRenderer* renderer;
  bool _exitGame;
  void loadCEGUI();
  MyScene* _scena;
  CEGUI::Window* _sheet;
  int _timesCreated;

 private:
  Ogre::AnimationState *_animState;
  bool _lanzaranimacion;

};

#endif
