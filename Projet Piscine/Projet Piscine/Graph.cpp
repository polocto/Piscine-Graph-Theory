#include "Graph.h"
#include "Arete.h"
#include "Sommet.h"
#include "svgfile.h"


Graph::Graph(std::ifstream&ifs)
{

}

Graph::~Graph()
{

}

void Graph::affichage(Svgfile* svgout)
{
    for (Sommet* S:m_sommets)
    {
        S->affichage(svgout);

    }
    for (Arete* S:m_aretes)
    {
        S->affichage(svgout);
    }
}
