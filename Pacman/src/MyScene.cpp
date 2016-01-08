
#include "MyScene.h"

MyScene::MyScene(Ogre::SceneManager* sceneManager, CEGUI::Window* sheet){
	_sheet = sheet;
	_sceneManager = sceneManager;
}

MyScene::~MyScene(){}

void MyScene::crearMenuInicio(){

  Ogre::Entity* ent1 = _sceneManager->createEntity("Pacman", "Pacman.mesh");
  Ogre::SceneNode* node1 = _sceneManager->createSceneNode("Pacman");
  node1->attachObject(ent1);
  node1->setScale(3.5,3.5,3.5);
  node1->setPosition(1,9.5,5);
  node1->yaw(Ogre::Degree(-80));
  node1->roll(Ogre::Degree(25));
  // roll --> z
  // pitch --> x
  // yaw --> y
  _sceneManager->getRootSceneNode()->addChild(node1);

  Ogre::Entity* entf = _sceneManager->createEntity("FantasmaP", "Fantasma.mesh");
  Ogre::SceneNode* nodef = _sceneManager->createSceneNode("FantasmaP");
  nodef->attachObject(entf);
  node1->addChild(nodef);
  nodef->yaw(Ogre::Degree(158));
  nodef->roll(Ogre::Degree(-5));
  nodef->pitch(Ogre::Degree(-1));
  nodef->setPosition(-3,0.2,-2);

  Ogre::Entity* entfr = _sceneManager->createEntity("FantasmaR", "FantasmaR.mesh");
  Ogre::SceneNode* nodefr = _sceneManager->createSceneNode("FantasmaR");
  nodefr->attachObject(entfr);
  node1->addChild(nodefr);
  nodefr->yaw(Ogre::Degree(210));
  nodefr->roll(Ogre::Degree(-5));
  nodefr->pitch(Ogre::Degree(-1));
  
  nodefr->setPosition(-3,0.2,3);

  Ogre::Plane plane1(Ogre::Vector3::UNIT_Y, 0);
  Ogre::MeshManager::getSingleton().createPlane("plane1",
  Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane1,
  1024,768,1,1,true,1,20,20,Ogre::Vector3::UNIT_Z);

  Ogre::SceneNode* node2 = _sceneManager->createSceneNode("ground");
  Ogre::Entity* groundEnt = _sceneManager->createEntity("planeEnt", "plane1");
  groundEnt->setMaterialName("Ground");
  node2->attachObject(groundEnt);

  _sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);	
  Ogre::Light* light = _sceneManager->createLight("Light1");
  light->setType(Ogre::Light::LT_DIRECTIONAL);
  light->setDirection(Ogre::Vector3(1,-1,0));
  node2->attachObject(light);

  _sceneManager->getRootSceneNode()->addChild(node2);
  crearMenuInicioCEGUI();
}
void MyScene::crearMenuInicioCEGUI(){
  CEGUI::Window* vent = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("MenuInicialPacman.layout");
  CEGUI::Window* ventinicio = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","VI");
  CEGUI::Window* ventcreditos = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("creditos.layout");
  
  vent->setPosition(CEGUI::UVector2(CEGUI::UDim(0.21f,0),CEGUI::UDim(0.30f,0)));
  ventcreditos->setPosition(CEGUI::UVector2(CEGUI::UDim(0.14f,0),CEGUI::UDim(0.30f,0)));
  ventinicio -> addChild(vent);
  _sheet->addChild(ventinicio); 
  _sheet->addChild(ventcreditos); 

  CEGUI::Window* imglogo = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage","VentImagen");
  CEGUI::ImageManager::getSingleton().addFromImageFile("ImagenLOGO","pacmanname.png");
  imglogo -> setProperty("Image","ImagenLOGO");
  imglogo -> setProperty("BackgroundEnabled","False");
  imglogo -> setProperty("FrameEnabled","False");
  imglogo -> setSize(CEGUI::USize(CEGUI::UDim(0.36f,0),CEGUI::UDim(0.36f,0)));  
  imglogo -> setPosition(CEGUI::UVector2(CEGUI::UDim(0.12f,0),CEGUI::UDim(0.53f,0)));
  ventinicio -> addChild(imglogo);
  //ventinicio -> setVisible(false);
  ventcreditos -> setVisible(false);
}
void MyScene::creditos(){
  CEGUI::Window* vent = _sheet-> getChild("VI");
  CEGUI::Window* ventinicio = vent-> getChild("MenuInicialPacman");
  ventinicio -> setVisible(false);
  CEGUI::Window* ventcreditos = _sheet-> getChild("Creditos");
  ventcreditos -> setVisible(true);
}
void MyScene::retroceder(){
  CEGUI::Window* vent = _sheet-> getChild("VI");
  CEGUI::Window* ventinicio = vent-> getChild("MenuInicialPacman");
  CEGUI::Window* ventcreditos = _sheet-> getChild("Creditos");
  if (ventcreditos-> isVisible()){
    ventcreditos->setVisible(false); 
    ventinicio->setVisible(true);
  } 
}
bool MyScene::limpiarpantallaCEGUI(){
  bool dev = false;
  CEGUI::Window* vent = _sheet-> getChild("VI");
  CEGUI::Window* ventinicio = vent-> getChild("MenuInicialPacman");
  if(ventinicio-> isVisible()){
    vent->setVisible(false);
    dev = true;
  }
  return dev;
}