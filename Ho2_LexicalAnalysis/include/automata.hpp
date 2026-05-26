#ifndef AUTOMATA_HPP
#define AUTOMATA_HPP

#include "regex.hpp"

#define ESTADO_INICIAL 0
#define ESTADO_FINAL 1

class Automata
{
private:
    int estado_actual;
    Regex *regex;

public:
    Automata(Regex *_regex);
    ~Automata();

    void reiniciar();
    bool transicion(char simbolo);
    bool procesar(const std::string &input);
    bool es_aceptado();
    int get_estado_actual();

};

#endif