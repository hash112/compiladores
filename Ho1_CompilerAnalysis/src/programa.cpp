#include "../include/programa.hpp"

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

int Programa::getSize()
{
    return programa.size();
}