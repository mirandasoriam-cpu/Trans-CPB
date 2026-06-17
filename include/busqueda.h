#ifndef BUSQUEDA_H
#define BUSQUEDA_H

#include <vector>

#include "envio.h"

using namespace std;

// ====== PROTOTIPOS DE BUSQUEDA ======

void buscarPorCodigo(const vector<Envio>& envios);

void buscarPorDestino(const vector<Envio>& envios);

void listarEnvios(const vector<Envio>& envios);

#endif
