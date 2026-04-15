#include "../include/cu.hpp"
#include "../include/alu.hpp"

#include <iostream>
#include <typeinfo>

#define SEPARADOR "-----------------------------"

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
    cout << "Cargado el programa en memoria." << endl << SEPARADOR << endl;
}

void ControlUnit::run()
{
    cout << "Ejecutando el programa." << endl << SEPARADOR << endl;
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
    if (parametro.empty())
        {
            cout << "No hay parametro." << endl;
            return 'N'; // No hay parámetro
        }
    for (int i = 0; i < 4; i++)
    {
        if (registros[i].nombre == parametro)
        {
            cout << "El parametro " << parametro << " es un registro." << endl;
            return 'R';
        }
    }

    if (parametro[0] == '#')
    {
        cout << "El parametro " << parametro << " es una direccion de memoria." << endl;
        return 'M';
    }

    else
    {
        cout << "El parametro " << parametro << " es un valor inmediato." << endl;
        return 'I';
    }
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
    cout << "Fetch de la direccion " << mar << ": ";
    if(ir != nullptr)
        cout << ir->getNombre() << endl;
    else
        cout << "Valor inmediato " << mbr->valor_entero << endl;

}

void ControlUnit::decode()
{
    parametro1 = ir->getParametro1();
    parametro2 = ir->getParametro2();

    cout << "Decodificando: " << ir->getNombre(); 
    if(!parametro1.empty())
        cout << " " << parametro1;
    if(!parametro2.empty())        cout << ", " << parametro2;
    cout << endl;

    tipoParametro1 = validarParametro(parametro1);
    tipoParametro2 = validarParametro(parametro2);

    cout << endl;
}

int ControlUnit::execute()
{
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
                cout << "Movimiendo del registro " << origen->nombre << " al registro " << destino->nombre << endl;
            }

            if(tipoParametro2 == 'I')
            {
                int origen = stoi(parametro2);
                mov(*destino, origen);
                cout << "Movimiendo el valor inmediato " << origen << " al registro " << destino->nombre << endl;
            }

            if (tipoParametro2 == 'M')
            {
                Memoria *origen = getMemoria(stoi(parametro2.substr(1)));
                mov(*destino, *origen);
                cout << "Movimiendo del valor en memoria " << parametro2 << " al registro " << destino->nombre << endl;
            }
        };
        break;

        case 3:
        {
            int valorp1 = recuperarValorParametro(parametro1, tipoParametro1);
            int valorp2 = recuperarValorParametro(parametro2, tipoParametro2);
            acc = ALU::add(valorp1, valorp2);
            cout << "Sumando " << parametro1 << " y " << parametro2 << ". Resultado almacenado en el acumulador: " << acc << endl;
        };
        break;

        case 4:
        {
            if(tipoParametro1 != 'M')
            {
                cout << "Error: El primer parámetro de STORE debe ser una direccion de memoria." << endl;
                break;
            }
            Memoria *destino = getMemoria(stoi(parametro1.substr(1)));
            store(*destino);
            cout << "Almacenando el valor del acumulador " << acc << " en la direccion de memoria " << parametro1 << endl;
        };
        break;
        case 5: // END
            cout << "Programa terminado." << endl << SEPARADOR << endl;
            return 0;
            break;

        default:
            cout << "Instrucción desconocida." << endl;
            break;
    }
    pc++;
    cout << SEPARADOR << endl;
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

int ControlUnit::recuperarValorParametro(string parametro, char tipoParametro)
{
    if (tipoParametro == 'R')
    {
        Registro *registro = getRegistro(parametro);
        return registro ? registro->valor : 0;
    }
    else if (tipoParametro == 'M')
    {
        Memoria *memoria = getMemoria(stoi(parametro.substr(1)));
        return memoria ? memoria->valor_entero : 0;
    }
    else if (tipoParametro == 'I')
    {
        return stoi(parametro);
    }
    return 0; // Valor por defecto si el tipo es desconocido
}

void ControlUnit::printRegistros()
{
    cout << "Estado de los registros:" << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << registros[i].nombre << ": " << registros[i].valor << endl;
    }
    cout << SEPARADOR << endl;
}

void ControlUnit::printMemoria(int inicio, int fin)
{
    cout << "Estado de la memoria:" << endl;
    for (int i = inicio; i <= fin; i++)
    {
        if (memoria[i].valor != nullptr)
        {
            cout << "Direccion " << i << ": " << memoria[i].valor->getNombre() << endl;
        }
        else
        {
            cout << "Direccion " << i << ": " << memoria[i].valor_entero << endl;
        }
    }
    cout << SEPARADOR << endl;
}