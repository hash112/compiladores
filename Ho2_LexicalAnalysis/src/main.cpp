#include <iostream>
#include <string>

#include "../include/automata.hpp"
#include "../include/regex.hpp"
#include "../include/patron.hpp"

using std::cin; using std::cout; using std::endl; using std::string;
using std::getline;

int main(int argc, char *argv[])
{
    int opcion;
    string input;

    Patron *patron;
    Regex *regex;

    do {
        cout << "==========================================" << endl;
        cout << " Autómata Finito Determinista (AFD)" << endl;
        cout << " 1. Validar cadena alfabética [A-Za-z]+" << endl;
        cout << " 2. Validar cadena numérica [0-9]+" << endl;
        cout << " 3. Salir" << endl;
        cout << "==========================================" << endl;
        cout << "Elige una opción: ";
        cin >> opcion;
        cin.ignore();

        if(opcion == 1)
        {
            patron = new Patron("[A-Za-z]+");
            regex = new Alfabeto(patron);
            cout << "Ingresa una cadena alfabética: ";
        }

        else if(opcion == 2)
        {
            patron = new Patron("[0-9]+");
            regex = new Numeros(patron);
            cout << "Ingresa una cadena numérica: ";
        }

        else if(opcion == 3) break;
        else continue;

        Automata *automata = new Automata(regex);
        getline(cin, input);

        if(automata->procesar(input))
        {
            cout << "Resultado: ACEPTADO" << endl;
        }
        else
        {
            cout << "Resultado: RECHAZADO" << endl;
        }

        cout << "Estado final: q" << automata->get_estado_actual() << endl << endl;
        delete automata;

    } while(opcion != 3);

    return 0;
}