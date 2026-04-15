#include "../include/instruction.hpp"

Instruccion::Instruccion(int _codigo, string _nombre)
{
    codigo = _codigo;
    nombre = _nombre;
}

Instruccion::Instruccion(int _codigo, string _nombre, string _parametro1)
{
    codigo = _codigo;
    nombre = _nombre;
    parametro1 = _parametro1;
}

Instruccion::Instruccion(int _codigo, string _nombre, string _parametro1, string _parametro2)
{
    codigo = _codigo;
    nombre = _nombre;
    parametro1 = _parametro1;
    parametro2 = _parametro2;
}

int Instruccion::getCodigo()
{
    return codigo;
}

string Instruccion::getNombre()
{
    return nombre;
}

string Instruccion::getParametro1()
{
    return parametro1;
}

string Instruccion::getParametro2()
{
    return parametro2;
}