#ifndef CU_HPP
#define CU_HPP

#include "programa.hpp"
#include "instruction.hpp"

#include <iostream>
#include <string>

using std::cout, std::string;

class ControlUnit
{
    private:
        Instruccion mbr, ir;
        Programa *programa;
        string nombre;
        int codigo;
        int parametros[5];
        int pc = 0;

    public:
        ControlUnit(Programa *_programa);
        void fetch(int mar);
};

ControlUnit::ControlUnit(Programa *_programa)
{
    programa = _programa;
    while(pc != NULL)
    {
        fetch(pc);
    }
}

void ControlUnit::fetch(int mar)
{
    Instruccion *instruccion = static_cast<Instruccion*>(programa->getInstruccion(mar));
    cout << "Fetch de instrucción: " <<
}

#endif