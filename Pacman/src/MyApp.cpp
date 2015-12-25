/*********************************************************************
 * Módulo 2. Curso de Experto en Desarrollo de Videojuegos
 * Autor: Carlos González Morcillo     Carlos.Gonzalez@uclm.es
 *
 * You can redistribute and/or modify this file under the terms of the
 * GNU General Public License ad published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * and later version. See <http://www.gnu.org/licenses/>.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.  
 *********************************************************************/

#include "MyApp.h" 

MyApp::MyApp() {
  _sceneManager = NULL;
  _framelistener = NULL;
}

MyApp::~MyApp() {
  delete _root;
  delete _framelistener;
}

int MyApp::start() {
  _root = new Ogre::Root();
  
  if(!_root->restoreConfig()) {
    _root->showConfigDialog();
    _root->saveConfig();
  }
  
  Ogre::RenderWindow* window = _root->initialise(true,"PacManian");
  _sceneManager = _root->createSceneManager(Ogre::ST_GENERIC);
  _sceneManager->setAmbientLight(Ogre::ColourValue(1,1,1));
  
  Ogre::Camera* cam = _sceneManager->createCamera("MainCamera");
  cam->setPosition(Ogre::Vector3(5,20,22));
  cam->lookAt(Ogre::Vector3(0,0,0));
  cam->setNearClipDistance(5);
  cam->setFarClipDistance(10000);
  
  Ogre::Viewport* viewport = window->addViewport(cam);
  viewport->setBackgroundColour(Ogre::ColourValue(0.0,0.0,0.0));
  double width = viewport->getActualWidth();
  double height = viewport->getActualHeight();
  cam->setAspectRatio(width / height);
  
  loadResources();
  createScene();
  createGUI();
 

  Ogre::SceneNode *node = _sceneManager->getSceneNode("Pacman");
  
  _framelistener = new MyFrameListener(window, cam, node, _sceneManager);
  _root->addFrameListener(_framelistener);
  
  _root->startRendering();
  return 0;
}

void MyApp::loadResources() {
  Ogre::ConfigFile cf;
  cf.load("resources.cfg");
  
  Ogre::ConfigFile::SectionIterator sI = cf.getSectionIterator();
  Ogre::String sectionstr, typestr, datastr;
  while (sI.hasMoreElements()) {
    sectionstr = sI.peekNextKey();
    Ogre::ConfigFile::SettingsMultiMap *settings = sI.getNext();
    Ogre::ConfigFile::SettingsMultiMap::iterator i;
    for (i = settings->begin(); i != settings->end(); ++i) {
      typestr = i->first;    datastr = i->second;
      Ogre::ResourceGroupManager::getSingleton().addResourceLocation
            (datastr, typestr, sectionstr);	
    }
  }
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void MyApp::createGUI(){
  renderer = &CEGUI::OgreRenderer::bootstrapSystem();
  CEGUI::Scheme::setDefaultResourceGroup("Schemes");
  CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
  CEGUI::Font::setDefaultResourceGroup("Fonts");
  CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
  CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
  //Para los botones
  //CEGUI::SchemeManager::getSingleton().createFromFile("VanillaSkin.scheme");
  //Para el Raton
  CEGUI::SchemeManager::getSingleton().createFromFile("OgreTray.scheme");
  //Para nada de momento
  CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
  
  CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont("DejaVuSans-12");
  CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("OgreTrayImages/MouseArrow");
  CEGUI::Window* sheet = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","Pacman/Sheet");
  CEGUI::Window* vent = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("MenuInicialPacman.layout");
  CEGUI::Window* ventinicio = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow");
  CEGUI::Window* ventcreditos = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("creditos.layout");
  
  vent->setPosition(CEGUI::UVector2(CEGUI::UDim(0.21f,0),CEGUI::UDim(0.30f,0)));
  ventcreditos->setPosition(CEGUI::UVector2(CEGUI::UDim(0.14f,0),CEGUI::UDim(0.30f,0)));
  ventinicio -> addChild(vent);
  sheet->addChild(ventinicio); 
  sheet->addChild(ventcreditos); 

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

  CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);

}

void MyApp::createScene() {

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
}
