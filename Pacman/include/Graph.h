#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <GraphVertex.h>
#include <GraphEdge.h>

class Graph
{
 public:
  Graph ();
  ~Graph ();
  
  void addVertex (GraphVertex* pVertex);
  void addEdge (GraphVertex* pOrigin, GraphVertex* pDestination,
		bool undirected = true);

  // Lista de vértices adyacentes a uno dado.
  std::vector<GraphVertex*> adjacents (int index) const;

  GraphVertex* getVertex (int index) const;
  std::vector<GraphVertex*> getVertexes () const { return _vertexes; }
  std::vector<GraphEdge*> getEdges () const { return _edges; }

 private:
  std::vector<GraphVertex*> _vertexes;
  std::vector<GraphEdge*> _edges;
};

#endif