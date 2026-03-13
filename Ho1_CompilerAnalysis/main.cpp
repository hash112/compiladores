#include "include/cu.hpp"
#include "include/instruction.hpp"
#include "include/programa.hpp"

void crear_instrucciones(Programa *programa)
{
    programa->addInstruccion(1, "START", "");
    programa->addInstruccion(2, "MOV", "eax, 20");
    programa->addInstruccion(2, "MOV", "ebx, 40");
    programa->addInstruccion(3, "ADD", "eax, ebx");
    programa->addInstruccion(4, "STORE", "10");
    programa->addInstruccion(5, "END", "")
}

int main() 
{
    Programa programa;
    crear_instrucciones(&programa);
    return 0;
}