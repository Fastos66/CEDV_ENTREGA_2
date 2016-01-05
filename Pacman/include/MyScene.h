//MyScene.h

#ifndef MyScene_H
#define MyScene_H

#include <Ogre.h>
#include <OIS/OIS.h>

#include <CEGUI.h>
#include <RendererModules/Ogre/Renderer.h>

class MyScene {
public:
	MyScene(Ogre::SceneManager *sceneManager);
	~MyScene();
	void crearMenuInicio();
	void crearMenuInicioCEGUI();
private:
	CEGUI::Window* _sheet;
	Ogre::SceneManager* _sceneManager;
};



#endif