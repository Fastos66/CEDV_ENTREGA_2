#include <GraphEdge.h>

GraphEdge::GraphEdge
(GraphVertex* origin, GraphVertex* dest)
  :_pOrigin(origin), _pDestination(dest)
{
}

GraphEdge::~GraphEdge () 
{
}
