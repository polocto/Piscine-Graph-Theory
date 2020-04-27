#include "biblio.h"

bool is_int(const std::string&s)
{
    size_t i=0;
    while(i<s.size() && std::isdigit(s[i]))i++;

    return i && i==s.size();
}
