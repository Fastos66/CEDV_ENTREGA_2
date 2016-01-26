//MyScenePlay.cpp

#include "MyScenePlay.h"
MyScenePlay::MyScenePlay(Ogre::SceneManager* sceneManager, Scene* scene){
	_sceneManager=sceneManager;
	_sheet = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
  _scene = scene;
}

MyScenePlay::~MyScenePlay() {}

void MyScenePlay::cargarscenainicial(){
  
  Ogre::SceneNode* nodemapa =  _sceneManager->getSceneNode("MapaM");
  nodemapa-> setVisible(true);
  
}	

void MyScenePlay::pruebasGRAFO(){
    GraphVertex* pactual;
    int tamgrafo= _scene->getGraph()->getVertexes().size();
    //for (int i = 0; i < tamgrafo; ++i){
    pactual = _scene->getGraph()->getVertex(1);
    cout << "1Vertex " << pactual->getData().getPosition()  << endl;

    Ogre::Entity* ebola = _sceneManager->createEntity("Bolita", "BolaComer.mesh");
    Ogre::SceneNode* nodebola = _sceneManager->createSceneNode("Bolita");
    nodebola->attachObject(ebola);
    _sceneManager->getRootSceneNode()->addChild(nodebola);
    nodebola-> setPosition(pactual->getData().getPosition());
    //}

}

void MyScenePlay::codigoParapedirelnombreFUTURO(){
	  CEGUI::Window* ventpuntos = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("Puntuacion.layout");
	  ventpuntos->setPosition(CEGUI::UVector2(CEGUI::UDim(0.21f,0),CEGUI::UDim(0.20f,0)));
	  CEGUI::Window* imglogo = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage","VentImagenTop");
  	CEGUI::ImageManager::getSingleton().addFromImageFile("ImagenLOGOTop","puntuaciontop.png");
  	imglogo -> setProperty("Image","ImagenLOGOTop");
  	imglogo -> setProperty("BackgroundEnabled","False");
  	imglogo -> setProperty("FrameEnabled","False");
  	imglogo -> setPosition(CEGUI::UVector2(CEGUI::UDim(0.42f,0),CEGUI::UDim(0.13f,0)));
  	imglogo -> setSize(CEGUI::USize(CEGUI::UDim(0.12f,0),CEGUI::UDim(0.12f,0)));  
  	ventpuntos -> addChild(imglogo);

  	CEGUI::Window* imgtexto = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage","VentImagenOnRanking");
  	CEGUI::ImageManager::getSingleton().addFromImageFile("ImagenOR","onranking.png");
  	imgtexto -> setProperty("Image","ImagenOR");
  	imgtexto -> setProperty("BackgroundEnabled","False");
  	imgtexto -> setProperty("FrameEnabled","False");
  	imgtexto -> setPosition(CEGUI::UVector2(CEGUI::UDim(0.08f,0),CEGUI::UDim(0.07f,0)));
  	imgtexto -> setSize(CEGUI::USize(CEGUI::UDim(0.24f,0),CEGUI::UDim(0.16f,0)));  
  	ventpuntos -> addChild(imgtexto);
  	_sheet-> addChild(ventpuntos);
}