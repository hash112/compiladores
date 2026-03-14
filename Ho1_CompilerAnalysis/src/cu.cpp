#include "../include/cu.hpp"

ControlUnit::ControlUnit(Programa *programa)
{
    registros[0] = {"eax", 0};
    registros[1] = {"ebx", 0};
    registros[2] = {"ecx", 0};
    registros[3] = {"edx", 0};

    for (int i = 0; i < 256; i++)
    {
        memoria[i].valor = nullptr;
    }

    for(int i = 0; i < programa->getSize(); i++)
    {
        memoria[i].valor = programa->getInstruccion(i);
    }
}