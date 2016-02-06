#ifndef MyScenePlay_H
#define MyScenePlay_H
#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI.h>
#include <RendererModules/Ogre/Renderer.h>
#include "Scene.h"
#include <iostream>
#include <sstream>
#include <string> 
#include "Item.h"
class MyScenePlay
{
	public:
		MyScenePlay(Ogre::SceneManager* sceneManager, Scene* scene, Ogre::Camera* _camera);
		MyScenePlay(Ogre::SceneManager* sceneManager, Ogre::Camera* _camera);
		~MyScenePlay();
		void cargarscenainicial();
		void pedirelnombre_actualizar_ranking();
		void creacionMapa(std::vector<Item*> *vItems);
		void convertCoordinates(const Ogre::Vector3 &vect, Ogre::SceneNode* node, double offset);
		void crearmenuCEGUI();
		void actualizarPuntos(int newpuntos);

		void cargarlives();
		void perderlive(int numlive);
		
		string getpuntosjugador();
		string getnombrejugador();

		void menupausa();
		void salirpausa();
	
	private:
		Ogre::SceneManager* _sceneManager;
		CEGUI::Window* _sheet;
		Scene* _scene;
		Ogre::Camera* _camera;
};


#endif
