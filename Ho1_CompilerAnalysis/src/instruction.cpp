#include "../include/instruction.hpp"

Instruccion::Instruccion(int _codigo, string _nombre, string _parametros)
{
    codigo = _codigo;
    nombre = _nombre;
    parametros = _parametros;
}