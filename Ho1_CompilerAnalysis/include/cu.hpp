#ifndef CU_HPP
#define CU_HPP

#include "programa.hpp"
#include "instruction.hpp"

#include <iostream>
#include <string>

using std::cout, std::string;

struct Parametro
{
    string nombre;
    int valor;
};

struct Memoria
{
    Instruccion *valor;
};

struct Registro
{
    string nombre;
    int valor;
};

class ControlUnit
{
    private:
        
        Instruccion *ir;
        Memoria memoria[256];
        Registro registros[4];

    public:
        ControlUnit(Programa *programa);
        void fetch(int mar);
        void decode();
        void execute();
};


#endif