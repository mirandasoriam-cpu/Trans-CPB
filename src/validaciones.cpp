#include <cstring>
#include <cctype>

#include "validaciones.h"
#include "constantes.h"

using namespace std;

// ====== VALIDAR SOLO LETRAS ======
bool validarSoloLetras(const char* texto) {

    for (int i = 0; texto[i] != '\0'; i++) {

        if (!isalpha(texto[i]) && texto[i] != ' ') {

            return false;
        }
    }

    return strlen(texto) > 0;
}

// ====== VALIDAR CARNET DE IDENTIDAD ======
bool validarCI(const char* ci) {

    if (strlen(ci) == 0) return true;

    int len = strlen(ci);

    if (len >= 7 && len <= 8) {

        for (int i = 0; i < len; i++) {

            if (ci[i] < '0' || ci[i] > '9') return false;
        }

        return true;
    }

    if (len < 9 || len > 11) return false;

    int i;

    for (i = 0; i < len && ci[i] != '-'; i++) {

        if (ci[i] < '0' || ci[i] > '9') return false;
    }

    if (i < 7 || i > 8) return false;

    if (i >= len || ci[i] != '-') return false;

    i++;

    if (len - i != 2) return false;

    char primerCaracter = ci[i];

    if (primerCaracter != '1' && primerCaracter != '2') return false;

    char segundoCaracter = toupper(ci[i + 1]);

    if (primerCaracter == '1') {

        if (segundoCaracter != 'A' && segundoCaracter != 'B' &&
            segundoCaracter != 'C' && segundoCaracter != 'D' &&
            segundoCaracter != 'E') {

            return false;
        }

    } else if (primerCaracter == '2') {

        if (segundoCaracter != 'A' && segundoCaracter != 'B' &&
            segundoCaracter != 'C') {

            return false;
        }
    }

    return true;
}

// ====== VALIDAR TELEFONO ======
bool validarTelefono(const char* telefono) {

    int len = strlen(telefono);

    if (len < 7 || len > 15) return false;

    for (int i = 0; i < len; i++) {

        if (telefono[i] < '0' || telefono[i] > '9') return false;
    }

    return true;
}

// ====== VALIDAR CORREO ======
bool validarCorreo(const char* correo) {

    if (strlen(correo) == 0) return true;

    int len = strlen(correo);

    if (len < 6) return false;

    bool tieneArroba = false;
    int posArroba = -1;

    for (int i = 0; i < len; i++) {

        if (correo[i] == '@') {

            tieneArroba = true;
            posArroba = i;
            break;
        }
    }

    if (!tieneArroba || posArroba == 0 || posArroba == len - 1) return false;

    if (len < 4) return false;

    const char* extension = correo + len - 4;

    return strcmp(extension, ".com") == 0;
}

// ====== VALIDAR PESO ======
bool validarPeso(float peso) {

    return peso > 0 && peso <= PESO_MAX_ENVIO;
}
