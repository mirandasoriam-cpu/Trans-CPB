/*
 * Modulo: busqueda_binaria.cpp
 * Proposito: Implementacion de busqueda binaria iterativa y recursiva
 *            sobre el vector de envios ordenado por codigo de guia.
 * Nota: Para que la busqueda binaria funcione correctamente, el vector
 *       debe estar ordenado por codigo antes de llamar estas funciones.
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include <limits>

#include "../include/busqueda_binaria.h"
#include "../include/ordenacion.h"
#include "../include/constantes.h"

using namespace std;

// ====== BUSQUEDA BINARIA ITERATIVA ======
// Proposito: Busca un envio por codigo recorriendo el arreglo de forma iterativa,
//            dividiendo el espacio de busqueda a la mitad en cada paso.
// Parametros: envios - vector ordenado; codigo - clave a buscar;
//             indiceEncontrado - retorna posicion o -1; comparacionesRealizadas - metrica
// Retorno multiple: indiceEncontrado y comparacionesRealizadas por referencia
void busquedaBinariaIterativa(const vector<Envio>& envios,
                               const char* codigo,
                               int& indiceEncontrado,
                               int& comparacionesRealizadas) {

    indiceEncontrado      = -1;
    comparacionesRealizadas = 0;

    int inicio = 0;
    int fin    = (int)envios.size() - 1;

    while (inicio <= fin) {

        int medio = inicio + (fin - inicio) / 2;

        comparacionesRealizadas++;

        int cmp = strcmp(envios[medio].codigo, codigo);

        if (cmp == 0) {

            indiceEncontrado = medio;
            return;

        } else if (cmp < 0) {

            inicio = medio + 1;

        } else {

            fin = medio - 1;
        }
    }
}

// ====== FUNCION AUXILIAR RECURSIVA ======
// Proposito: Implementacion recursiva del algoritmo de busqueda binaria.
//            Caso base: inicio > fin (no encontrado) o envios[medio] == codigo.
//            Caso recursivo: llamarse con la mitad izquierda o derecha.
// Parametros: envios, codigo, inicio, fin (rango actual), llamadas (contador por ref.)
// Retorno: indice encontrado o -1
int busquedaRecursivaAux(const vector<Envio>& envios,
                          const char* codigo,
                          int inicio,
                          int fin,
                          int& llamadas) {

    // Caso base: rango vacio, elemento no encontrado
    if (inicio > fin) return -1;

    int medio = inicio + (fin - inicio) / 2;

    llamadas++;

    int cmp = strcmp(envios[medio].codigo, codigo);

    // Caso base: elemento encontrado
    if (cmp == 0) return medio;

    // Caso recursivo: buscar en la mitad derecha
    if (cmp < 0) {

        return busquedaRecursivaAux(envios, codigo, medio + 1, fin, llamadas);
    }

    // Caso recursivo: buscar en la mitad izquierda
    return busquedaRecursivaAux(envios, codigo, inicio, medio - 1, llamadas);
}

// ====== BUSQUEDA BINARIA RECURSIVA (funcion publica) ======
// Proposito: Envuelve la funcion recursiva auxiliar para uso externo.
// Parametros: envios, codigo, indiceEncontrado y llamadasRealizadas por referencia
// Retorno multiple: indiceEncontrado y llamadasRealizadas por referencia
void busquedaBinariaRecursiva(const vector<Envio>& envios,
                               const char* codigo,
                               int& indiceEncontrado,
                               int& llamadasRealizadas) {

    llamadasRealizadas = 0;

    indiceEncontrado = busquedaRecursivaAux(envios,
                                             codigo,
                                             0,
                                             (int)envios.size() - 1,
                                             llamadasRealizadas);
}

// ====== MOSTRAR DATOS DE UN ENVIO ENCONTRADO ======
static void mostrarEnvioEncontrado(const Envio& e) {

    cout << "\n=== ENVIO ENCONTRADO ===\n";
    cout << "Codigo:        " << e.codigo              << "\n";
    cout << "Remitente:     " << e.remitente.nombre    << "\n";
    cout << "  Telefono:    " << e.remitente.telefono  << "\n";
    cout << "  Correo:      " << e.remitente.correo    << "\n";
    cout << "Destinatario:  " << e.destinatario.nombre << "\n";
    cout << "  Telefono:    " << e.destinatario.telefono << "\n";
    cout << "Destino:       " << e.destino    << "\n";
    cout << "Horario:       " << e.horario    << "\n";
    cout << "Peso:          " << e.peso       << " kg\n";
    cout << fixed << setprecision(2);
    cout << "Costo base:    Bs. " << e.costoBase  << "\n";

    if (e.impuesto > 0) {
        cout << "Impuesto:      Bs. " << e.impuesto << "\n";
    }

    cout << "COSTO TOTAL:   Bs. " << e.costoTotal << "\n";
}

// ====== MENU DE BUSQUEDA BINARIA ======
// Proposito: Presenta ambas variantes de busqueda binaria al usuario,
//            ejecuta la seleccionada, muestra el resultado y las metricas.
// Parametros: envios por referencia (se ordena in-situ antes de buscar)
void menuBusquedaBinaria(vector<Envio>& envios) {

    system("cls");

    cout << string(60, '=') << "\n";
    cout << "        BUSQUEDA BINARIA POR CODIGO DE GUIA\n";
    cout << string(60, '=') << "\n";

    if (envios.empty()) {

        cout << "No hay envios registrados.\n";
        return;
    }

    // Ordenar por codigo antes de buscar (necesario para binaria)
    int n = (int)envios.size();
    bool huboIntercambio;

    for (int i = 0; i < n - 1; i++) {

        huboIntercambio = false;

        for (int j = 0; j < n - 1 - i; j++) {

            if (strcmp(envios[j].codigo, envios[j + 1].codigo) > 0) {

                Envio tmp      = envios[j];
                envios[j]      = envios[j + 1];
                envios[j + 1]  = tmp;

                huboIntercambio = true;
            }
        }

        if (!huboIntercambio) break;
    }

    cout << "El vector esta ordenado por codigo (requisito de busqueda binaria).\n";
    cout << "Total de envios disponibles: " << n << "\n\n";

    char codigo[20];

    cout << "Ingrese el codigo de guia a buscar (ej: 20260612-001): ";
    cin >> codigo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n=== SELECCIONE TIPO DE BUSQUEDA ===\n";
    cout << "1. Busqueda binaria ITERATIVA\n";
    cout << "2. Busqueda binaria RECURSIVA\n";
    cout << "3. Comparar AMBAS\n";
    cout << "0. Cancelar\n";
    cout << "Opcion: ";

    int opcion;
    cin >> opcion;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int idxIter = -1, cmpIter = 0;
    int idxRec  = -1, llamRec  = 0;

    switch (opcion) {

        case 1:
            busquedaBinariaIterativa(envios, codigo, idxIter, cmpIter);

            cout << "\n--- Resultado ITERATIVO ---\n";
            cout << "Comparaciones realizadas: " << cmpIter << "\n";

            if (idxIter != -1) {
                mostrarEnvioEncontrado(envios[idxIter]);
            } else {
                cout << "Envio con codigo \"" << codigo << "\" no encontrado.\n";
            }
            break;

        case 2:
            busquedaBinariaRecursiva(envios, codigo, idxRec, llamRec);

            cout << "\n--- Resultado RECURSIVO ---\n";
            cout << "Llamadas recursivas realizadas: " << llamRec << "\n";

            if (idxRec != -1) {
                mostrarEnvioEncontrado(envios[idxRec]);
            } else {
                cout << "Envio con codigo \"" << codigo << "\" no encontrado.\n";
            }
            break;

        case 3:
            busquedaBinariaIterativa(envios, codigo, idxIter, cmpIter);
            busquedaBinariaRecursiva(envios, codigo, idxRec,  llamRec);

            cout << "\n" << string(55, '-') << "\n";
            cout << "  COMPARACION DE METODOS DE BUSQUEDA BINARIA\n";
            cout << string(55, '-') << "\n";
            cout << left << setw(30) << "Metodo"
                         << setw(15) << "Iteraciones" << "Resultado\n";
            cout << string(55, '-') << "\n";
            cout << left << setw(30) << "Iterativa"
                         << setw(15) << cmpIter
                         << (idxIter != -1 ? "Encontrado" : "No encontrado") << "\n";
            cout << left << setw(30) << "Recursiva"
                         << setw(15) << llamRec
                         << (idxRec  != -1 ? "Encontrado" : "No encontrado") << "\n";
            cout << string(55, '-') << "\n";

            if (cmpIter == llamRec) {
                cout << "Ambos metodos usaron la misma cantidad de pasos.\n";
            } else if (cmpIter < llamRec) {
                cout << "La version ITERATIVA uso menos pasos.\n";
            } else {
                cout << "La version RECURSIVA uso menos pasos.\n";
            }

            cout << "\nNota: En busqueda binaria, iterativa y recursiva\n";
            cout << "realizan exactamente los mismos pasos logicos;\n";
            cout << "la diferencia es la forma de expresarlo en codigo.\n";

            if (idxIter != -1) {
                mostrarEnvioEncontrado(envios[idxIter]);
            } else {
                cout << "\nEnvio con codigo \"" << codigo << "\" no encontrado.\n";
            }
            break;

        case 0:
            return;

        default:
            cout << "Opcion invalida.\n";
            break;
    }
}
