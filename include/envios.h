#ifndef ENVIOS_H
#define ENVIOS_H

#include <vector>

#include "envio.h"
#include "bus.h"

using namespace std;

// ====== PROTOTIPOS DE FUNCIONES AUXILIARES DE ENVIOS ======

void generarCodigo(char* codigo,
                   int totalEnviosRegistrados);

void calcularCostoConImpuesto(Envio& envio,
                               int indiceCiudad);

void mostrarCiudades();

void mostrarHorariosCiudad(const char* ciudad);

void ingresarPersona(Persona& p,
                     const char* rol);

#endif
