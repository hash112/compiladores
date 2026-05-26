#ifndef PATRON_HPP
#define PATRON_HPP

#include <string>

using std::string;

class Patron
{
private:
    string patron;

public:
    Patron(string _patron);
    ~Patron();

    string getPatron();
};


#endif