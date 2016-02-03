//PlayState.h
#ifndef PlayState_H
#define PlayState_H

#include <Ogre.h>
#include <OIS/OIS.h>
#include "MyScenePlay.h"
#include "GameState.h"
#include "Importer.h"
#include "Scene.h"
#include "MovementController.h"
#include "Ghost.h"
#include "Character.h"

class PlayState : public Ogre::Singleton<PlayState>, public GameState
{
 public:
  PlayState () { }

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
  void pruebaCharacter();
  void creacionGhosts();
  MovementController * getMovementController();
  void setMovementController(MovementController* movementController);
  void convertCoordinates(Ogre::Vector3 &vector, double offset);

  // Heredados de Ogre::Singleton.
  static PlayState& getSingleton ();
  static PlayState* getSingletonPtr ();

 protected:
  Ogre::AnimationState *_animStatePacmanG;
  bool _lanzaranimationPG;
  Ogre::Root* _root;
  Ogre::SceneManager* _sceneMgr;
  Ogre::Viewport* _viewport;
  Ogre::Camera* _camera;
  MyScenePlay* _splay;
  bool _exitGame;
  Importer* _importer;
  Scene* _scene;
  MovementController* _movementController;
  Character* _chara;
  bool _inMovement;
  std::vector<Ghost>* _ghosts;
};

#endif
