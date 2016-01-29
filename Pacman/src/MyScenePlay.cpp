//MyScenePlay.cpp

#include "MyScenePlay.h"
MyScenePlay::MyScenePlay(Ogre::SceneManager* sceneManager, Scene* scene, Ogre::Camera* camera){
	_sceneManager=sceneManager;
	_sheet = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
  _scene = scene;
  _camera = camera;
}
MyScenePlay::~MyScenePlay() {}
void MyScenePlay::cargarscenainicial(){  
  _camera->setPosition(Ogre::Vector3(0,15,-15));
  _camera->lookAt(Ogre::Vector3(0,0,0));
  Ogre::SceneNode* nodemapa =  _sceneManager->getSceneNode("MapaM");
  nodemapa-> setVisible(true);
  //nodemapa-> setScale(1.1,1.1,1.1);
  nodemapa-> setPosition(0,0.1,0);
  //nodemapa-> yaw(Ogre::Degree(12.5));
  //nodemapa-> pitch(Ogre::Degree(20));
  nodemapa-> yaw(Ogre::Degree(180));
}	
void MyScenePlay::pruebasGRAFO(){
    GraphVertex* pactual;
    int tamgrafo= _scene->getGraph()->getVertexes().size();
    Ogre::SceneNode* nodemapa =  _sceneManager->getSceneNode("MapaM");  
    for (int i = 0; i < tamgrafo; ++i){
        pactual = _scene->getGraph()->getVertex(i+1);
        cout << "1Vertex " << pactual->getData().getPosition()  << endl;
        if (pactual->getData().getType().compare("gummelon")==0){
            ostringstream os;
            os << "Gum" << i;
            Ogre::Entity* egum = _sceneManager->createEntity(os.str(), "Melon.mesh");
            Ogre::SceneNode* nodegum = _sceneManager->createSceneNode(os.str());
            nodegum->attachObject(egum);
            nodegum -> setScale(0.45,0.45,0.45);
            nodegum-> yaw(Ogre::Degree(-45));
            //nodemapa->addChild(nodegum);
            _sceneManager->getRootSceneNode()->addChild(nodegum);
            const Ogre::Vector3& position = pactual->getData().getPosition();
            nodegum-> setPosition(position.x,position.z+0.1,position.y);  
        }else{
            ostringstream os;
            os << "BolaC" << i;
            Ogre::Entity* ebola = _sceneManager->createEntity(os.str(), "BolaComer.mesh");
            Ogre::SceneNode* nodebola = _sceneManager->createSceneNode(os.str());
            nodebola->attachObject(ebola);
            //nodemapa->addChild(nodebola);
            _sceneManager->getRootSceneNode()->addChild(nodebola);
            const Ogre::Vector3& position = pactual->getData().getPosition();
            cout << position.x << " " << position.y << " " << position.z << endl; 
            nodebola-> setPosition(position.x,position.z+0.1,position.y);  
        }
    }
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