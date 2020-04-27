#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "biblio.h"
#include "svgfile.h"
class Sommet;
class Arete;

class Graph
{
public:
    Graph(std::ifstream&ifs);
    ~Graph();
    void affichage(Svgfile& svgout);
    void chargementPonderation(std::string nomfichier);
    void affichageconsole();
private:
    std::vector<Sommet*> m_sommets;
    std::vector<Arete*> m_aretes;
    bool m_oriente;
};

#endif
