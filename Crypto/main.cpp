#include <iostream>
#include <limits>
#include <string>

using namespace std;

#define nl '\n' //uso esto por comodidad porque el alt en qt agarra otras cosas y no puedo usar el ascii
// |

string cifrarPorCesar(const string& mensaje, int desplazamiento);
string desencriptarCesar(const string& mensaje, int desplazamiento);
int validarEntero();
int validarEnteroPositivo();

int main()
{
    int opcionPrincipal = 0;

    do {
        cout << "============CRYPTO============" << nl;
        cout << "1. Cifrado Cesar" << nl;
        cout << "4. Salir" << nl;
        cout << "Elija una opcion: ";
        opcionPrincipal = validarEntero();

        switch (opcionPrincipal) {
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

            int opcionCesar = 0;

            do {
                cout << "============CIFRADO CESAR============" << nl;
                cout << "1. Encriptar mensaje" << nl;
                cout << "2. Desencriptar mensaje" << nl;
                cout << "3. Salir" << nl;
                cout << "Ingrese una opcion: ";
                opcionCesar = validarEntero();

                switch (opcionCesar) {
                case 1: {
                    string fraseIngresada = "";
                    string fraseEncriptada = "";

                    cout << "Ingrese el mensaje a encriptar: ";
                    getline(cin, fraseIngresada);

                    cout << "Ingrese un numero entero positivo al cual desea desplazar cada letra del mensaje: ";
                    int desplazamiento = validarEnteroPositivo();

                    fraseEncriptada = cifrarPorCesar(fraseIngresada, desplazamiento);

                    cout << "Mensaje encriptado: " << fraseEncriptada << nl;
                    break;
                }
                case 2: {
                    string fraseIngresada = "";
                    string fraseDesencriptada = "";

                    cout << "Ingrese el mensaje a desencriptar: ";
                    getline(cin, fraseIngresada);

                    cout << "Ingrese la constante de desplazamiento: ";
                    int desplazamiento = validarEnteroPositivo();

                    fraseDesencriptada = desencriptarCesar(fraseIngresada, desplazamiento);

                    cout << "Mensaje desencriptado: " << fraseDesencriptada << nl;
                    break;
                }
                case 3:
                    cout << "Regresando al menu principal..." << nl;
                    break;
                default:
                    cout << "Error: opcion no valida, intente de nuevo." << nl;
                }
            } while (opcionCesar != 3);

            break;
        }
        case 4:
            cout << "Saliendo del programa..." << nl;
            break;
        default:
            cout << "Error: numero invalido. Intente de nuevo." << nl;
        }

    } while (opcionPrincipal != 4);

    return 0;
}

string cifrarPorCesar(const string& mensaje, int desplazamiento)
{
    string mensajeEncriptado = "";

    for (size_t i = 0; i < mensaje.length(); i++) {
        int asciiCaracter = (int)mensaje.at(i);

        if (asciiCaracter >= 97 && asciiCaracter <= 122) {
            mensajeEncriptado += (char)(((asciiCaracter + desplazamiento - 97) % 26) + 97);
        } else if (asciiCaracter >= 65 && asciiCaracter <= 90) {
            mensajeEncriptado += (char)(((asciiCaracter + desplazamiento - 65) % 26) + 65);
        } else {
            mensajeEncriptado += (char)asciiCaracter;
        }
    }

    return mensajeEncriptado;
}

string desencriptarCesar(const string& mensaje, int desplazamiento)
{
    string mensajeDesencriptado = "";

    for (size_t i = 0; i < mensaje.length(); i++) {
        int asciiCaracter = (int)mensaje.at(i);

        if (asciiCaracter >= 97 && asciiCaracter <= 122) {
            mensajeDesencriptado += (char)(((asciiCaracter - desplazamiento - 97 + 26) % 26) + 97);
        } else if (asciiCaracter >= 65 && asciiCaracter <= 90) {
            mensajeDesencriptado += (char)(((asciiCaracter - desplazamiento - 65 + 26) % 26) + 65);
        } else {
            mensajeDesencriptado += (char)asciiCaracter;
        }
    }

    return mensajeDesencriptado;
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
