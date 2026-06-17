#ifndef SEEDING_H
#define SEEDING_H

/*
 * Modulo: seeding.h
 * Proposito: Carga automatica de datos de prueba al iniciar el sistema
 *            si el archivo de envios esta vacio o no existe.
 * Parametros de entrada: vector de envios por referencia, vector de buses por referencia
 * Retorno: void (modifica los vectores y guarda en CSV)
 */

#include <vector>
#include "../include/envio.h"
#include "../include/bus.h"

using namespace std;

// ====== VERIFICAR SI SE NECESITA SEEDING ======
// Retorna true si el archivo de datos esta vacio o tiene menos de 10 registros
bool necesitaSeeding(const vector<Envio>& envios);

// ====== CARGAR DATOS DE PRUEBA ======
// Inserta 10 envios de prueba realistas para permitir probar
// ordenacion, busqueda binaria y reportes desde el primer arranque
void cargarDatosPrueba(vector<Envio>& envios,
                        vector<Bus>& buses,
                        int& totalEnviosRegistrados);

#endif
