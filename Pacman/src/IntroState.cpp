#include "IntroState.h"
#include "ControlState.h"
#include "MyScene.h"
#include "Ranking.h"
template<> IntroState* Ogre::Singleton<IntroState>::msSingleton = 0;

void
IntroState::enter ()
{
  _root = Ogre::Root::getSingletonPtr();

  _sceneMgr = _root->createSceneManager(Ogre::ST_GENERIC, "SceneManager");
  _sceneMgr -> setAmbientLight(Ogre::ColourValue(1,1,1));
  _camera = _sceneMgr->createCamera("IntroCamera");
  _camera->setPosition(Ogre::Vector3(5,20,22));
  _camera->lookAt(Ogre::Vector3(0,0,0));
  _camera->setNearClipDistance(5);
  _camera->setFarClipDistance(10000);
  _viewport = _root->getAutoCreatedWindow()->addViewport(_camera);
  _viewport->setBackgroundColour(Ogre::ColourValue(0.0,0.0,0.0));
  double width = _viewport->getActualWidth();
  double height = _viewport->getActualHeight();
  _camera->setAspectRatio(width / height);
  printf("Estado:Intro\n");
  
  loadCEGUI();
 
  _scena = new MyScene(_sceneMgr,_sheet);
  _scena -> crearMenuInicio();
  _scena -> ActRanking();
  _animState = NULL;
  _lanzaranimacion = true;
  _exitGame = false;

  GameManager::getSingletonPtr()->_mainTrack = GameManager::getSingletonPtr()->_pTrackManager->load("s_song.mp3");
  GameManager::getSingletonPtr()->_soundEffect = GameManager::getSingletonPtr()->_pSoundFXManager->load("s_gameOver.wav");
  GameManager::getSingletonPtr()->_mainTrack->play();

}
void
IntroState::exit()
{
  //_sceneMgr->clearScene();
  _sceneMgr->getSceneNode("Pacman")-> setVisible(false);
  _root->getAutoCreatedWindow()->removeAllViewports();
}

void
IntroState::pause ()
{
}

void
IntroState::resume ()
{
}

bool
IntroState::frameStarted
(const Ogre::FrameEvent& evt) 
{
  Ogre::Real deltaT = evt.timeSinceLastFrame;
  if (_lanzaranimacion){
    _animState = _sceneMgr->getEntity("Pacman")->getAnimationState("VerMenu");
    _animState->setEnabled(true);
    _animState->setLoop(true);
    _animState->setTimePosition(0.0);
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
IntroState::frameEnded
(const Ogre::FrameEvent& evt)
{
  if (_exitGame)
    return false;
  
  return true;
}

void
IntroState::keyPressed
(const OIS::KeyEvent &e)
{
  
  if (e.key == OIS::KC_P) {
    if (_scena->limpiarpantallaCEGUI()){
      changeState(ControlState::getSingletonPtr()); 
    }
  }
  if (e.key == OIS::KC_C) {
    _scena-> creditos();
  }
  if (e.key == OIS::KC_A) {
    _scena-> retroceder();
  }
  if (e.key == OIS::KC_R) {
    _scena-> ranking();
  }
}

void
IntroState::keyReleased
(const OIS::KeyEvent &e )
{
  if (e.key == OIS::KC_ESCAPE) {
    _exitGame = true;
  }
  if (e.key == OIS::KC_X) {
    _exitGame = true;
  }
}

void
IntroState::mouseMoved
(const OIS::MouseEvent &e)
{
  CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(e.state.X.rel, e.state.Y.rel);  
}

void
IntroState::mousePressed
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
  CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(convertMouseButton(id)); 
}

void
IntroState::mouseReleased
(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
  CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(convertMouseButton(id));
}

CEGUI::MouseButton IntroState::convertMouseButton(OIS::MouseButtonID id)
{
  CEGUI::MouseButton ceguiId;
  switch(id)
    {
    case OIS::MB_Left:
      ceguiId = CEGUI::LeftButton;
      break;
    case OIS::MB_Right:
      ceguiId = CEGUI::RightButton;
      break;
    case OIS::MB_Middle:
      ceguiId = CEGUI::MiddleButton;
      break;
    default:
      ceguiId = CEGUI::LeftButton;
    }
  return ceguiId;
}

bool IntroState::playButtonC(const CEGUI::EventArgs& e){
    if (_scena->limpiarpantallaCEGUI()){
      changeState(ControlState::getSingletonPtr()); 
    }
    return true; 
}
bool IntroState::creditsButtonC(const CEGUI::EventArgs& e){
    _scena-> creditos();
    return true; 
}
bool IntroState::rankingButtonC(const CEGUI::EventArgs& e){
    _scena-> ranking();
    return true; 
}
bool IntroState::exitButtonC(const CEGUI::EventArgs& e){
    _exitGame = true;
    return true; 
}
bool IntroState::atrasCreditsButtonC(const CEGUI::EventArgs& e){
    _scena-> retroceder();
    return true; 
}
bool IntroState::atrasRankingButtonC(const CEGUI::EventArgs& e){
    _scena-> retroceder();
    return true; 
}

IntroState*
IntroState::getSingletonPtr ()
{
return msSingleton;
}

IntroState&
IntroState::getSingleton ()
{ 
  assert(msSingleton);
  return *msSingleton;
}

void IntroState::loadCEGUI(){

  //CEGUI
  renderer = &CEGUI::OgreRenderer::bootstrapSystem();
  CEGUI::Scheme::setDefaultResourceGroup("Schemes");
  CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
  CEGUI::Font::setDefaultResourceGroup("Fonts");
  CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
  CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
  //Para los botones
  CEGUI::SchemeManager::getSingleton().createFromFile("VanillaSkin.scheme");
  //Para el Raton
  CEGUI::SchemeManager::getSingleton().createFromFile("OgreTray.scheme");
  //Para nada de momento
  CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
  
  CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont("DejaVuSans-12");
  CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("OgreTrayImages/MouseArrow");
  
  _sheet = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","Ex1/Sheet");
  CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(_sheet);
  
}