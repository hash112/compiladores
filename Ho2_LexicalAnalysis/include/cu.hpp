#ifndef CU_HPP
#define CU_HPP

#include "programa.hpp"
#include "instruction.hpp"

#include <iostream>
#include <string>

using std::cout; using std::string;

struct Parametro
{
    string nombre;
};

struct Memoria
{
    Instruccion *valor;
    int valor_entero;
};

struct Registro
{
    string nombre;
    int valor;
};

class ControlUnit
{
    private:
        // Memoria de instrucciones 
        Memoria memoria[256];
        Registro registros[4];
        
        // Registros internos
        int pc;
        int acc;
        Instruccion *ir;
        Memoria *mbr;

        string parametro1;
        string parametro2;

        char tipoParametro1;
        char tipoParametro2;

    public:
        // Constructor que recibe un programa para cargarlo en memoria
        ControlUnit(Programa *programa);

        // Función principal que ejecuta el programa cargado en memoria
        void run();
        void fetch(int mar);
        void decode();
        int execute();

        // Se encarga de validar el tipo de parámetro (registro, memoria o inmediato)
        char validarParametro(string parametro);

        Registro* getRegistro(string nombre);
        Memoria* getMemoria(int direccion);

        // Funciones para ejecutar instrucciones específicas
        void mov(Registro &destino, Memoria &origen);
        void mov(Registro &destino, Registro &origen);
        void mov(Registro &destino, int valor);
        void store(Memoria &destino);

        int recuperarValorParametro(string parametro, char tipoParametro);

        // Funciones para obtener estados de registros y memoria (para depuración)
        void printRegistros();
        void printMemoria(int inicio, int fin);
};

#endif
