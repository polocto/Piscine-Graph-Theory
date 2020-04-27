#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

class Graph;

class Menu
{
public:
    Menu();
    ~Menu()=default;
    void menu();
    void affichage()const;
    void calculIndices();
    bool choix();
    void chargementGraph();
private:
    Graph* m_etude;
};

#endif // MENU_H_INCLUDED
