#include <iostream>
#include <limits>
#include <string>

using namespace std;

#define nl '\n' //uso esto por comodidad porque el alt en qt agarra otras cosas y no puedo usar el ascii
// |

char cifrarPorCesar(int asciiCaracter, int desplazamiento);
int validarEntero();
int validarEnteroPositivo();

int main()
{
    int opcion = 0;
    do {
        cout << "============CRYPTO============" << nl;
        cout << "1. Cifrado Cesar" << nl;
        cout << "4. Salir" << nl;
        cout << "Elija una opcion: ";
        opcion = validarEntero();

        switch (opcion) {
        case 1: {
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
             */

            string fraseIngresada = "";
            string fraseEncriptada = "";

            cout << "============CIFRADO CESAR============" << nl;
            cout << "Ingrese el mensaje a encriptar: ";
            getline(cin, fraseIngresada);

            cout << "Ingrese un numero entero positivo al cual desea desplazar cada letra del mensaje: ";
            int desplazamiento = validarEnteroPositivo();

            for (size_t i = 0; i < fraseIngresada.length(); i++) {
                int asciiCaracterEvaluar = (int) fraseIngresada.at(i);
                char caracterEncriptado = cifrarPorCesar(asciiCaracterEvaluar, desplazamiento);

                fraseEncriptada += caracterEncriptado;
            }

            cout << "Mensaje encriptado: " << fraseEncriptada << nl;
            break;
        }
        case 4:
            break;
        default:
            cout << "Error: numero invalido. Intente de nuevo." << nl;
        }

    } while (opcion != 4);

    return 0;
}

char cifrarPorCesar(int asciiCaracter, int desplazamiento) {
    if (asciiCaracter >= 97 && asciiCaracter <= 122) {
        return (char) (((asciiCaracter - 97 + desplazamiento) % 26) + 97);
    } else if (asciiCaracter >= 65 && asciiCaracter <= 90) {
        return (char) (((asciiCaracter - 65 + desplazamiento) % 26) + 65);
    } else {
        return (char) asciiCaracter;
    }
}

int validarEntero()
{
    int numero = 0;

    while (!(cin >> numero)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida. Ingrese un numero entero: ";
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return numero;
}

int validarEnteroPositivo()
{
    int numero = -1;

    do {
        numero = validarEntero();
        if (numero <= 0) {
            cout << "Error: ingrese un numero entero positivo: ";
        }
    } while (numero <= 0);

    return numero;
}
