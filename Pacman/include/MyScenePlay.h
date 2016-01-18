#ifndef MyScenePlay_H
#define MyScenePlay_H
#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI.h>
#include <RendererModules/Ogre/Renderer.h>
class MyScenePlay
{
	public:
		MyScenePlay(Ogre::SceneManager* sceneManager);
		~MyScenePlay();
		void cargarscenainicial();
		void codigoParapedirelnombreFUTURO();
	private:
		Ogre::SceneManager* _sceneManager;
		CEGUI::Window* _sheet;	
};


#endif
