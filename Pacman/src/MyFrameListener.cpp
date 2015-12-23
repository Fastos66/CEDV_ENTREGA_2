/*********************************************************************
 * Módulo 2. Curso de Experto en Desarrollo de Videojuegos
 * Autor: Carlos González Morcillo     Carlos.Gonzalez@uclm.es
 *
 * You can redistribute and/or modify this file under the terms of the
 * GNU General Public License ad published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * and later version. See <http://www.gnu.org/licenses/>.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.  
 *********************************************************************/
#include "MyFrameListener.h"

MyFrameListener::MyFrameListener(Ogre::RenderWindow* win, 
				 Ogre::Camera* cam, 
				 Ogre::SceneNode *node, 
				 Ogre::SceneManager *sm) {
  OIS::ParamList param;
  size_t windowHandle;  std::ostringstream wHandleStr;

  _camera = cam;  _node = node;
  _sceneManager = sm; _win = win;
  
  _win->getCustomAttribute("WINDOW", &windowHandle);
  wHandleStr << windowHandle;
  param.insert(std::make_pair("WINDOW", wHandleStr.str()));
  
  _inputManager = OIS::InputManager::createInputSystem(param);
  _keyboard = static_cast<OIS::Keyboard*>
    (_inputManager->createInputObject(OIS::OISKeyboard, false));

  _animState = NULL;
}

MyFrameListener::~MyFrameListener() {
  _inputManager->destroyInputObject(_keyboard);
  OIS::InputManager::destroyInputSystem(_inputManager);
}

bool MyFrameListener::frameStarted(const Ogre::FrameEvent& evt) {
  Ogre::Vector3 vt(0,0,0);     
  Ogre::Real r = 0;
  Ogre::Real deltaT = evt.timeSinceLastFrame;
 
  _keyboard->capture();

  if(_keyboard->isKeyDown(OIS::KC_ESCAPE)) return false;

  if (_keyboard->isKeyDown(OIS::KC_A) || _keyboard->isKeyDown(OIS::KC_Z)) {
    if (_keyboard->isKeyDown(OIS::KC_A)) {
      _animState = _sceneManager->getEntity("Pacman")->getAnimationState("VerMenu");
    }
    _animState->setEnabled(true);
    _animState->setLoop(true);
    _animState->setTimePosition(0.0);
  }
  
  if (_animState != NULL) {
    if (_animState->hasEnded()) {
      _animState->setTimePosition(0.0);
      _animState->setEnabled(false);
    }
    else {
      _animState->addTime(deltaT);
    }
  }

  if(_keyboard->isKeyDown(OIS::KC_T)) r+=180;
  _node->yaw(Ogre::Degree(r * deltaT));
  
 
  return true;
}
