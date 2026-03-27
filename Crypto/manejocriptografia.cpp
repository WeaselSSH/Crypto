#include "manejocriptografia.h"

#include <string>

using namespace std;

string algoritmoCesar(const string &texto, int desplazamiento, OperacionCriptografica modoCriptografia) {
    string textoProcesado = "";

    if (modoCriptografia == OperacionCriptografica::Desencriptar) desplazamiento = -desplazamiento;

    for (size_t i = 0; i < texto.length(); i++) {
        int asciiCaracter = (int)texto.at(i);
        textoProcesado += aplicarDesplazamiento((int) asciiCaracter, desplazamiento);
    }

    return textoProcesado;
}

string algoritmoXOR(const string &texto, const string &key, OperacionCriptografica modoCriptografia)
{
    if (key.empty()) return texto;

    string textoProcesado = "";

    for (size_t i = 0; i < texto.length(); i++) {
        char charEvaluarTexto = texto.at(i);
        char charEvaluarKey = key.at(i % key.length()); // se usa mod por si la key es mas corta

        string binarioCharEvaluarTexto = numeroDecimalABinario((int) charEvaluarTexto);
        string binarioCharEvaluarKey = numeroDecimalABinario((int) charEvaluarKey);

        string binarioResultado = "";

        for (size_t j = 0; j < binarioCharEvaluarTexto.length(); j++) {
            int unidadEvaluarTexto = (int) binarioCharEvaluarTexto.at(j) - '0';
            int unidadEvaluarKey = (int) binarioCharEvaluarKey.at(j) - '0';

            int bitResultante = unidadEvaluarTexto + unidadEvaluarKey - 2*(unidadEvaluarTexto*unidadEvaluarKey);

            binarioResultado += char(bitResultante + '0');
        }

        int numeroDecimalResultante = numeroBinarioADecimal(binarioResultado);

        textoProcesado += (char) numeroDecimalResultante;
    }

    return textoProcesado;
}


string algoritmoVigenere(const string &texto, const string &key, OperacionCriptografica modoCriptografia) {
    if (key.empty()) return texto;

    string textoEncriptado = "";
    size_t indiceKey = 0;

    for (size_t i = 0; i < texto.length(); i++) {
        char charEvaluarTexto = texto.at(i);

        bool esLetra = ((charEvaluarTexto >= 97 && charEvaluarTexto <= 122) || (charEvaluarTexto >= 65 && charEvaluarTexto <= 90));

        if (!esLetra) {
            textoEncriptado += charEvaluarTexto;
            continue;
        }

        char charEvaluarKey = key.at(indiceKey % key.length());
        int desplazamiento = 0;

        bool esMinuscula = charEvaluarKey >= 97 && charEvaluarKey <= 122;
        bool esMayuscula = charEvaluarKey >= 65 && charEvaluarKey <= 90;

        if (esMinuscula) {
            desplazamiento = charEvaluarKey - 97;
        } else if (esMayuscula) {
            desplazamiento = charEvaluarKey - 65;
        } else {
            textoEncriptado += charEvaluarTexto;
            indiceKey++;
            continue;
        }

        if (modoCriptografia == OperacionCriptografica::Desencriptar) {
            desplazamiento = -desplazamiento;
        }

        textoEncriptado += aplicarDesplazamiento((int) charEvaluarTexto, desplazamiento);
        indiceKey++;
    }

    return textoEncriptado;
}

char aplicarDesplazamiento(int asciiCaracter, int desplazamiento) {
    bool esMinuscula = asciiCaracter >= 97 && asciiCaracter <= 122;
    bool esMayuscula = asciiCaracter >= 65 && asciiCaracter <= 90;

    if (esMinuscula) {
        return (char)(((asciiCaracter + desplazamiento - 97 + 26) % 26) + 97);
    } else if (esMayuscula) {
        return (char)(((asciiCaracter + desplazamiento - 65 + 26) % 26) + 65);
    } else {
        return (char)asciiCaracter;
    }
}

string numeroDecimalABinario(int numeroDecimal) {
    string representacionBinaria = "";

    if (numeroDecimal == 0) return "00000000";

    while (numeroDecimal > 0) {
        int residuo = numeroDecimal % 2;
        representacionBinaria = char(residuo + '0') + representacionBinaria; //residuo + '0' es lo mismo que residuo + 48
        numeroDecimal /= 2;
    }

    while (representacionBinaria.length() < 8) { //se completa hasta 8 bits porque el algoritmo está trabajando byte a byte
        representacionBinaria = "0" + representacionBinaria;
    }

    return representacionBinaria;
}

int numeroBinarioADecimal(const string &binario) {
    int numeroDecimal = 0;

    for (size_t i = 0; i < binario.length(); i++) {
        numeroDecimal = numeroDecimal * 2 + (binario.at(i) - '0');
    }

    return numeroDecimal;
}
