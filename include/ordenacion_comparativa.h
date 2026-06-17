#ifndef ORDENACION_COMPARATIVA_H
#define ORDENACION_COMPARATIVA_H

/*
 * Modulo: ordenacion_comparativa.h
 * Proposito: Compara la eficiencia de Bubble Sort optimizado e Intercalacion (Merge Sort)
 *            contando comparaciones e intercambios en cada algoritmo.
 * Parametros de entrada: vector de envios por referencia
 * Retorno: void (resultados mostrados en consola con reporte comparativo)
 */

#include <vector>
#include "../include/envio.h"

using namespace std;

// ====== BUBBLE SORT CON METRICAS ======
// Ordena el vector por ciudad y cuenta comparaciones e intercambios
// Retorno multiple por referencia: comparaciones e intercambios
void bubbleSortConMetricas(vector<Envio> copia,
                            int& comparaciones,
                            int& intercambios);

// ====== INTERCALACION (MERGE SORT) CON METRICAS ======
// Divide el arreglo, ordena recursivamente y fusiona
// Retorno multiple por referencia: comparaciones e intercambios
void mergeSortConMetricas(vector<Envio>& v,
                           int inicio,
                           int fin,
                           int& comparaciones,
                           int& intercambios);

// ====== MENU COMPARATIVO DE ORDENACION ======
// Ejecuta ambos algoritmos sobre el mismo conjunto de datos,
// muestra las metricas y determina cual fue mas eficiente
void menuOrdenacionComparativa(vector<Envio>& envios);

#endif
