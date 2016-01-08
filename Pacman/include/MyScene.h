//MyScene.h

#ifndef MyScene_H
#define MyScene_H

#include <Ogre.h>
#include <OIS/OIS.h>

#include <CEGUI.h>
#include <RendererModules/Ogre/Renderer.h>

class MyScene {
public:
	MyScene(Ogre::SceneManager *sceneManager, CEGUI::Window* sheet);
	~MyScene();
	void crearMenuInicio();
	void crearMenuInicioCEGUI();
	void creditos();
	void retroceder();
	bool limpiarpantallaCEGUI();
private:
	Ogre::SceneManager* _sceneManager;
	CEGUI::Window* _sheet;
};



#endif