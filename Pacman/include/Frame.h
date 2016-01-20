#ifndef FRAME_H
#define FRAME_H

#include <OgreVector3.h>
#include <OgreVector4.h>

class Frame
{
 public:
  Frame (int index, const Ogre::Vector3& position, const Ogre::Vector4& rotation);
  ~Frame ();
  
  int getIndex () const { return _index; }
  Ogre::Vector3 getPosition () const { return _position; }
  Ogre::Vector4 getRotation () const { return _rotation; }
    
 private:
  // Número de frame.
  int _index;
  // Posición de la cámara en el frame _index.
  Ogre::Vector3 _position;
  // Rotación de la cámara en el frame _index.
  Ogre::Vector4 _rotation;
};

#endif