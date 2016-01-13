#ifndef MyScenePlay_H
#define MyScenePlay_H
#include <Ogre.h>
#include <OIS/OIS.h>
class MyScenePlay
{
	public:
		MyScenePlay(Ogre::SceneManager* sceneManager);
		~MyScenePlay();
		void cargarscenainicial();
	private:
		Ogre::SceneManager* _sceneManager;	
};


#endif
