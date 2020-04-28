#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

class Graph;

class Menu
{
public:
    Menu();//constucteur
    ~Menu();//destructeur
    void menu();//menu
    void affichage()const;//affichage menu

    void calculIndices(Graph* Graph);//calcul affichage et sauvegarde des indices
    bool choix();//choix
    void chargementGraph();//chargement du graph
    void chargementPonderation();//chargement du poids des aretes du graphe
    ///vulnerabilit�///
    void vulnerabilite();
    void affichage_vulnerabilite()const;
private:
    Graph* m_etude;
};

#endif // MENU_H_INCLUDED
