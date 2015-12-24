#ifndef MYFRAMELISTENER_H
#define MYFRAMELISTENER_H

#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI.h>
#include <RendererModules/Ogre/Renderer.h>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class MyFrameListener : public Ogre::FrameListener ,OIS::MouseListener {
private:
  OIS::InputManager* _inputManager;
  OIS::Keyboard* _keyboard;
  OIS::Mouse* _mouse;
  Ogre::Camera* _camera;
  Ogre::RenderWindow* _win;
  Ogre::SceneNode* _node;
  Ogre::SceneManager* _sceneManager;
  Ogre::AnimationState *_animState;

  bool mouseMoved(const OIS::MouseEvent& evt);
  bool mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
  bool mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
  CEGUI::MouseButton convertMouseButton(OIS::MouseButtonID id);
public:
  MyFrameListener(Ogre::RenderWindow* win, Ogre::Camera* cam, 
		  Ogre::SceneNode* node,
		  Ogre::SceneManager* sm);
  ~MyFrameListener();
  bool frameStarted(const Ogre::FrameEvent& evt);  
};

#endif