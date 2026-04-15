#include "include/cu.hpp"
#include "include/instruction.hpp"
#include "include/programa.hpp"

void crear_instrucciones(Programa *programa)
{
    programa->addInstruccion(1, "START");
    programa->addInstruccion(2, "MOV", "eax", "20");
    programa->addInstruccion(2, "MOV", "ebx", "70");
    programa->addInstruccion(3, "ADD", "eax", "ebx");
    programa->addInstruccion(4, "STORE", "#15");
    programa->addInstruccion(2, "MOV", "ecx", "#15");
    programa->addInstruccion(5, "END");
}

int main() 
{
    Programa programa;
    crear_instrucciones(&programa);
    ControlUnit cu(&programa);
    cu.run();
    cu.printRegistros();
    cu.printMemoria(0, 20);
    return 0;
}