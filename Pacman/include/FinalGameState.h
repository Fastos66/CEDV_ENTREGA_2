#ifndef FinalGameState_H
#define FinalGameState_H

#include <Ogre.h>
#include <OIS/OIS.h>
#include "GameState.h"
#include "MyScenePlay.h"

class FinalGameState : public Ogre::Singleton<FinalGameState>, public GameState
{
 public:
  FinalGameState(){ }

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
  static FinalGameState& getSingleton ();
  static FinalGameState* getSingletonPtr ();

  CEGUI::MouseButton convertMouseButton(OIS::MouseButtonID id);
  bool menuPrincipalButtonC(const CEGUI::EventArgs& e);

  bool actualizarranking();

  void LimpiarPlayState();
  void LimpiarFinalState();
  void LimpiarPausaState();

  bool exitButtonC(const CEGUI::EventArgs& e);
  void DestroyAllAttachedMovableObjects(Ogre::SceneNode* i_pSceneNode );
  void LimpiarTodo();
 protected:

  Ogre::Root* _root;
  Ogre::SceneManager* _sceneMgr;
  Ogre::Viewport* _viewport;
  Ogre::Camera* _camera;
  MyScenePlay* _scplay;
  bool _exitGame;
};

#endif
