#ifndef MANEJOCRIPTOGRAFIA_H
#define MANEJOCRIPTOGRAFIA_H

#include <string>

enum class OperacionCriptografica {
    Encriptar,
    Desencriptar
};

enum class AlgoritmoCriptografico {
    Cesar,
    XOR,
    Vigenere
};

std::string algoritmoCesar(const std::string &texto, int desplazamiento, OperacionCriptografica modoCriptografia);
std::string algoritmoXOR(const std::string &texto, const std::string &key, OperacionCriptografica modoCriptografia);
std::string algoritmoVigenere(const std::string &texto, const std::string &key, OperacionCriptografica modoCriptografia);

#endif // MANEJOCRIPTOGRAFIA_H
