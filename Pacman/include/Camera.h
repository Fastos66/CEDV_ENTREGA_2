#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <vector>
#include <Frame.h>

class Camera
{
 public:
  Camera (int index, int fps);
  ~Camera ();
  
  void addFrameToPath (Frame* frame);
  
  int getIndex () const { return _index; }
  int getFPS () const { return _fps; }
  std::vector<Frame*> getPath () const { return _path; }
  
  operator std::string() const;
    
 private:
  // Identificador de la cámara.
  int _index;
  // Tasa de frames de la cámara.
  int _fps;
  // Secuencia de frames que conforman el camino de la cámara.
  std::vector<Frame*> _path;
};

#endif
