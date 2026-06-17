#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include <vector>

#include "envio.h"
#include "bus.h"

using namespace std;

// ====== PROTOTIPOS DE ARCHIVOS ======

vector<Envio> cargarEnvios();

void guardarEnvios(const vector<Envio>& v);

vector<Bus> cargarBuses();

void guardarBuses(const vector<Bus>& v);

void intercalarEnvios(vector<Envio>& envios);

#endif
