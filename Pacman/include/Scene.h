#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <Camera.h>
#include <Node.h>
#include <Graph.h>

class Scene
{
 public:
  Scene ();
  ~Scene ();
  
  void addCamera (Camera* camera);    
  Graph* getGraph () const { return _graph;}
  std::vector<Camera*> getCameras () const { return _cameras; }
    
 private:
  Graph *_graph;
  std::vector<Camera*> _cameras;
};

#endif
