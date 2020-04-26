#include "Graph.h"
#include "Arete.h"
#include "Sommet.h"


Graph::Graph()
{

}

Graph::~Graph()
{

}

void Graph::chargementPonderation(std::string nomfichier)
{
    std::ifstream ifs(nomfichier);
	std::string line;
    int taille;
    int i;
	try
	{
	    if(!ifs.is_open())
            throw("probleme a l'ouverture du fichier:"+nomfichier);

    std::getline(ifs, line);
    std::stringstream iss(line);
    iss>>taille;

    for (i=0;i<taille;i++)
    {
        std::getline(ifs, line);
        std::stringstream iss(line);
        int indice;
        iss >> indice;

        if (iss.fail())
				throw("probleme dans la lecture de la ligne du fichier: fichier corompu");

        m_aretes[indice]->ponderation(iss);
    }
	}
	catch (std::string probleme)
	{
	    std::cout<<probleme;
	}
}
