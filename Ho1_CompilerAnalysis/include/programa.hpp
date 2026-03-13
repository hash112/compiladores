#ifndef PROGRAMA_HPP
#define PROGRAMA_HPP

#include "instruction.hpp"
#include <vector>

using std::vector;

class Programa
{
    private:
        vector<Instruccion> programa;

    public:
        Programa();
        void addInstruccion(int codigo, string nombre, string parametros);
        Instruccion *getInstruccion(int direccion);
};

Programa::Programa(){}

void Programa::addInstruccion(int codigo, string nombre, string parametros)
{
    Instruccion instruccion(codigo, nombre, parametros);
    programa.push_back(instruccion);
}

Instruccion *Programa::getInstruccion(int direccion)
{
    return &programa[direccion];
}

#endif