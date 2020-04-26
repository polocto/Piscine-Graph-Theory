#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "biblio.h"

class Sommet;
class Arete;

class Graph
{
public:
    Graph();
    ~Graph();
private:
    std::vector<Sommet*> m_sommets;
    std::vector<Arete*> m_aretes;
};

#endif
