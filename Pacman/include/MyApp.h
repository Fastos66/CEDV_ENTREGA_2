#ifndef MYAPP_H
#define MYAPP_H

#include <Ogre.h>
#include "MyFrameListener.h"
#include <iostream>
#include <sstream>
#include <string> 
#include <CEGUI.h>
#include <RendererModules/Ogre/Renderer.h>
using namespace std;

class MyApp {
  
private:
  Ogre::SceneManager* _sceneManager;
  Ogre::Root* _root;
  MyFrameListener* _framelistener;
  CEGUI::OgreRenderer* renderer; 	
public:
  MyApp();
  ~MyApp();  
  int start();
  void loadResources();
  void createScene();
  void createGUI();	
};

#endif