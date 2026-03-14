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

string algoritmoXOR(const string &texto, const string &key, OperacionCriptografica modoCriptografia)
{
    /* FUNCIONAMIENTO DEL ALGORITMO
     *
     * Tal como indica el nombre, el elemento central del cifrado es el operador XOR (exclusive OR u OR exclusivo). Este operador en terminos de
     * bits lo que hace es tirar 0 si ambos de estos son iguales y 1 si son distintos el uno del otro.
     *
     * En este cifrado, el operador XOR se aplica bit a bit entre cada carácter del texto original y el carácter
     * correspondiente de una llave (key).
     *
     * Esto lo usa el cifrado de la siguiente forma:
     *
     * Supongamos que queremos encriptar el mensaje HOLAMUNDO
     * Entonces lo que se hace es que primero se le pide al usuario una llave (key), la cual es otra palabra.
     * En este caso digamos que la llave ingresada por el usuario es "ADIOSTIERRA"
     *
     * El algoritmo compara cada carácter del texto con el carácter correspondiente de la llave:
     *
     * H con A, O con D, L con I, A con O, etc.
     *
     * Como en este caso la llave es más larga que el texto original, simplemente se utilizan los primeros
     * caracteres necesarios de la llave. Es decir, solo se compara hasta completar la longitud del texto original.
     *
     * para comparar una letra con otra es necesaria pasarla primero a codigo ASCII y luego su representacion binaria. Como los codigos ASCII
     * se encuentran en sistema decimal, es decir, base 10, para pasarlo a binario es necesario hacer lo siguiente:
     *
     * Teniendo en cuenta que el sistema binario es de base 2, cualquier entero no negativo n puede expresarse como:
     *
     * n = sumatoria desde k = 0 hasta m de (b_k * 2^k)
     *
     * donde:
     *
     * - b_k pertenece al conjunto {0,1}
     * - k indica la posición del bit
     * - m es el mayor índice de la representación
     *
     * Ejemplo:
     *
     * n = 8
     *
     * entonces:
     *
     * 8 = 1*2^3 + 0*2^2 + 0*2^1 + 0*2^0
     *
     * Por lo tanto, la representación binaria de 8 es:
     *
     * 1000 base 2
     *
     * En el caso del algoritmo, esto implica que los primeros pasos a hacer son los siguientes:
     *
     * 1. Leer primera letra del texto original
     * 2. Leer primera letra de la llave
     * 3. Castear a int ambas letras (para obtener su codigo ASCII)
     *
     * y luego para ambas letras, sacar su valor binario aplicando lo siguiente:
     *
     * 1. aplicar modulo 2
     * 2. guardar residuo
     * 3. dividirlo entre 2
     * 4. a la division aplicarle modulo 2
     * 5. guardar residuo
     *
     * y asi sucesivamente hasta que la division entre 2 tenga de cociente 0
     * (aqui se juega con truncar datos haciendo todas las divisiones enteras)
     *
     * Los residuos se guardan en una string del primero al ultimo (algo tipo LIFO) y posteriormente ya se puede hacer la operacion XOR
     * bit a bit, haciendo lo siguiente:
     *
     * 1. castear a int el caracter que se evalua de la string de numero binario de ambos
     * 2. hacer la operacion XOR a cada bit
     * 3. guardar el bit resultante
     * 4. asi sucesivamente hasta llegar al utlimo
     * 5. una vez hecho esto se guardan todos los bits en una string nuevamente
     * 6. repetir hasta fin del texto de la representacion binaria.
     *
     * La operacion XOR bit a bit se puede entender algebraicamente como: x+y-2xy, por lo que para este algoritmo se usara esa operacion.
     *
     * Esta logica presentada se debe hacer para cada caracter del texto a encriptar.
     * En caso que el texto original sea mas grande que la llave, entonces a la llave se le agrega mas texto para que coincida con la longitud del
     * texto. Para este algoritmo, el texto extra seria la misma llave, ejemplo:
     *
     * Texto a encriptar: HOLAMUNDO
     * Llave: ADIOS
     *
     * la nueva llave seria ADIOSADIO.
     */

    if (key.empty()) return texto;

    string textoEncriptado = "";

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

        textoEncriptado += (char) numeroDecimalResultante;
    }

    return textoEncriptado;
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
