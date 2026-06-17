/*
 * Modulo: ordenacion_comparativa.cpp
 * Proposito: Implementa Bubble Sort optimizado e Intercalacion (Merge Sort),
 *            ambos con contadores de comparaciones e intercambios.
 *            Al finalizar genera un reporte indicando cual metodo fue mas eficiente.
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>

#include "../include/ordenacion_comparativa.h"
#include "../include/archivos.h"
#include "../include/constantes.h"

using namespace std;

// ====== BUBBLE SORT OPTIMIZADO CON METRICAS ======
// Proposito: Ordena por ciudad (y codigo como desempate) contando cada
//            comparacion e intercambio para medir eficiencia.
// Parametros: copia - vector por valor (no modifica el original),
//             comparaciones e intercambios por referencia (retorno multiple)
void bubbleSortConMetricas(vector<Envio> copia,
                            int& comparaciones,
                            int& intercambios) {

    comparaciones = 0;
    intercambios  = 0;

    int n = (int)copia.size();
    bool huboIntercambio;

    for (int i = 0; i < n - 1; i++) {

        huboIntercambio = false;

        for (int j = 0; j < n - 1 - i; j++) {

            comparaciones++;

            int cmp = strcmp(copia[j].destino, copia[j + 1].destino);

            if (cmp == 0) {
                cmp = strcmp(copia[j].codigo, copia[j + 1].codigo);
            }

            if (cmp > 0) {

                Envio tmp      = copia[j];
                copia[j]       = copia[j + 1];
                copia[j + 1]   = tmp;

                intercambios++;
                huboIntercambio = true;
            }
        }

        // Optimizacion: si no hubo intercambio en toda la pasada, ya esta ordenado
        if (!huboIntercambio) break;
    }
}

// ====== FUSION DE DOS MITADES (auxiliar de Merge Sort) ======
// Proposito: Combina dos subarreglos ya ordenados en uno unico ordenado.
// Parametros: v (vector), inicio, medio, fin (indices del rango),
//             comparaciones e intercambios por referencia
static void fusionar(vector<Envio>& v,
                     int inicio,
                     int medio,
                     int fin,
                     int& comparaciones,
                     int& intercambios) {

    vector<Envio> izq(v.begin() + inicio, v.begin() + medio + 1);
    vector<Envio> der(v.begin() + medio + 1, v.begin() + fin + 1);

    int i = 0, j = 0, k = inicio;

    while (i < (int)izq.size() && j < (int)der.size()) {

        comparaciones++;

        int cmp = strcmp(izq[i].destino, der[j].destino);

        if (cmp == 0) {
            cmp = strcmp(izq[i].codigo, der[j].codigo);
        }

        if (cmp <= 0) {

            v[k++] = izq[i++];

        } else {

            v[k++] = der[j++];
            intercambios++;  // cada vez que un elemento de la derecha "salta" sobre los de la izquierda
        }
    }

    while (i < (int)izq.size()) { v[k++] = izq[i++]; }
    while (j < (int)der.size())  { v[k++] = der[j++]; }
}

// ====== INTERCALACION / MERGE SORT RECURSIVO CON METRICAS ======
// Proposito: Divide el vector en mitades, ordena cada mitad recursivamente
//            y las fusiona. Cuenta comparaciones e intercambios totales.
// Parametros: v por referencia, inicio y fin del rango actual,
//             comparaciones e intercambios por referencia (retorno multiple)
void mergeSortConMetricas(vector<Envio>& v,
                           int inicio,
                           int fin,
                           int& comparaciones,
                           int& intercambios) {

    // Caso base: un solo elemento ya esta ordenado
    if (inicio >= fin) return;

    int medio = inicio + (fin - inicio) / 2;

    // Caso recursivo: ordenar mitad izquierda y mitad derecha
    mergeSortConMetricas(v, inicio, medio, comparaciones, intercambios);
    mergeSortConMetricas(v, medio + 1, fin, comparaciones, intercambios);

    // Fusionar las dos mitades ordenadas
    fusionar(v, inicio, medio, fin, comparaciones, intercambios);
}

// ====== MENU COMPARATIVO DE ORDENACION ======
// Proposito: Ejecuta Bubble Sort e Intercalacion sobre copias del mismo vector,
//            muestra las metricas de cada uno y determina cual fue mas eficiente.
// Parametros: envios por referencia (se actualiza con el vector ordenado por Merge Sort)
void menuOrdenacionComparativa(vector<Envio>& envios) {

    system("cls");

    cout << string(65, '=') << "\n";
    cout << "   COMPARACION DE ALGORITMOS DE ORDENACION\n";
    cout << "   (Bubble Sort Optimizado vs Intercalacion / Merge Sort)\n";
    cout << string(65, '=') << "\n";

    if (envios.empty()) {

        cout << "No hay envios para ordenar.\n";
        return;
    }

    int n = (int)envios.size();

    cout << "Conjunto de datos: " << n << " envios\n";
    cout << "Criterio de orden: Ciudad destino (desempate: codigo)\n\n";

    // ---- Ejecutar Bubble Sort sobre copia ----
    int cmpBubble = 0, intBubble = 0;
    bubbleSortConMetricas(envios, cmpBubble, intBubble);

    // ---- Ejecutar Merge Sort sobre copia ----
    vector<Envio> copiaParaMerge = envios;
    int cmpMerge = 0, intMerge = 0;
    mergeSortConMetricas(copiaParaMerge, 0, n - 1, cmpMerge, intMerge);

    // ---- Reporte comparativo ----
    cout << string(65, '-') << "\n";
    cout << left << setw(32) << "Metrica"
                 << setw(16) << "Bubble Sort"
                 << setw(16) << "Intercalacion" << "\n";
    cout << string(65, '-') << "\n";

    cout << left << setw(32) << "Comparaciones realizadas"
                 << setw(16) << cmpBubble
                 << setw(16) << cmpMerge << "\n";

    cout << left << setw(32) << "Intercambios / movimientos"
                 << setw(16) << intBubble
                 << setw(16) << intMerge << "\n";

    cout << string(65, '-') << "\n";

    // ---- Veredicto ----
    cout << "\n=== CONCLUSION ===\n";

    if (cmpBubble < cmpMerge) {

        cout << "Para este conjunto, Bubble Sort realizo MENOS comparaciones.\n";
        cout << "(Probable causa: el arreglo estaba casi ordenado.)\n";

    } else if (cmpMerge < cmpBubble) {

        cout << "Para este conjunto, Intercalacion realizo MENOS comparaciones.\n";
        cout << "(Merge Sort es mas eficiente en arreglos grandes o desordenados.)\n";

    } else {

        cout << "Ambos algoritmos realizaron la misma cantidad de comparaciones.\n";
    }

    if (intBubble < intMerge) {

        cout << "Bubble Sort realizo menos intercambios/movimientos.\n";

    } else if (intMerge < intBubble) {

        cout << "Intercalacion realizo menos movimientos de elementos.\n";

    } else {

        cout << "Igual cantidad de movimientos en ambos metodos.\n";
    }

    // ---- Aplicar el resultado de Merge Sort al vector principal ----
    envios = copiaParaMerge;
    guardarEnvios(envios);

    cout << "\nVector ordenado con Intercalacion y guardado en " << Arch_envios << "\n";

    // ---- Vista previa ----
    cout << "\n=== PRIMEROS 5 REGISTROS ORDENADOS ===\n";
    cout << left << setw(15) << "CODIGO"
                 << setw(15) << "DESTINO"
                 << setw(10) << "HORARIO"
                 << "COSTO\n";
    cout << string(50, '-') << "\n";

    int mostrar = n < 5 ? n : 5;

    for (int i = 0; i < mostrar; i++) {

        cout << left << setw(15) << envios[i].codigo
                     << setw(15) << envios[i].destino
                     << setw(10) << envios[i].horario
                     << fixed << setprecision(2) << envios[i].costoTotal << " Bs.\n";
    }
}
