#ifndef BUSQUEDA_BINARIA_H
#define BUSQUEDA_BINARIA_H

/*
 * Modulo: busqueda_binaria.h
 * Proposito: Prototipos para busqueda binaria iterativa y recursiva
 *            aplicadas al dominio de envios.
 * Parametros de entrada: vector de envios ordenados por codigo, codigo buscado,
 *                        referencias para retornar indice y cantidad de iteraciones.
 * Retorno: void (los resultados se retornan por referencia - retorno multiple)
 */

#include <vector>
#include "../include/envio.h"

using namespace std;

// ====== BUSQUEDA BINARIA ITERATIVA ======
// Parametros: envios (vector ordenado por codigo), codigo (clave de busqueda)
// Retorno multiple por referencia: indiceEncontrado (-1 si no existe),
//                                  comparacionesRealizadas (metrica de eficiencia)
void busquedaBinariaIterativa(const vector<Envio>& envios,
                               const char* codigo,
                               int& indiceEncontrado,
                               int& comparacionesRealizadas);

// ====== BUSQUEDA BINARIA RECURSIVA ======
// Funcion auxiliar recursiva interna
int busquedaRecursivaAux(const vector<Envio>& envios,
                          const char* codigo,
                          int inicio,
                          int fin,
                          int& llamadas);

// Funcion publica que invoca la recursion
void busquedaBinariaRecursiva(const vector<Envio>& envios,
                               const char* codigo,
                               int& indiceEncontrado,
                               int& llamadasRealizadas);

// ====== MENU DE BUSQUEDA BINARIA ======
// Muestra ambas opciones al usuario y compara resultados
void menuBusquedaBinaria(vector<Envio>& envios);

#endif
