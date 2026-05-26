#include "../include/regex.hpp"
#include <cctype>

using std::isalpha; using std::isdigit;

Regex::Regex(Patron *_patron)
{
    patron = _patron;
}

Regex::~Regex()
{
    delete patron;
    patron = nullptr;
}

Patron *Regex::getPatron()
{
    return patron;
}

bool Regex::es_valido(char)
{
    return false;
}

Alfabeto::Alfabeto(Patron *_patron) : Regex(_patron)
{
}

Alfabeto::~Alfabeto()
{
}

bool Alfabeto::es_valido(char simbolo)
{
    return isalpha(static_cast<unsigned char>(simbolo)) != 0;
}

Numeros::Numeros(Patron *_patron) : Regex(_patron)
{
}

Numeros::~Numeros()
{
}

bool Numeros::es_valido(char simbolo)
{
    return isdigit(static_cast<unsigned char>(simbolo)) != 0;
}