#include <iostream>
#include <iomanip>
#include <cstring>
#include <ctime>
#include <limits>

#include "envios.h"
#include "buses.h"
#include "validaciones.h"
#include "constantes.h"

using namespace std;

// ====== GENERAR CODIGO UNICO DE ENVIO ======
void generarCodigo(char* codigo,
                   int totalEnviosRegistrados) {

    time_t ahora = time(0);

    tm* tiempo = localtime(&ahora);

    int ano              = tiempo->tm_year + 1900;
    int mes              = tiempo->tm_mon + 1;
    int dia              = tiempo->tm_mday;
    int numeroSecuencial = totalEnviosRegistrados + 1;

    sprintf(codigo, "%04d%02d%02d-%03d", ano, mes, dia, numeroSecuencial);
}

// ====== CALCULAR COSTO CON IMPUESTO ======
void calcularCostoConImpuesto(Envio& envio,
                               int indiceCiudad) {

    float precioPorKg = PRECIOS_CIUDAD[indiceCiudad];

    envio.costoBase = precioPorKg * envio.peso;

    if (envio.peso > PESO_LIMITE_IMPUESTO) {

        float kgExtra      = envio.peso - PESO_LIMITE_IMPUESTO;
        float costoKgExtra = precioPorKg * kgExtra;

        envio.impuesto = costoKgExtra * PORCENTAJE_IMPUESTO;

    } else {

        envio.impuesto = 0.0;
    }

    envio.costoTotal = envio.costoBase + envio.impuesto;
}

// ====== MOSTRAR CIUDADES DISPONIBLES ======
void mostrarCiudades() {

    cout << "\n=== CIUDADES DISPONIBLES ===\n";

    for (int i = 0; i < NUM_CIUDADES; i++) {

        cout << "  " << (i + 1) << ". "
             << CIUDADES_INTERNAS[i]
             << " - Precio (por kg): "
             << PRECIOS_CIUDAD[i] << " Bs." << endl;
    }
}

// ====== MOSTRAR HORARIOS DE UNA CIUDAD ======
void mostrarHorariosCiudad(const char* ciudad) {

    int numHorarios;

    const char* const* horarios = obtenerHorariosCiudad(ciudad, numHorarios);

    if (horarios == NULL || numHorarios == 0) {

        cout << "No hay horarios disponibles para " << ciudad << endl;

        return;
    }

    cout << "\n=== HORARIOS DISPONIBLES PARA " << ciudad << " ===\n";

    for (int i = 0; i < numHorarios; i++) {

        cout << "  " << (i + 1) << ". " << horarios[i] << endl;
    }
}

// ====== INGRESAR DATOS DE UNA PERSONA ======
void ingresarPersona(Persona& p,
                     const char* rol) {

    cout << "\n=== Datos del " << rol << " ===\n";

    bool esRemitente = (strcmp(rol, "Remitente") == 0);

    bool nombreValido = false;

    while (!nombreValido) {

        cout << "Nombre completo: ";

        cin.getline(p.nombre, 50);

        if (strlen(p.nombre) == 0) {

            cout << "Error: El nombre no puede estar vacio.\n";

        } else if (!validarSoloLetras(p.nombre)) {

            cout << "Error: El nombre solo puede contener letras y espacios.\n";

        } else {

            nombreValido = true;
        }
    }

    if (esRemitente) {

        bool ciValido = false;

        while (!ciValido) {

            cout << "Carnet de identidad: ";

            cin.getline(p.ci, 12);

            if (strlen(p.ci) == 0) {

                cout << "Error: El CI es obligatorio para el remitente.\n";

            } else if (!validarCI(p.ci)) {

                cout << "Error: CI no valido. (Solamente puede incluir digitos, minimo 7 digitos)\n";

            } else {

                ciValido = true;
            }
        }

    } else {

        cout << "Carnet de identidad (opcional - presione Enter para omitir): ";

        cin.getline(p.ci, 12);

        if (strlen(p.ci) > 0 && !validarCI(p.ci)) {

            cout << "Error: CI no valido.\n";
            cout << "Se guardara sin CI.\n";

            strcpy(p.ci, "");
        }
    }

    bool telefonoValido = false;

    while (!telefonoValido) {

        cout << "Telefono: ";

        cin.getline(p.telefono, 16);

        if (!validarTelefono(p.telefono)) {

            cout << "Error: Telefono no valido (solo digitos, minimo 7, maximo 15).\n";

        } else {

            telefonoValido = true;
        }
    }

    if (esRemitente) {

        bool correoValido = false;

        while (!correoValido) {

            cout << "Correo electronico: ";

            cin.getline(p.correo, 50);

            if (strlen(p.correo) == 0) {

                cout << "Error: El correo es obligatorio para el remitente.\n";

            } else if (!validarCorreo(p.correo)) {

                cout << "Error: Correo no valido. Debe contener @ y terminar en .com\n";

            } else {

                correoValido = true;
            }
        }

    } else {

        cout << "Correo electronico (opcional - presione Enter para omitir): ";

        cin.getline(p.correo, 50);

        if (strlen(p.correo) > 0 && !validarCorreo(p.correo)) {

            cout << "Error: Correo no valido.\n";
            cout << "Se guardara sin correo.\n";

            strcpy(p.correo, "");
        }
    }

    cout << "Datos del " << rol << " ingresados correctamente.\n";
}
