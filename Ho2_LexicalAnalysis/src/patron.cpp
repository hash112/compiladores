#include <string>
#include "../include/patron.hpp"

using std::string;

Patron::Patron(string _patron)
{
    patron = _patron;
}

Patron::~Patron()
{
}

string Patron::getPatron()
{
    return patron;
}