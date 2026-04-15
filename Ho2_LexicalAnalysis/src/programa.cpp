#include "../include/programa.hpp"

Programa::Programa(){}

void Programa::addInstruccion(int codigo, string nombre)
{
    Instruccion instruccion(codigo, nombre);
    programa.push_back(instruccion);
}

void Programa::addInstruccion(int codigo, string nombre, string parametro1)
{
    Instruccion instruccion(codigo, nombre, parametro1);
    programa.push_back(instruccion);
}

void Programa::addInstruccion(int codigo, string nombre, string parametro1, string parametro2)
{
    Instruccion instruccion(codigo, nombre, parametro1, parametro2);
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