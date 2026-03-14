#include "manejocriptografia.h"

#include <string>

using namespace std;

string algoritmoCesar(const string &texto, int desplazamiento, OperacionCriptografica modoCriptografia) {
    /*FUNCIONAMIENTO DEL ALGORITMO
             *
             * Este cifrado consiste en desplazar cada letra de la frase/palabra por un numero entero k el cual es un valor constante
             *
             * Ejemplo:
             * sea k = 3 e i la posicion de una letra en el alfabeto
             * si la letra es 'a', entonces i = 0
             *
             * f(i) = i+k
             * f(i) = 0 + 3
             * f(i) = 3
             *
             * => a pasaria a ser la letra 'd'
             *
             * Intervalo de letras minusculas en ASCII: [97, 122] = ['a','z']
             * Intervalo de letras mayusculas en ASCII: [65,90] = ['A','Z']
             *
             * letras totales en el alfabeto ingles: 26 (52 si se cuentan mayusculas)
             * => intervalo de posiciones [0,25]
             *
             * Esto implica que las operaciones se basan en:
             * C ≡ (i+k) mod 26
             *
             * donde:
             *  C es la posicion de la letra cifrada
             *  i la posicion de la letra original en el alfabeto
             *  k el desplazamiento de la letra
             *
             *  Para desencriptar simplemente se hace que la constante de desplazamiento sea negativa y para que no se salga del rango
             *  del intervalo se le suma 26 a la operacion.
             */
    string textoProcesado = "";
    if (modoCriptografia == OperacionCriptografica::Desencriptar) desplazamiento = -desplazamiento;

    for (size_t i = 0; i < texto.length(); i++) {
        int asciiCaracter = (int)texto.at(i);

        if (asciiCaracter >= 97 && asciiCaracter <= 122) {
            textoProcesado += (char)(((asciiCaracter + desplazamiento - 97 + 26) % 26) + 97);
        } else if (asciiCaracter >= 65 && asciiCaracter <= 90) {
            textoProcesado += (char)(((asciiCaracter + desplazamiento - 65 + 26) % 26) + 65);
        } else {
            textoProcesado += (char)asciiCaracter;
        }
    }

    return textoProcesado;

}
