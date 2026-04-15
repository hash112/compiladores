#ifndef INSTRUCCION_H
#define INSTRUCCION_H

#include <string>
using std::string;
class Instruccion
{
    private:
        int codigo;
        string nombre;
        string parametro1;
        string parametro2;
        
    public:
        // Sobrecarga de constructores para diferentes tipos de instrucciones
        Instruccion(int _codigo, string _nombre);
        Instruccion(int _codigo, string _nombre, string _parametro1);
        Instruccion(int _codigo, string _nombre, string _parametro1, string _parametro2);
        int getCodigo();
        string getNombre();
        string getParametro1();
        string getParametro2();
};

#endif