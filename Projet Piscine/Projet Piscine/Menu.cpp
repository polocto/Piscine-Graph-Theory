#include "Graph.h"
#include "Menu.h"

/**Constructeur de menu
initialise le graph à nullptr*/
Menu::Menu()
    :m_etude(nullptr)
{

}
/**Destructeur de Menu*/
Menu::~Menu()
{
    if(m_etude)//si graph n'est pa null
        delete m_etude;//detruir graph
}

/**Menu Affichage et choix option*/
void Menu::menu()
{
    do//faire
        affichage();//affichage des différentes option du menu
    while(choix());//tant qu'on ne quitte pas

}

/**Affiche les différentes options proposer pour l'etude d'un graphe
son chargement
chargement de pondération
calcul de ses différents indices
sa vulnérabilité
ainsi que l'option pour quitter*/
void Menu::affichage()const
{
    std::cout<<"0/Quitter"<<std::endl;
    std::cout<<"1/Charger Graph"<<std::endl;
    std::cout<<"2/Charger Ponderation"<<std::endl;
    std::cout<<"3/Calcule indices"<<std::endl;
    std::cout<<"4/Vulnerabilite"<<std::endl;
}

/**Saisie du choix et appel en fonction du choix
retourn un booléen:
faux si quitter
sinon vrai*/
bool Menu::choix()
{
    std::string saisie;
    std::cin>>saisie;//saisie utilisateur
    if(!is_int(saisie))//si la saisie n'est pas un nombre entier naturel
        saisie="99";//metre saisie à 99
    if(!m_etude && std::stoi(saisie)>1)//si etude est null et qu'on ne quitte pas ou qu'on ne charge pas de graph
    {
        std::cout<<"Veuillez charger un Graph."<<std::endl;//message console
        return true;//retourne vrai
    }
    switch(std::stoi(saisie))
    {
    case 0://Quitter
        return false;
        break;
    case 1://Chargement d'un Graph
        chargementGraph();
        break;
    case 2://Chargement d'une pondération pour graph
        chargementPonderation();
        break;
    case 3://calcul affichage et sauvegarde des indices
        calculIndices();
        break;
    case 4://Test la vulnérabilité du graph
        break;
    default://si la saisie ne correspond à aucune case
        std::cout<<"Ce choix ne fait pas parti des options ci-dessus."<<std::endl;//message console
    }
    return true;//retourne vrai par default
}
/**
calcul affichage et sauvegarde des indices du graph
*/

void Menu::calculIndices()
{
    Svgfile svgout;//fichier svg pour l'affichage
    //svgout.addGrid();
    m_etude->calc_icd();
    m_etude->calc_icp();
    m_etude->affichage(svgout);//affichage sur fichier svg
    m_etude->affichageconsole();//affichage console

}

/**
Chargement du graph
Chargement du graph à paritir d'un fichier dont le nom est à saisir
*/
void Menu::chargementGraph()
{
    std::string nom_fichier;
    std::ifstream ifs;
    Graph* tampon=nullptr;
    std::cout<<"Entrez le nom du fichier a charger : ";
    std::cin>>nom_fichier;//saisie console
    if (nom_fichier=="oui")
        nom_fichier="graphe_etoile1_topo.txt";
    ifs.open(nom_fichier);//ouverture du fichier
    if(!ifs.is_open())//si le fichier ne s'est pas ouvert
    {
        std::cout<<"Probleme d'ouverture du fichier : "<<nom_fichier<<std::endl;//affichage console
        return;
    }
    try//essai lecture fichier
    {
        tampon=new Graph(ifs);//test ouverture fichier
        if(m_etude)//si non null
            delete m_etude;//supprimer graph
        m_etude=tampon;//graph = au graph lu
    }
    catch(int a)//si probleme de lecture fichier
    {
        if(tampon)//si graphe tout de meme construit
            delete tampon;//le supprimer
        std::cout<<"Verifie le format du fichier : "<<nom_fichier<<std::endl;//message console
    }

}

/**
Chargement pondération du graph
change le poids des aretes
*/

void Menu::chargementPonderation()
{
    std::ifstream ifs;
    std::string nom_fichier;

    std::cout<<"entrer le nom du fichier de ponderation : ";
    std::cin>>nom_fichier;//saisie console

    if (nom_fichier=="oui")
        nom_fichier="graphe_etoile1_Ponderation.txt";

    ifs.open(nom_fichier);//ouverture du fichier
    if(!ifs.is_open())//si le fichier n'est pas ouvert
    {
        std::cout<<"Probleme d'ouverture du fichier : "<<nom_fichier<<std::endl;//message console
        return;
    }

    m_etude->chargementPonderation(nom_fichier);//chargement du fichier de pondération d'un graph
}
