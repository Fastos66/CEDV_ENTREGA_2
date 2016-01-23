#include <Frame.h>

Frame::Frame
(int index, const Ogre::Vector3& position, const Ogre::Vector4& rotation):
  _index(index), _position(position), _rotation(rotation)
{
}

Frame::~Frame ()
{
}

