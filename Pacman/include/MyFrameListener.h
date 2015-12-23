#include <Ogre.h>
#include <OIS/OIS.h>


class MyFrameListener : public Ogre::FrameListener {
private:
  OIS::InputManager* _inputManager;
  OIS::Keyboard* _keyboard;
  Ogre::Camera* _camera;
  Ogre::RenderWindow* _win;
  Ogre::SceneNode* _node;
  Ogre::SceneManager* _sceneManager;
  Ogre::AnimationState *_animState;

public:
  MyFrameListener(Ogre::RenderWindow* win, Ogre::Camera* cam, 
		  Ogre::SceneNode* node,
		  Ogre::SceneManager* sm);
  ~MyFrameListener();
  bool frameStarted(const Ogre::FrameEvent& evt);  
};
