#include "manejoarchivos.h"

#include <string>
#include <fstream>

using namespace std;

string leerArchivo(const string &ruta) {
    ifstream archivo(ruta, ios::binary); //se usa binario principalmente por el cifrado xor

    if (!archivo.is_open()) return "";

    archivo.seekg(0, ios::end);
    streamsize tamanio = archivo.tellg();

    if (tamanio <= 0) {
        archivo.close();
        return "";
    }

    archivo.seekg(0, ios::beg);
    string contenido(tamanio, '\0');

    if (!archivo.read(&contenido[0], tamanio)) {
        archivo.close();
        return "";
    }

    archivo.close();
    return contenido;
}

bool escribirArchivo(const string &ruta, const string &texto) {
    ofstream archivo(ruta, ios::binary);

    if (!archivo.is_open()) return false;

    archivo.write(texto.c_str(), texto.size());

    archivo.close();
    return true;
}

bool procesarArchivo(const string &ruta, AlgoritmoCriptografico algoritmo, OperacionCriptografica operacion,
                     int desplazamiento, const string &key)
{
    string texto = leerArchivo(ruta);
    if (texto.empty()) return false;

    string textoProcesado = "";

    switch(algoritmo) {
    case AlgoritmoCriptografico::Cesar:
        textoProcesado = algoritmoCesar(texto, desplazamiento, operacion);
        break;
    case AlgoritmoCriptografico::XOR:
        textoProcesado = algoritmoXOR(texto, key, operacion);
        break;
    case AlgoritmoCriptografico::Vigenere:
        textoProcesado = algoritmoVigenere(texto, key, operacion);
        break;
    }

    return escribirArchivo(ruta, textoProcesado);
}
