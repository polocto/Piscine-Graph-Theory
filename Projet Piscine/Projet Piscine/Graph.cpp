#include "Graph.h"
#include "Arete.h"
#include "Sommet.h"


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
        m_sommets.push_back(new Sommet(nom,x,y));
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
        m_aretes.push_back(new Arete(m_sommets[s1],m_sommets[s2]));
    }
}

Graph::~Graph()
{

}
