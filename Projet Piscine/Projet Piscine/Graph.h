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
    Graph(Graph* Gmodel,std::string changement);
    ~Graph();
    void affichage(Svgfile& svgout);
    void chargementPonderation(std::string nomfichier);
    void affichageconsole()const;
    void calc_icd();
    void calc_vect_propre();
    void calc_ici_naif();
    void calc_icp();
    double Dijkstra(Sommet* depart,Sommet* arriver);
    bool Dijkstra(Sommet* depart,Sommet* arriver,Sommet* passage);
    void sauvegarde(std::ofstream&fichier)const;
    int k_connexe()const;
///vulnerabilité
    Graph* Supression_element();
private:
    std::vector<Sommet*> m_sommets;//tableau de tous les sommet du graph
    std::vector<Arete*> m_aretes;// tableau de toutes les aretes du graph
    bool m_oriente;
};

#endif
