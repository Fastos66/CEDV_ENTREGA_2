
#include "MyScene.h"
#include "IntroState.h"
#include "ControlState.h"

MyScene::MyScene(Ogre::SceneManager* sceneManager, CEGUI::Window* sheet){
	_sheet = sheet;
	_sceneManager = sceneManager;
}
MyScene::MyScene(Ogre::SceneManager* sceneManager){
  _sheet = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
  _sceneManager = sceneManager;
}
MyScene::~MyScene(){
  
}

void MyScene::crearMenuInicio(){
  Ogre::Entity* mapae = _sceneManager->createEntity("MapaR", "ParedesM.mesh");
  Ogre::SceneNode* nodemapa = _sceneManager->createSceneNode("MapaM");
  nodemapa->attachObject(mapae);
  nodemapa-> setPosition(0,1,0);
  _sceneManager->getRootSceneNode()->addChild(nodemapa);

   Ogre::SceneNode* nodeinv = _sceneManager->createSceneNode("nodeinv");
  _sceneManager->getRootSceneNode()->addChild(nodeinv);

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

  Ogre::Entity* entf = _sceneManager->createEntity("FantasmaP", "FantasmaJGuisante.mesh");
  Ogre::SceneNode* nodef = _sceneManager->createSceneNode("FantasmaP");
  nodef->attachObject(entf);
  node1->addChild(nodef);
  //nodef->yaw(Ogre::Degree(158));
  nodef->yaw(Ogre::Degree(-10));
  nodef->roll(Ogre::Degree(-7));
  nodef-> setScale(1.5,1.5,1.5);
  nodef->pitch(Ogre::Degree(-1));
  nodef->setPosition(-3,-1,-2);

  Ogre::Entity* entfr = _sceneManager->createEntity("FantasmaR", "FantasmaJCebolla.mesh");
  Ogre::SceneNode* nodefr = _sceneManager->createSceneNode("FantasmaR");
  nodefr->attachObject(entfr);
  node1->addChild(nodefr);
  //nodefr->yaw(Ogre::Degree(210));
  nodefr->yaw(Ogre::Degree(120));
  nodefr->roll(Ogre::Degree(-5));
  nodefr-> setScale(1.4,1.4,1.4);
  //nodefr->pitch(Ogre::Degree(-1));
  
  nodefr->setPosition(-4,-1,3);

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
  CEGUI::Window* ventranking = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("rankingl.layout");
  
  //BOTONES
  CEGUI::Window* playButton = vent->getChild("PlayButton");
  playButton->subscribeEvent(CEGUI::PushButton::EventClicked,
          CEGUI::Event::Subscriber(&IntroState::playButtonC, 
                IntroState::getSingletonPtr())); 

  CEGUI::Window* creditsButton = vent->getChild("CreditsButton");
  creditsButton->subscribeEvent(CEGUI::PushButton::EventClicked,
          CEGUI::Event::Subscriber(&IntroState::creditsButtonC, 
                IntroState::getSingletonPtr())); 

  CEGUI::Window* rankingButton = vent->getChild("RankingButton");
  rankingButton->subscribeEvent(CEGUI::PushButton::EventClicked,
          CEGUI::Event::Subscriber(&IntroState::rankingButtonC, 
                IntroState::getSingletonPtr())); 

  CEGUI::Window* exitButton = vent->getChild("ExitButton");
  exitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
          CEGUI::Event::Subscriber(&IntroState::exitButtonC, 
                IntroState::getSingletonPtr())); 

  CEGUI::Window* atrasCButton = ventcreditos->getChild("AtrasCredits");
  atrasCButton->subscribeEvent(CEGUI::PushButton::EventClicked,
          CEGUI::Event::Subscriber(&IntroState::atrasCreditsButtonC, 
                IntroState::getSingletonPtr())); 

  CEGUI::Window* atrasRButton = ventranking->getChild("AtrasRanking");
  atrasRButton->subscribeEvent(CEGUI::PushButton::EventClicked,
          CEGUI::Event::Subscriber(&IntroState::atrasRankingButtonC, 
                IntroState::getSingletonPtr())); 

  vent->setPosition(CEGUI::UVector2(CEGUI::UDim(0.21f,0),CEGUI::UDim(0.30f,0)));
  ventcreditos->setPosition(CEGUI::UVector2(CEGUI::UDim(0.14f,0),CEGUI::UDim(0.30f,0)));
  ventranking->setPosition(CEGUI::UVector2(CEGUI::UDim(0.20f,0),CEGUI::UDim(0.01f,0)));
  
  ventinicio -> addChild(vent);
  ventinicio-> moveToFront(); //Mover al frente para que otras ventanas no interfieran.
  _sheet->addChild(ventinicio); 
  _sheet->addChild(ventcreditos); 
  _sheet-> addChild(ventranking);

  CEGUI::Window* imglogo = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage","VentImagen");
  CEGUI::ImageManager::getSingleton().addFromImageFile("ImagenLOGO","pacmanname.png");
  imglogo -> setProperty("Image","ImagenLOGO");
  imglogo -> setProperty("BackgroundEnabled","False");
  imglogo -> setProperty("FrameEnabled","False");
  imglogo -> setSize(CEGUI::USize(CEGUI::UDim(0.36f,0),CEGUI::UDim(0.36f,0)));  
  imglogo -> setPosition(CEGUI::UVector2(CEGUI::UDim(0.12f,0),CEGUI::UDim(0.53f,0)));
  ventinicio -> addChild(imglogo);

  CEGUI::Window* imgnameranking = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage","ImagenNameRanking");
  CEGUI::ImageManager::getSingleton().addFromImageFile("INameRanking","nameranking.png");
  imgnameranking -> setProperty("Image","INameRanking");
  imgnameranking -> setProperty("BackgroundEnabled","False");
  imgnameranking -> setProperty("FrameEnabled","False");
  imgnameranking -> setSize(CEGUI::USize(CEGUI::UDim(0.12f,0),CEGUI::UDim(0.09f,0)));  
  imgnameranking -> setPosition(CEGUI::UVector2(CEGUI::UDim(0.20f,0),CEGUI::UDim(0.13f,0)));
  ventranking -> addChild(imgnameranking);

  CEGUI::Window* imgpointranking = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage","ImagenPointRanking");
  CEGUI::ImageManager::getSingleton().addFromImageFile("IPointRanking","pointsranking.png");
  imgpointranking -> setProperty("Image","IPointRanking");
  imgpointranking -> setProperty("BackgroundEnabled","False");
  imgpointranking -> setProperty("FrameEnabled","False");
  imgpointranking -> setSize(CEGUI::USize(CEGUI::UDim(0.12f,0),CEGUI::UDim(0.09f,0)));  
  imgpointranking -> setPosition(CEGUI::UVector2(CEGUI::UDim(0.36f,0),CEGUI::UDim(0.13f,0)));
  ventranking -> addChild(imgpointranking);

  //ventinicio -> setVisible(false);
  ventcreditos -> setVisible(false);
  ventranking -> setVisible(false);
}
void MyScene::creditos(){
  CEGUI::Window* vent = _sheet-> getChild("VI");
  CEGUI::Window* ventinicio = vent-> getChild("MenuInicialPacman");
  ventinicio -> setVisible(false);
  CEGUI::Window* ventcreditos = _sheet-> getChild("Creditos");
  ventcreditos -> setVisible(true);
  ventcreditos -> moveToFront();
  CEGUI::Window* ventranking = _sheet-> getChild("RankingL");
  ventranking-> setVisible(false);
}

void MyScene::ranking(){
  CEGUI::Window* vent = _sheet-> getChild("VI");
  CEGUI::Window* ventinicio = vent-> getChild("MenuInicialPacman");
  ventinicio -> setVisible(false);
  CEGUI::Window* ventcreditos = _sheet-> getChild("Creditos");
  ventcreditos -> setVisible(false);
  CEGUI::Window* ventranking = _sheet-> getChild("RankingL");
  ventranking-> setVisible(true);
  ventranking-> moveToFront();
  
}
void MyScene::retroceder(){
  CEGUI::Window* vent = _sheet-> getChild("VI");
  CEGUI::Window* ventinicio = vent-> getChild("MenuInicialPacman");
  CEGUI::Window* ventcreditos = _sheet-> getChild("Creditos");
  CEGUI::Window* ventranking = _sheet-> getChild("RankingL");
  if (ventcreditos-> isVisible() || ventranking-> isVisible() ){
    ventcreditos->setVisible(false); 
    ventinicio->setVisible(true);
    ventranking-> setVisible(false);
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

void MyScene::ActRanking(){
  Ranking* ran = new Ranking();
  ran -> leerPlayeryPuntos();
  ran -> acturanking();
}

void MyScene::controles(){
  Ogre::SceneNode* node1 = _sceneManager->getSceneNode("Pacman");
  node1-> setVisible(true);
  _sceneManager->getSceneNode("FantasmaR")->setVisible(false);
  _sceneManager->getSceneNode("MapaM")->setVisible(false);
  node1-> setPosition(8,12,12);
  node1-> roll(Ogre::Degree(12));
  node1-> yaw(Ogre::Degree(-12));
  node1-> setScale(5,5,5); 

  CEGUI::Window* ventcontroles = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("controles.layout");
  
  CEGUI::Window* goButton = ventcontroles->getChild("GoButton");
  goButton->subscribeEvent(CEGUI::PushButton::EventClicked,
          CEGUI::Event::Subscriber(&ControlState::goButtonC, 
                ControlState::getSingletonPtr())); 

  _sheet->addChild(ventcontroles); 

  CEGUI::Window* imgcontroles = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage","ImagenControles");
  CEGUI::ImageManager::getSingleton().addFromImageFile("INameControles","controlesName.png");
  imgcontroles -> setProperty("Image","INameControles");
  imgcontroles -> setProperty("BackgroundEnabled","False");
  imgcontroles -> setProperty("FrameEnabled","False");
  imgcontroles -> setSize(CEGUI::USize(CEGUI::UDim(0.20f,0),CEGUI::UDim(0.14f,0)));  
  imgcontroles -> setPosition(CEGUI::UVector2(CEGUI::UDim(0.05f,0),CEGUI::UDim(0.02f,0)));
  ventcontroles -> addChild(imgcontroles);

  CEGUI::Window* imgcontrolesT = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage","ImagenControlesT");
  CEGUI::ImageManager::getSingleton().addFromImageFile("IControlesT","controlesTeclado.png");
  imgcontrolesT -> setProperty("Image","IControlesT");
  imgcontrolesT -> setProperty("BackgroundEnabled","False");
  imgcontrolesT -> setProperty("FrameEnabled","False");
  imgcontrolesT -> setSize(CEGUI::USize(CEGUI::UDim(0.15f,0),CEGUI::UDim(0.15f,0)));  
  imgcontrolesT -> setPosition(CEGUI::UVector2(CEGUI::UDim(0.16f,0),CEGUI::UDim(0.13f,0)));
  ventcontroles -> addChild(imgcontrolesT);

  CEGUI::Window* imgpuntos = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage","ImagenPuntos");
  CEGUI::ImageManager::getSingleton().addFromImageFile("INamePuntos","puntosName.png");
  imgpuntos -> setProperty("Image","INamePuntos");
  imgpuntos -> setProperty("BackgroundEnabled","False");
  imgpuntos -> setProperty("FrameEnabled","False");
  imgpuntos -> setSize(CEGUI::USize(CEGUI::UDim(0.20f,0),CEGUI::UDim(0.14f,0)));  
  imgpuntos -> setPosition(CEGUI::UVector2(CEGUI::UDim(0.05f,0),CEGUI::UDim(0.30f,0)));
  ventcontroles -> addChild(imgpuntos);

  CEGUI::Window* imgpuntosPJ = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage","ImagenPuntosPJ");
  CEGUI::ImageManager::getSingleton().addFromImageFile("INamePuntosPJ","puntosControl.png");
  imgpuntosPJ -> setProperty("Image","INamePuntosPJ");
  imgpuntosPJ -> setProperty("BackgroundEnabled","False");
  imgpuntosPJ -> setProperty("FrameEnabled","False");
  imgpuntosPJ -> setSize(CEGUI::USize(CEGUI::UDim(0.40f,0),CEGUI::UDim(0.40f,0)));  
  imgpuntosPJ -> setPosition(CEGUI::UVector2(CEGUI::UDim(0.16f,0),CEGUI::UDim(0.40f,0)));
  ventcontroles -> addChild(imgpuntosPJ);

}

bool MyScene::limpiarpantallaCEGUIControles(){
  bool dev = false;
  CEGUI::Window* ventcontroles = _sheet-> getChild("ControlesLayout");
  if(ventcontroles->isVisible()){
    ventcontroles->setVisible(false);
    dev=true;
  }
  return dev;
}

