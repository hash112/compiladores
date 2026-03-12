#ifndef INSTRUCCION_HPP
#define INSTRUCCION_HPP

#include <string>

using std::string;

class Instruccion
{
    private:
        string nombre;
        int codigo;

    public:
        Instruccion(string _nombre, int _codigo);

};

Instruccion::Instruccion(string _nombre, int _codigo)
{
    nombre = _nombre;
    codigo = _codigo;
}


#endif