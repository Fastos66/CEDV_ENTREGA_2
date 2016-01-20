#ifndef GRAPHVERTEX_H
#define GRAPHVERTEX_H

#include <iostream>
#include <vector>
#include <GraphEdge.h>
#include <Node.h>

using namespace std;

class GraphEdge;

class GraphVertex
{
 public:
  GraphVertex (const Node& data);
  ~GraphVertex ();

  Node getData () const { return _data; }
  void addEdge (GraphEdge* pEdge) { _edges.push_back(pEdge); }

  std::vector<GraphEdge*> getEdges () const { return _edges; }
  std::vector<GraphVertex*> adjacents () const;
  
 private:
  Node _data;
  std::vector<GraphEdge*> _edges;
};

#endif