#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <OgreVector3.h>

using namespace std;

class Node
{
 public:
  Node ();
  Node (const int& index, const string& type, const Ogre::Vector3& position);
  ~Node ();
  
  int getIndex () const { return _index; }
  string getType () const { return _type; }
  Ogre::Vector3 getPosition () const { return _position; }
  operator std::string() const;
    
 private:
  // Índice del nodo (id único).
  int _index;
  // Tipo: generador (spawn), sumidero (drain)
  string _type;
  // Posición del nodo en el espacio 3D.
  Ogre::Vector3 _position;
};

#endif
