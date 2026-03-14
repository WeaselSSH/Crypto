#ifndef MANEJOARCHIVOS_H
#define MANEJOARCHIVOS_H

#include "manejocriptografia.h"
#include <string>

std::string leerArchivo(const std::string &ruta);
bool escribirArchivo(const std::string &ruta, const std::string &texto);
bool procesarArchivo(const std::string &ruta, AlgoritmoCriptografico algoritmo, OperacionCriptografica operacion,
                     int desplazamiento, const std::string &key);

#endif // MANEJOARCHIVOS_H
