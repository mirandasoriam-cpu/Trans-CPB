#ifndef CRUD_H
#define CRUD_H

#include <vector>

#include "envio.h"
#include "bus.h"

using namespace std;

// ====== PROTOTIPOS DE CRUD ======

void agregarEnvio(vector<Envio>& envios,
                  vector<Bus>& buses,
                  int& totalEnviosRegistrados);

void modificarEnvio(vector<Envio>& envios);

void eliminarEnvio(vector<Envio>& envios,
                   vector<Bus>& buses,
                   int& totalEnviosRegistrados);

#endif
