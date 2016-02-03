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
  nodemapa-> setPosition(0,0.1,0);
  nodemapa-> yaw(Ogre::Degree(180));
}	
void MyScenePlay::creacionMapa(){
    GraphVertex* pactual;
    int tamgrafo= _scene->getGraph()->getVertexes().size();
    //Ogre::SceneNode* nodemapa =  _sceneManager->getSceneNode("MapaM");  
    for (int i = 0; i < tamgrafo; ++i){
        pactual = _scene->getGraph()->getVertex(i);
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
            convertCoordinates(position,nodegum,0.1);
        }else{
            ostringstream os;
            os << "BolaC" << i;
            Ogre::Entity* ebola = _sceneManager->createEntity(os.str(), "BolaComer.mesh");
            Ogre::SceneNode* nodebola = _sceneManager->createSceneNode(os.str());
            nodebola->attachObject(ebola);
            //nodemapa->addChild(nodebola);
            _sceneManager->getRootSceneNode()->addChild(nodebola);
            const Ogre::Vector3& position = pactual->getData().getPosition();
            convertCoordinates(position,nodebola,0.1); 
        }
    }
}

void MyScenePlay::crearmenuCEGUI(){
    CEGUI::Window* imglivespuntos = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage","VentImagenLivesPoints");
    CEGUI::ImageManager::getSingleton().addFromImageFile("ImagenLivesPuntos","Livespuntos.png");
    imglivespuntos -> setProperty("Image","ImagenLivesPuntos");
    imglivespuntos -> setProperty("BackgroundEnabled","False");
    imglivespuntos -> setProperty("FrameEnabled","False");
    imglivespuntos -> setPosition(CEGUI::UVector2(CEGUI::UDim(0.23f,0),CEGUI::UDim(0.02f,0)));
    imglivespuntos -> setSize(CEGUI::USize(CEGUI::UDim(0.56f,0),CEGUI::UDim(0.17f,0)));  

    CEGUI::Window* actpoints = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("textpoints.layout");
    actpoints -> setPosition(CEGUI::UVector2(CEGUI::UDim(0.62f,0),CEGUI::UDim(0.05f,0)));
    
    _sheet -> addChild(imglivespuntos);
    _sheet -> addChild(actpoints);
}

void MyScenePlay::convertCoordinates(const Ogre::Vector3 &vect, Ogre::SceneNode* node, double offset){
    node-> setPosition(vect.x,vect.z+offset,vect.y); 
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