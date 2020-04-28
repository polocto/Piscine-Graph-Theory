#include "Graph.h"
#include "Menu.h"

/**Constructeur de menu
initialise le graph � nullptr*/
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
        affichage();//affichage des diff�rentes option du menu
    while(choix());//tant qu'on ne quitte pas

}

/**Affiche les diff�rentes options proposer pour l'etude d'un graphe
son chargement
chargement de pond�ration
calcul de ses diff�rents indices
sa vuln�rabilit�
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
retourn un bool�en:
faux si quitter
sinon vrai*/
bool Menu::choix()
{
    std::string saisie;
    std::cin>>saisie;//saisie utilisateur
    if(!is_int(saisie))//si la saisie n'est pas un nombre entier naturel
        saisie="99";//metre saisie � 99
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
    case 2://Chargement d'une pond�ration pour graph
        chargementPonderation();
        break;
    case 3://calcul affichage et sauvegarde des indices
        calculIndices(m_etude);
        break;
    case 4://Test la vuln�rabilit� du graph
        vulnerabilite();
        break;
    default://si la saisie ne correspond � aucune case
        std::cout<<"Ce choix ne fait pas parti des options ci-dessus."<<std::endl;//message console
    }
    return true;//retourne vrai par default
}
/**
calcul affichage et sauvegarde des indices du graph
*/
void Menu::calculIndices(Graph* graph)
{
    std::ofstream fichier("sauvegarde.txt");
    Svgfile svgout;//fichier svg pour l'affichage
    //svgout.addGrid();
    graph->calc_icd();
    graph->calc_vect_propre();

    graph->calc_icp();
    graph->calc_ici_naif();
    graph->affichage(svgout);//affichage sur fichier svg
    std::cout<<"le graf est "<<graph->k_connexe()<<" conexe(s)"<<std::endl;
    graph->affichageconsole();//affichage console

    if(fichier.is_open())
        graph->sauvegarde(fichier);
    else
        std::cout<<"Sauvegarde impossible"<<std::endl;
}

/**
Chargement du graph
Chargement du graph � paritir d'un fichier dont le nom est � saisir
*/
void Menu::chargementGraph()
{
    std::string nom_fichier;
    std::ifstream ifs;
    Graph* tampon=nullptr;
    std::cout<<"Entrez le nom du fichier a charger : ";
    std::cin>>nom_fichier;//saisie console
    if (nom_fichier=="1")
        nom_fichier="graphe_etoile1_topo.txt";
    if (nom_fichier=="3")
         nom_fichier="graphe_etoile3_topo.txt";
    if (nom_fichier=="5")
        nom_fichier="graphe_cycle5_topo.txt";
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
Chargement pond�ration du graph
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

    m_etude->chargementPonderation(nom_fichier);//chargement du fichier de pond�ration d'un graph
}

/// /////////////////////////////Vulnerabilité

void Menu::affichage_vulnerabilite()const
{
    std::cout<<"MENU VULNERABILITE"<<std::endl;
    std::cout<<"0/Retour au menu 1"<<std::endl;
    std::cout<<"1/Suprimer un element du graphe"<<std::endl;
    std::cout<<"2/Affichage nouveau graphe "<<std::endl;
    std::cout<<"3/Calcule indice nouveau graphe "<<std::endl;
    std::cout<<"4/Annalyse modification du changement"<<std::endl;
}
void Menu::vulnerabilite()
{
    Graph* etude2=nullptr;
    Graph* tampon=m_etude;
    std::string saisie;

    Svgfile svgout;

    bool stay=true;
    while(stay)
    {
    affichage_vulnerabilite();
    std::cin>>saisie;
    switch(std::stoi(saisie))
    {
    case 0://Quitter
        stay=false;
        if(etude2)//si graph n'est pa null
            delete etude2;
        break;
    case 1://Suppretion d'un element du graph
        tampon->affichageconsole();
        etude2=tampon->Supression_element();
        tampon=etude2;
        break;
    case 2://Affichage du nouveau graph
        if (etude2)
        {
            etude2->affichage(svgout);
            etude2->affichageconsole();
        }
        break;
    case 3://calcule des indicateur pour le nouveau graphe
        if (etude2)
          calculIndices(etude2);
        break;
    case 4://Annalyse des modification

        break;
    default://si la saisie ne correspond � aucune case
        std::cout<<"Ce choix ne fait pas parti des options ci-dessus."<<std::endl;//message console
    }
    }
}


