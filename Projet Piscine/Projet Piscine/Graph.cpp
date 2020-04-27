#include "Graph.h"
#include "Arete.h"
#include "Sommet.h"
#include "svgfile.h"

///Constructeur de graph:
///Prend en paramettre le nom du fichier utilisé
/// Crée et initialise les valeur des arretes et sommet en utilisant leur constructeur avec les information du fichier
Graph::Graph(std::ifstream&ifs)
{
    std::string line;
    size_t ot=0;
    if(!std::getline(ifs,line) || !is_int(line))throw(1);
        m_oriente=(bool)std::stoi(line);
    if(!std::getline(ifs,line) || !is_int(line))throw(1);
        ot=(size_t)std::stoi(line);
    if(ifs.fail())throw(1);
    for(size_t i=0;i<ot;i++)
    {
        std::string nom;
        int verrif=0;
        double x=0,y=0;
        if(!std::getline(ifs,line))throw(1);
        std::stringstream iss(line);
        iss>>verrif;
        if(iss.fail()|| verrif!=(int)i)throw(1);
        iss>>nom;
        if(iss.fail())throw(1);
        iss>>x;
        if(iss.fail())throw(1);
        iss>>y;
        if(iss.fail())throw(1);
        m_sommets.push_back(new Sommet(nom,x,y));// Creation d'une sommet avec les parametre du fichier nom, x, y
    }
    if(!std::getline(ifs,line) || !is_int(line))throw(1);
        ot=(size_t)std::stoi(line);
    for(size_t i=0;i<ot;i++)
    {
        std::string line;
        size_t verrif=0, s1=0,s2=0;
        if(!std::getline(ifs,line))throw(1);
        std::stringstream iss(line);
        iss>>verrif;
        if(iss.fail()||verrif!=i)throw(1);
        iss>>s1;
        if(ifs.fail() || s1>m_sommets.size())throw(1);
        iss>>s2;
        if(ifs.fail() || s2>m_sommets.size())throw(1);
        m_aretes.push_back(new Arete(m_sommets[s1],m_sommets[s2]));// Creation d'une Arete a partir des informations du fichier
    }
}

///Destructeur de Graph
///Supression de tout les sommets et de toutes les aretes qui le compose
Graph::~Graph()
{
    for(Sommet* s: m_sommets)
        delete s;
    for(Arete* a : m_aretes)
        delete a;
}

///Chargement de la ponderation
///mise en place d'une ponderation au arete du graph a partir d'un fichier
void Graph::chargementPonderation(std::string nomfichier)
{
    std::ifstream ifs(nomfichier);
	std::string line;
    int taille;

	try
	{
	    if(!ifs.is_open())
            throw("probleme a l'ouverture du fichier:"+nomfichier);

        //recuperation de la taille du graph
        if(std::getline(ifs, line))
        {
            std::stringstream iss(line);
            iss>>taille;
        }
        else
            throw("probleme dans la lecture de la ligne du "+nomfichier+" : fichier corompu");

        if(taille>(int)m_aretes.size())
            throw(nomfichier+" non comforme : trops d'arrete pour la taille du graph // fichier peu etre corompu");

        for (int i=0;i<taille;i++)
        {
            std::getline(ifs, line);
            std::stringstream iss(line);
            int indice;
            iss >> indice;//recuperation de la position de l'arrete dans le vecteur d'arete de graph

            if (iss.fail())
                    throw("probleme dans la lecture de la ligne du "+nomfichier+" : fichier corompu");

            if (indice>taille)
                throw("fichier non comforme : trops d'arrete pour la taille du graph // fichier peu etre corompu");

            m_aretes[indice]->ponderation(iss);//apele de la fonction de arete pour modifier la valeur du poid
        }
	}
	catch (std::string probleme)
	{
	    std::cout<<probleme;
	}
}

/// Affichage du graph au format svg
/// Appel des fonction affichage pour chaque sommets et chaque arretes
void Graph::affichage(Svgfile& svgout)
{
    for (Sommet* S:m_sommets)
        S->affichage(svgout);
    for (Arete* A:m_aretes)
        A->affichage(svgout);
}

///Affichage des parametre du graphe en console
///utiliser pour verification du chargement du graphe
void Graph::affichageconsole()
{
    std::cout<<" Sommet composant le graf :"<<std::endl;
    for( auto s:m_sommets)
    {
        s->affichageconsole();//Appel de l'affichage des paramettre des Sommets
        std::cout<<std::endl;
    }
    std::cout <<" Arete composant le graph : "<<std::endl;
    for (auto s:m_aretes)
    {
        s->affichageconsole();//Appel de l'affichage de aretes qui affiche ces attribues
        std::cout<<std::endl;
    }
}

///Calcule de l'indice de centralité de degrée
void Graph::calc_icd()
{
    for (auto s:m_sommets)
        s->calc_icd();
}
