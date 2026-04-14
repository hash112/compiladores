#include "../include/cu.hpp"
#include "../include/alu.hpp"

#include <iostream>
#include <typeinfo>

using std::cout; using std::endl;

ControlUnit::ControlUnit(Programa *programa)
{
    registros[0] = {"eax", 0};
    registros[1] = {"ebx", 0};
    registros[2] = {"ecx", 0};
    registros[3] = {"edx", 0};

    for (int i = 0; i < 256; i++)
    {
        memoria[i].valor = nullptr;
        memoria[i].valor_entero = 0;
    }

    for(int i = 0; i < programa->getSize(); i++)
    {
        Instruccion *instruccion = programa->getInstruccion(i);
        if(instruccion->getCodigo() != 0)
        {
            memoria[i].valor = instruccion;
        } 

        else // Si el código es 0, asumimos que es un valor inmediato y lo almacenamos en valor_entero
        {
            memoria[i].valor_entero = stoi(instruccion->getParametro1());
        }
    }

    pc = 0;
    acc = 0;
    cout << "Cargado el programa en memoria." << endl;
}

void ControlUnit::run()
{
    cout << "Ejecutando el programa." << endl;
    while(true)
    {
        fetch(pc);
        decode();
        if(execute() == 0)
            break;
    }
    return;
}

char ControlUnit::validarParametro(string parametro)
{
    for (int i = 0; i < 4; i++)
    {
        if (registros[i].nombre == parametro)
            return 'R';
    }

    if (parametro[0] == '#')
        return 'M';

    else
        return 'I';
}

Registro* ControlUnit::getRegistro(string nombre)
{
    for (int i = 0; i < 4; i++)
    {
        if (registros[i].nombre == nombre)
            return &registros[i];
    }
    return nullptr;
}

Memoria* ControlUnit::getMemoria(int direccion)
{
    if (direccion >= 0 && direccion < 256)
        return &memoria[direccion];
    return nullptr;
}

void ControlUnit::fetch(int mar)
{
    mbr = &memoria[mar];
    ir = mbr->valor;
    cout << "Fetch: " << ir->getNombre() << endl;
}

void ControlUnit::decode()
{
    parametro1 = ir->getParametro1();
    parametro2 = ir->getParametro2();
    tipoParametro1 = validarParametro(parametro1);
    tipoParametro2 = validarParametro(parametro2);
}

int ControlUnit::execute()
{
    cout << "Execute: " << ir->getNombre() << endl;
    int codigo = ir->getCodigo();
    switch(codigo)
    {
        case 1: // START
            cout << "Programa iniciado." << endl;
            break;
        case 2: // MOV
        {
            if(tipoParametro1 != 'R')
            {
                cout << "Error: El primer parámetro de MOV debe ser un registro." << endl;
                break;
            }
            Registro *destino = getRegistro(parametro1);
            if(tipoParametro2 == 'R')
            {
                Registro *origen = getRegistro(parametro2);
                mov(*destino, *origen);
            }

            if(tipoParametro2 == 'I')
            {
                int origen = stoi(parametro2);
                mov(*destino, origen);
            }

            if (tipoParametro2 == 'M')
            {
                Memoria *origen = getMemoria(stoi(parametro2.substr(1)));
                mov(*destino, *origen);
            }
        };
        break;

        case 3: // ADD
            cout << "ADD " << ir->getParametro1() << ", " << ir->getParametro2() << endl;
            break;
        case 4: // STORE
            cout << "STORE " << ir->getParametro1() << ", " << ir->getParametro2() << endl;
            break;
        case 5: // END
            cout << "Programa terminado." << endl;
            return 0;
            break;

        default:
            cout << "Instrucción desconocida." << endl;
            break;
    }
    pc++;
    return 1;
}

void ControlUnit::mov(Registro &destino, Memoria &origen)
{
    destino.valor = origen.valor_entero; 
}

void ControlUnit::mov(Registro &destino, Registro &origen)
{
    destino.valor = origen.valor;
}

void ControlUnit::mov(Registro &destino, int valor)
{
    destino.valor = valor;
}

void ControlUnit::store(Memoria &destino)
{
    destino.valor_entero = acc;
}