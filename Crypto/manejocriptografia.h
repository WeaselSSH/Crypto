#ifndef MANEJOCRIPTOGRAFIA_H
#define MANEJOCRIPTOGRAFIA_H

#include <string>

using namespace std;

string algoritmoCesar(const string &texto, int desplazamiento, bool encriptar);
string algoritmoXOR(const string &texto, string key, bool encriptar);
string algoritmoVigenere(const string &texto, string key, bool encriptar);

#endif // MANEJOCRIPTOGRAFIA_H
