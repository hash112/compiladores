#ifndef INSTRUCCION_H
#define INSTRUCCION_H

#include <string>
using std::string;
class Instruccion
{
    private:
        int codigo;
        string nombre;
        string parametros;
        
    public:
        Instruccion(int _codigo, string _nombre, string _parametros);
};

Instruccion::Instruccion(int _codigo, string _nombre, string _parametros)
{
    codigo = _codigo;
    nombre = _nombre;
    parametros = _parametros;
}

#endif