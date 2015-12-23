#include <Ogre.h>
#include "MyFrameListener.h"
#include <iostream>
#include <sstream>
#include <string> 
#include <CEGUI.h>
using namespace std;

class MyApp {
  
private:
  Ogre::SceneManager* _sceneManager;
  Ogre::Root* _root;
  MyFrameListener* _framelistener;
 
public:
  MyApp();
  ~MyApp();  
  int start();
  void loadResources();
  void createScene();
 
};
