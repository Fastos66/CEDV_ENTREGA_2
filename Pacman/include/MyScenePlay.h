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
class MyScenePlay
{
	public:
		MyScenePlay(Ogre::SceneManager* sceneManager, Scene* scene);
		~MyScenePlay();
		void cargarscenainicial();
		void codigoParapedirelnombreFUTURO();
		void pruebasGRAFO();
	private:
		Ogre::SceneManager* _sceneManager;
		CEGUI::Window* _sheet;
		Scene* _scene;
};


#endif
