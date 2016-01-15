//MyScene.h

#ifndef MyScene_H
#define MyScene_H

#include <Ogre.h>
#include <OIS/OIS.h>
#include "Ranking.h"
#include <CEGUI.h>
#include <RendererModules/Ogre/Renderer.h>

class MyScene {
public:
	MyScene(Ogre::SceneManager *sceneManager, CEGUI::Window* sheet);
	MyScene(Ogre::SceneManager *sceneManager);
	~MyScene();
	void crearMenuInicio();
	void crearMenuInicioCEGUI();
	void creditos();
	void ranking();
	void retroceder();
	bool limpiarpantallaCEGUI();
	bool limpiarpantallaCEGUIControles();
	void ActRanking();
	void controles();
private:
	Ogre::SceneManager* _sceneManager;
	CEGUI::Window* _sheet;
};
#endif