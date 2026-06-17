#ifndef BUSES_H
#define BUSES_H

#include <vector>

#include "bus.h"

using namespace std;

// ====== PROTOTIPOS DE BUSES ======

const char* const* obtenerHorariosCiudad(const char* ciudad,
                                          int& numHorarios);

int obtenerNumHorariosCiudad(const char* ciudad);

const char* obtenerHorarioPorIndice(const char* ciudad,
                                    int indice);

void inicializarBuses(vector<Bus>& buses);

int buscarBusDisponible(vector<Bus>& buses,
                        const char* ciudad,
                        const char* horario,
                        float pesoEnvio);

void actualizarCapacidadBus(vector<Bus>& buses,
                             int indiceBus,
                             float peso,
                             bool agregar,
                             const char* codigoEnvio);

void mostrarBusesDisponibles(const vector<Bus>& buses,
                              const char* ciudad);

void mostrarEstadoBuses(const vector<Bus>& buses);

void mostrarRutasHorarios();

#endif
