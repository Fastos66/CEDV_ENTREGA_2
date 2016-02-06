//MyScenePlay.cpp

#include "MyScenePlay.h"
#include "PauseState.h"
#include "FinalGameState.h"
MyScenePlay::MyScenePlay(Ogre::SceneManager* sceneManager, Scene* scene, Ogre::Camera* camera){
	_sceneManager = sceneManager;
	_sheet = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
  _scene = scene;
  _camera = camera;
}

MyScenePlay::MyScenePlay(Ogre::SceneManager* sceneManager, Ogre::Camera* camera){
  _sceneManager = sceneManager;
  _sheet = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
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
void MyScenePlay::creacionMapa(vector<Item*> *vItems){
    GraphVertex* pactual;
    int tamgrafo= _scene->getGraph()->getVertexes().size();
    //Ogre::SceneNode* nodemapa =  _sceneManager->getSceneNode("MapaM");  
    for (int i = 0; i < tamgrafo; ++i){
        pactual = _scene->getGraph()->getVertex(i);
        cout << "1Vertex " << pactual->getData().getPosition()  << endl;
        
        if (pactual->getData().getType().compare("gummelon")==0){
           
            cout << "Gum" << i << endl;
            ostringstream os;
            os << "Gum" << i;
            Ogre::Entity* egum = _sceneManager->createEntity(os.str(), "Melon.mesh");
            Ogre::SceneNode* nodegum = _sceneManager->createSceneNode(os.str());
            Item *ite = new Item(nodegum,true);
            ite-> setGraphVertex(pactual);
            vItems->push_back(ite);

            nodegum->attachObject(egum);
            nodegum -> setScale(0.90,0.90,0.90);
            nodegum-> yaw(Ogre::Degree(-45));
            //nodemapa->addChild(nodegum);
            _sceneManager->getRootSceneNode()->addChild(nodegum);
            const Ogre::Vector3& position = pactual->getData().getPosition();
            convertCoordinates(position,nodegum,0.4);
        }else{
            ostringstream os;
            os << "BolaC" << i;
            Ogre::Entity* ebola = _sceneManager->createEntity(os.str(), "BolaComer.mesh");
            Ogre::SceneNode* nodebola = _sceneManager->createSceneNode(os.str());
            Item *ite = new Item(nodebola,false);
            ite->setGraphVertex(pactual);
            vItems->push_back(ite);

            nodebola->attachObject(ebola);
            //nodemapa->addChild(nodebola);
            _sceneManager->getRootSceneNode()->addChild(nodebola);
            const Ogre::Vector3& position = pactual->getData().getPosition();
            convertCoordinates(position,nodebola,0.2); 
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

    CEGUI::Window* menupausa = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("pausaState.layout");
    menupausa -> setVisible(false);
    CEGUI::Window* lista = menupausa->getChild("ListaPausa");
    CEGUI::Window* continuar = lista->getChild("ContinuarButton");
      continuar->subscribeEvent(CEGUI::PushButton::EventClicked,
          CEGUI::Event::Subscriber(&PauseState::continuarButtonC, 
                PauseState::getSingletonPtr())); 
    _sheet -> addChild(menupausa);  
}

void MyScenePlay::convertCoordinates(const Ogre::Vector3 &vect, Ogre::SceneNode* node, double offset){
    node-> setPosition(vect.x,vect.z+offset,vect.y); 
}
void MyScenePlay::actualizarPuntos(int newpuntos){
    CEGUI::Window* points = _sheet -> getChild("PointsPlayer");
    int points_actuales = atoi(points->getText().c_str());
    cout << "Puntos Actuales:" << points_actuales << endl; 
    points_actuales = newpuntos + points_actuales;
    ostringstream os;
    os << points_actuales;
    points -> setText(os.str());
}
void MyScenePlay::pedirelnombre_actualizar_ranking(){
	  CEGUI::Window* ventpuntos = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("Puntuacion.layout");
	  ventpuntos->setPosition(CEGUI::UVector2(CEGUI::UDim(0.21f,0),CEGUI::UDim(0.20f,0)));
	  
    //Act Puntos
    CEGUI::Window* points = _sheet -> getChild("PointsPlayer");
    CEGUI::Window* puntosplayer = ventpuntos->getChild("PuntosPlayer");
    puntosplayer->setText(points->getText().c_str());

    CEGUI::Window* exitbutton = ventpuntos->getChild("ExitButton");
      exitbutton->subscribeEvent(CEGUI::PushButton::EventClicked,
          CEGUI::Event::Subscriber(&FinalGameState::exitButtonC, 
                FinalGameState::getSingletonPtr())); 

    CEGUI::Window* imglogo = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage","VentImagenTop");
  	CEGUI::ImageManager::getSingleton().addFromImageFile("ImagenLOGOTop","puntuaciontop.png");
  	imglogo -> setProperty("Image","ImagenLOGOTop");
  	imglogo -> setProperty("BackgroundEnabled","False");
  	imglogo -> setProperty("FrameEnabled","False");
  	imglogo -> setPosition(CEGUI::UVector2(CEGUI::UDim(0.47f,0),CEGUI::UDim(0.13f,0)));
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

void MyScenePlay::menupausa(){
     CEGUI::Window* menupausa = _sheet-> getChild("Menupausa");
     menupausa -> setVisible(true);
     menupausa -> setPosition(CEGUI::UVector2(CEGUI::UDim(0.18f,0),CEGUI::UDim(0.14f,0)));      
}
void MyScenePlay::salirpausa(){
     CEGUI::Window* menupausa = _sheet-> getChild("Menupausa");
     menupausa -> setVisible(false);  
}

string MyScenePlay::getpuntosjugador(){
     return _sheet->getChild("Puntuacion")->getChild("PuntosPlayer")->getText().c_str();
}
string MyScenePlay::getnombrejugador(){
     return _sheet->getChild("Puntuacion")->getChild("NombrePlayer")->getText().c_str();
}

void MyScenePlay::cargarlives(){
     double posx[3] = {3,2.5,2};
     for (int i = 0; i < 3; ++i){
          ostringstream os;
          os << "Live" << i;  
          Ogre::Entity* elive = _sceneManager->createEntity(os.str(), "FantasmaR.mesh");
          Ogre::SceneNode* nodelive = _sceneManager->createSceneNode(os.str());
          nodelive->attachObject(elive);
          nodelive->setPosition(posx[i],7.7,0);   
          nodelive->setScale(0.2,0.2,0.2);
          nodelive->yaw(Ogre::Degree(-82.5));
          _sceneManager->getRootSceneNode()->addChild(nodelive);
     }
}
void MyScenePlay::perderlive(int numlive){
    ostringstream os;
    os << "Live" << numlive;
    _sceneManager->getSceneNode(os.str())->setVisible(false); 
}