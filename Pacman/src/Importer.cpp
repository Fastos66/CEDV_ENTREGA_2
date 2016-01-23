#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <OgreVector3.h>
#include <OgreVector4.h>
#include <iostream>
#include <Importer.h>

using namespace std;
using namespace xercesc;

template<> Importer* Ogre::Singleton<Importer>::msSingleton = 0;

Importer* Importer::getSingletonPtr(void)
{
    return msSingleton;
}
Importer& Importer::getSingleton(void)
{  
    assert( msSingleton );  return ( *msSingleton );  
}

void
Importer::parseScene
(const char* path, Scene *scene)
{
  // Inicialización.
  try {
    XMLPlatformUtils::Initialize();
  }
  catch (const XMLException& toCatch) {
    char* message = XMLString::transcode(toCatch.getMessage());
    cout << "Error durante la inicialización! :\n"
	 << message << "\n";
    XMLString::release(&message);
    return;
  }

  XercesDOMParser* parser = new XercesDOMParser();
  parser->setValidationScheme(XercesDOMParser::Val_Always);

  // 'Parseando' el fichero xml...
  try {
    parser->parse(path);
  }
  catch (const XMLException& toCatch) {
    char* message = XMLString::transcode(toCatch.getMessage());
    cout << "Excepción capturada: \n"
	 << message << "\n";
    XMLString::release(&message);
  }
  catch (const DOMException& toCatch) {
    char* message = XMLString::transcode(toCatch.msg);
    cout << "Excepción capturada: \n"
	 << message << "\n";
    XMLString::release(&message);
  }
  catch (...) {
    cout << "Excepción no esperada.\n" ;
    return;
  }

  DOMDocument* xmlDoc;
  DOMElement* elementRoot;

  try {
    // Obtener el elemento raíz del documento.
    xmlDoc = parser->getDocument(); 
    elementRoot = xmlDoc->getDocumentElement();

    if(!elementRoot)
      throw(std::runtime_error("Documento XML vacío."));

  }
  catch (xercesc::XMLException& e ) {
    char* message = xercesc::XMLString::transcode( e.getMessage() );
    ostringstream errBuf;
    errBuf << "Error 'parseando': " << message << flush;
    XMLString::release( &message );
    return;
  }

  XMLCh* camera_ch = XMLString::transcode("camera");  
  XMLCh* graph_ch = XMLString::transcode("graph");  

  // Procesando los nodos hijos del raíz...
  for (XMLSize_t i = 0; 
       i < elementRoot->getChildNodes()->getLength(); 
       ++i ) {
    
    DOMNode* node = elementRoot->getChildNodes()->item(i);

    if (node->getNodeType() == DOMNode::ELEMENT_NODE) {
      // Nodo <camera>?
      if (XMLString::equals(node->getNodeName(), camera_ch))
	parseCamera(node, scene);
      else
	// Nodo <graph>?
	if (XMLString::equals(node->getNodeName(), graph_ch))
	  parseGraph(node, scene);
    }
    
  }
  // Liberar recursos.
  XMLString::release(&camera_ch);
  XMLString::release(&graph_ch);

  delete parser;
}

void
Importer::parseCamera
(xercesc::DOMNode* cameraNode, Scene* scene)
{
  // Atributos de la cámara.
  DOMNamedNodeMap* attributes = cameraNode->getAttributes();
  DOMNode* indexNode = attributes->getNamedItem(XMLString::transcode("index"));
  DOMNode* fpsNode = attributes->getNamedItem(XMLString::transcode("fps"));

  int camera_index = atoi(XMLString::transcode(indexNode->getNodeValue()));
  int camera_fps = atoi(XMLString::transcode(fpsNode->getNodeValue()));

  // Instanciar la cámara.
  Camera* camera = new Camera(camera_index, camera_fps);

  XMLCh* path_ch = XMLString::transcode("path");  

  // Procesar el path de la cámara.
  for (XMLSize_t i = 0; i < cameraNode->getChildNodes()->getLength(); ++i ) {

    DOMNode* pathNode = cameraNode->getChildNodes()->item(i);

    // Nodo <path>?
    if (pathNode->getNodeType() == DOMNode::ELEMENT_NODE &&
	XMLString::equals(pathNode->getNodeName(), path_ch))
      addPathToCamera(pathNode, camera);

  }

  XMLString::release(&path_ch);

  // Cada vez que se parsea una cámara,
  // se añade a la escena.
  scene->addCamera(camera);
}

void
Importer::addPathToCamera
(xercesc::DOMNode* pathNode, Camera *camera)
{
  XMLCh* position_ch = XMLString::transcode("position");
  XMLCh* rotation_ch = XMLString::transcode("rotation");

  for (XMLSize_t i = 0; i < pathNode->getChildNodes()->getLength(); ++i ) {

    DOMNode* frameNode = pathNode->getChildNodes()->item(i);
    if (frameNode->getNodeType() == DOMNode::ELEMENT_NODE ) {

      // Atributos del frame.
      DOMNamedNodeMap* attributes = frameNode->getAttributes();
      DOMNode* indexNode = attributes->getNamedItem(XMLString::transcode("index"));
      int frame_index = atoi(XMLString::transcode(indexNode->getNodeValue()));

      Ogre::Vector3 frame_position;
      Ogre::Vector4 frame_rotation;

      for (XMLSize_t j = 0; j < frameNode->getChildNodes()->getLength(); ++j ) {
	DOMNode* node = frameNode->getChildNodes()->item(j);

	if (node->getNodeType() == DOMNode::ELEMENT_NODE) {
	  // Nodo <position>?
	  if (XMLString::equals(node->getNodeName(), position_ch))
	    getFramePosition(node, &frame_position);
	  else
	    // Nodo <rotation>?
	    if (XMLString::equals(node->getNodeName(), rotation_ch))
	      getFrameRotation(node, &frame_rotation);
	}
      }

      // Instaciar el frame.
      Frame* frame = new Frame(frame_index, frame_position, frame_rotation);
      // Añadirlo al path de la cámara.
      camera->addFrameToPath(frame);

    }

  }

  XMLString::release(&position_ch);
  XMLString::release(&rotation_ch);
}

void
Importer::getFramePosition
(xercesc::DOMNode* node, Ogre::Vector3* position)
{
  XMLCh* x_ch = XMLString::transcode("x");  
  XMLCh* y_ch = XMLString::transcode("y");  
  XMLCh* z_ch = XMLString::transcode("z");  

  float x = getValueFromTag(node, x_ch);
  float y = getValueFromTag(node, y_ch);
  float z = getValueFromTag(node, z_ch);

  position->x = x;
  position->y = y;
  position->z = z;

  XMLString::release(&x_ch);
  XMLString::release(&y_ch);
  XMLString::release(&z_ch);
}

void
Importer::getFrameRotation
(xercesc::DOMNode* node, Ogre::Vector4* rotation)
{
  XMLCh* x_ch = XMLString::transcode("x");  
  XMLCh* y_ch = XMLString::transcode("y");  
  XMLCh* z_ch = XMLString::transcode("z");  
  XMLCh* w_ch = XMLString::transcode("w");  

  float x = getValueFromTag(node, x_ch);
  float y = getValueFromTag(node, y_ch);
  float z = getValueFromTag(node, z_ch);
  float w = getValueFromTag(node, w_ch);

  rotation->x = x;
  rotation->y = y;
  rotation->z = z;
  rotation->w = w;

  XMLString::release(&x_ch);
  XMLString::release(&y_ch);
  XMLString::release(&z_ch);
  XMLString::release(&w_ch);
}

void
Importer::parseGraph
(xercesc::DOMNode* graphNode, Scene* scene)
{
  XMLCh* vertex_ch = XMLString::transcode("vertex");
  XMLCh* edge_ch = XMLString::transcode("edge");

  for (XMLSize_t i = 0; i < graphNode->getChildNodes()->getLength(); ++i ) {

    DOMNode* node = graphNode->getChildNodes()->item(i);

    if (node->getNodeType() == DOMNode::ELEMENT_NODE) {
      // Nodo <vertex>?
      if (XMLString::equals(node->getNodeName(), vertex_ch))
	addVertexToScene(node, scene);
      else
      // Nodo <edge>?
	if (XMLString::equals(node->getNodeName(), edge_ch)) {
	  addEdgeToScene(node, scene);
	}
    }
    
  }

  XMLString::release(&vertex_ch);
  XMLString::release(&edge_ch);
}

void
Importer::addVertexToScene
(xercesc::DOMNode* vertexNode, Scene* scene)
{
  DOMNamedNodeMap* attributes = vertexNode->getAttributes();
  DOMNode* indexNode = attributes->getNamedItem(XMLString::transcode("index"));
  DOMNode* typeNode = attributes->getNamedItem(XMLString::transcode("type"));

  int vertex_index = atoi(XMLString::transcode(indexNode->getNodeValue()));
  string vertex_type = XMLString::transcode(typeNode->getNodeValue());  

  XMLCh* x_ch = XMLString::transcode("x");  
  XMLCh* y_ch = XMLString::transcode("y");  
  XMLCh* z_ch = XMLString::transcode("z");  

  float x = getValueFromTag(vertexNode, x_ch);
  float y = getValueFromTag(vertexNode, y_ch);
  float z = getValueFromTag(vertexNode, z_ch);

  // Instanciar la posición del nodo.
  Ogre::Vector3 position(x, y, z);
  // Instanciar el nodo.
  Node n(vertex_index, vertex_type, position);
  // Añadir el nodo a la estructura de grafo.
  scene->getGraph()->addVertex(new GraphVertex(n));

  XMLString::release(&x_ch);
  XMLString::release(&y_ch);
  XMLString::release(&z_ch);
}

void
Importer::addEdgeToScene
(xercesc::DOMNode* edgeNode, Scene* scene)
{
  XMLCh* vertex_ch = XMLString::transcode("vertex");
  std::vector<int> edge;

  for (XMLSize_t i = 0; i < edgeNode->getChildNodes()->getLength(); ++i ) {

    DOMNode* node = edgeNode->getChildNodes()->item(i);
    // Nodo <vertex>?
    if ((node->getNodeType() == DOMNode::ELEMENT_NODE) &&
  	XMLString::equals(node->getNodeName(), vertex_ch))
      edge.push_back(atoi(XMLString::transcode
			  (node->getFirstChild()->getNodeValue())));
  }

  // Recuperar los vértices a partir de su index,
  // para generar y añadir el arco.
  GraphVertex *v1 = scene->getGraph()->getVertex(edge[0]);
  GraphVertex *v2 = scene->getGraph()->getVertex(edge[1]);

  scene->getGraph()->addEdge(v1, v2);

  XMLString::release(&vertex_ch);
}

float
Importer::getValueFromTag
(xercesc::DOMNode* node, const XMLCh *tag)
{
  for (XMLSize_t i = 0; i < node->getChildNodes()->getLength(); ++i ) {

    DOMNode* aux = node->getChildNodes()->item(i);

    if (aux->getNodeType() == DOMNode::ELEMENT_NODE &&
	XMLString::equals(aux->getNodeName(), tag))
      return atof(XMLString::transcode(aux->getFirstChild()->getNodeValue()));

  }
  return 0.0;
}
