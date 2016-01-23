#include <Scene.h>

Scene::Scene ()
{
  _graph = new Graph;
}

Scene::~Scene ()
{
}

void
Scene::addCamera
(Camera* camera)
{
  _cameras.push_back(camera);
}
