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
        int getSize();
};

#endif