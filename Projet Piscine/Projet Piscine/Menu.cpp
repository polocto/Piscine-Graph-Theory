#include "Graph.h"
#include "Menu.h"


Menu::Menu()
    :m_etude(nullptr)
{

}

void Menu::menu()
{
    do
        affichage();
    while(choix());

}

void Menu::affichage()const
{
    std::cout<<"0/Quitter"<<std::endl;
    std::cout<<"1/Charger Graph"<<std::endl;
    std::cout<<"2/Charger Ponderation"<<std::endl;
    std::cout<<"3/Calcule indices"<<std::endl;
    std::cout<<"4/Vulnerabilite"<<std::endl;
}

//affichage dans la console du graphe apres la construction
void Menu::affichageresultat()
{
    m_etude->affichageconsole();
}


bool Menu::choix()
{
    std::string saisie;
    std::cin>>saisie;
    if(!is_int(saisie))
        saisie="99";
    if(!m_etude && std::stoi(saisie)>1)
    {
        std::cout<<"Veuillez charger un Graph."<<std::endl;
        return true;
    }
    switch(std::stoi(saisie))
    {
    case 0:
        return false;
        break;
    case 1:
        chargementGraph();
        break;
    case 2:
        chargementPonderation();
        break;
    case 3:
        break;
    case 4:
        break;
    default:
        std::cout<<"Ce choix ne fait pas parti des options ci-dessus."<<std::endl;
    }
    return true;
}


void Menu::chargementGraph()
{
    std::string nom_fichier;
    std::ifstream ifs;
    Graph* tampon=nullptr;
    std::cout<<"Entrez le nom du fichier a charger : ";
    std::cin>>nom_fichier;
    ifs.open(nom_fichier);
    if(!ifs.is_open())
    {
        std::cout<<"Probleme d'ouverture du fichier : "<<nom_fichier<<std::endl;
        return;
    }
    try
    {
        tampon=new Graph(ifs);
        if(m_etude)
            delete m_etude;
        m_etude=tampon;
    }
    catch(int a)
    {
        if(tampon)
            delete tampon;
        std::cout<<"Verifie le format du fichier : "<<nom_fichier<<std::endl;
    }

}

void Menu::chargementPonderation()
{
    std::ifstream ifs;
    std::string nom_fichier;

    std::cout<<"entrer le nom du fichier de ponderation : ";
    std::cin>>nom_fichier;

    ifs.open(nom_fichier);
    if(!ifs.is_open())
    {
        std::cout<<"Probleme d'ouverture du fichier : "<<nom_fichier<<std::endl;
        return;
    }

    m_etude->chargementPonderation(nom_fichier);

}
