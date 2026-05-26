#ifndef REGEX_HPP
#define REGEX_HPP

#include "patron.hpp"

using std::string;

class Regex
{
protected:
    Patron *patron;

public:
    Regex(Patron *_patron);
    virtual ~Regex();

    Patron *getPatron();

    virtual bool es_valido(char simbolo);
};

class Alfabeto : public Regex
{
public:
    Alfabeto(Patron *_patron);
    virtual ~Alfabeto();

    virtual bool es_valido(char simbolo) override;
};

class Numeros: public Regex
{
public:
    Numeros(Patron *_patron);
    virtual ~Numeros();

    virtual bool es_valido(char simbolo) override;
};

#endif