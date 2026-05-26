#include "../include/automata.hpp"
#include <iostream>

using std::string; using std::cout; using std::endl;

Automata::Automata(Regex *_regex) 
{
    estado_actual = ESTADO_INICIAL;
    regex = _regex;
}

Automata::~Automata() 
{
    delete regex;
    regex = nullptr;
}

void Automata::reiniciar() 
{
    estado_actual = ESTADO_INICIAL;
}

bool Automata::transicion(char simbolo) 
{
    cout << simbolo << endl;
    switch (estado_actual) {
        case ESTADO_INICIAL:
            if (regex->es_valido(simbolo)) {
                estado_actual = ESTADO_FINAL;
                return true;
            }
            return false;

        case ESTADO_FINAL:
            if (regex->es_valido(simbolo)) {
                estado_actual = ESTADO_FINAL;
                return true;
            }
            return false;

        default:
            return false;
    }
}

bool Automata::procesar(const string &input) 
{
    reiniciar();

    if (input.empty()) {
        return false;
    }

    for (size_t i = 0; i < input.length(); i++) {
        if (!transicion(input[i])) {
            return false;
        }
    }

    return es_aceptado();
}

bool Automata::es_aceptado() 
{
    return estado_actual == ESTADO_FINAL;
}

int Automata::get_estado_actual() 
{
    return estado_actual;
}