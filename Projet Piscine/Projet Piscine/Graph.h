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
    void calc_icd();
    double Dijkstra(Sommet* depart,Sommet* arriver);
    void calc_icp();
private:
    std::vector<Sommet*> m_sommets;//tableau de tous les sommet du graph
    std::vector<Arete*> m_aretes;// tableau de toutes les aretes du graph
    bool m_oriente;
};

#endif
