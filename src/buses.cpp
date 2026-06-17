#include <iostream>
#include <iomanip>
#include <cstring>

#include "buses.h"
#include "archivos.h"
#include "constantes.h"

using namespace std;

// ====== OBTENER HORARIOS DE UNA CIUDAD ======
const char* const* obtenerHorariosCiudad(const char* ciudad,
                                          int& numHorarios) {

    if (strcmp(ciudad, "Santa Cruz") == 0) {

        numHorarios = NUM_HORARIOS_SANTACRUZ;
        return HORARIOS_SANTACRUZ;

    } else if (strcmp(ciudad, "Cochabamba") == 0) {

        numHorarios = NUM_HORARIOS_COCHABAMBA;
        return HORARIOS_COCHABAMBA;

    } else if (strcmp(ciudad, "Sucre") == 0) {

        numHorarios = NUM_HORARIOS_SUCRE;
        return HORARIOS_SUCRE;

    } else if (strcmp(ciudad, "Tarija") == 0) {

        numHorarios = NUM_HORARIOS_TARIJA;
        return HORARIOS_TARIJA;

    } else if (strcmp(ciudad, "Cobija") == 0) {

        numHorarios = NUM_HORARIOS_COBIJA;
        return HORARIOS_COBIJA;

    } else if (strcmp(ciudad, "Oruro") == 0) {

        numHorarios = NUM_HORARIOS_ORURO;
        return HORARIOS_ORURO;

    } else if (strcmp(ciudad, "Trinidad") == 0) {

        numHorarios = NUM_HORARIOS_TRINIDAD;
        return HORARIOS_TRINIDAD;
    }

    numHorarios = 0;

    return NULL;
}

// ====== OBTENER NUMERO DE HORARIOS DE UNA CIUDAD ======
int obtenerNumHorariosCiudad(const char* ciudad) {

    int numHorarios;

    obtenerHorariosCiudad(ciudad, numHorarios);

    return numHorarios;
}

// ====== OBTENER HORARIO POR INDICE ======
const char* obtenerHorarioPorIndice(const char* ciudad,
                                    int indice) {

    int numHorarios;

    const char* const* horarios = obtenerHorariosCiudad(ciudad, numHorarios);

    if (horarios != NULL && indice >= 0 && indice < numHorarios) {

        return horarios[indice];
    }

    return NULL;
}

// ====== INICIALIZAR BUSES ======
void inicializarBuses(vector<Bus>& buses) {

    if (!buses.empty()) return;

    for (int i = 0; i < NUM_CIUDADES; i++) {

        int numHorarios;

        const char* const* horarios = obtenerHorariosCiudad(
                                    CIUDADES_INTERNAS[i],
                                    numHorarios
                                );

        for (int j = 0; j < numHorarios; j++) {

            Bus nuevoBus;

            strcpy(nuevoBus.ruta, CIUDADES_INTERNAS[i]);
            strcpy(nuevoBus.horario, horarios[j]);

            nuevoBus.capacidadTotal    = CAPACIDAD_MAX_BUS;
            nuevoBus.capacidadUsada    = 0.0;
            nuevoBus.capacidadRestante = CAPACIDAD_MAX_BUS;
            nuevoBus.contadorEnvios    = 0;

            memset(nuevoBus.envios, 0, sizeof(nuevoBus.envios));

            buses.push_back(nuevoBus);
        }
    }

    guardarBuses(buses);
}

// ====== BUSCAR BUS DISPONIBLE ======
int buscarBusDisponible(vector<Bus>& buses,
                        const char* ciudad,
                        const char* horario,
                        float pesoEnvio) {

    for (int i = 0; i < (int)buses.size(); i++) {

        Bus& bus = buses[i];

        if (strcmp(bus.ruta, ciudad) == 0 &&
            strcmp(bus.horario, horario) == 0 &&
            bus.capacidadRestante >= pesoEnvio) {

            return i;
        }
    }

    return -1;
}

// ====== ACTUALIZAR CAPACIDAD DE BUS ======
void actualizarCapacidadBus(vector<Bus>& buses,
                             int indiceBus,
                             float peso,
                             bool agregar,
                             const char* codigoEnvio = nullptr) {

    if (indiceBus < 0 || indiceBus >= (int)buses.size()) return;

    Bus& bus = buses[indiceBus];

    if (agregar) {

        bus.capacidadUsada    += peso;
        bus.capacidadRestante -= peso;

        if (codigoEnvio && bus.contadorEnvios < 100) {

            bus.contadorEnvios++;
        }

    } else {

        bus.capacidadUsada    -= peso;
        bus.capacidadRestante += peso;

        if (bus.contadorEnvios > 0) {

            bus.contadorEnvios--;
        }
    }

    guardarBuses(buses);
}

// ====== MOSTRAR BUSES DISPONIBLES PARA UNA CIUDAD ======
void mostrarBusesDisponibles(const vector<Bus>& buses,
                              const char* ciudad) {

    cout << "\n=== BUSES DISPONIBLES PARA " << ciudad << " ===\n";

    cout << left
         << setw(15) << "Horario"
         << setw(20) << "Capacidad"
         << setw(20) << "Usado (kg)"
         << setw(20) << "Disponible (kg)" << endl;

    cout << string(75, '-') << endl;

    for (int i = 0; i < (int)buses.size(); i++) {

        if (strcmp(buses[i].ruta, ciudad) == 0) {

            cout << left
                 << setw(15) << buses[i].horario
                 << setw(20) << "10,000 kg"
                 << setw(20) << fixed << setprecision(2) << buses[i].capacidadUsada
                 << setw(20) << buses[i].capacidadRestante << endl;
        }
    }
}

// ====== MOSTRAR ESTADO DE TODOS LOS BUSES ======
void mostrarEstadoBuses(const vector<Bus>& buses) {

    system("cls");

    cout << string(60, '=') << endl;
    cout << "          ESTADO DE LOS BUSES" << endl;
    cout << string(60, '=') << endl;

    cout << left
         << setw(15) << "Ruta"
         << setw(15) << "Horario"
         << setw(15) << "Usado (kg)"
         << setw(20) << "Disponible(kg)"
         << setw(10) << "Envios" << endl;

    cout << string(75, '-') << endl;

    for (int i = 0; i < (int)buses.size(); i++) {

        cout << left
             << setw(15) << buses[i].ruta
             << setw(15) << buses[i].horario
             << setw(15) << fixed << setprecision(2) << buses[i].capacidadUsada
             << setw(20) << buses[i].capacidadRestante
             << setw(10) << buses[i].contadorEnvios << endl;
    }
}

// ====== MOSTRAR RUTAS Y HORARIOS ======
void mostrarRutasHorarios() {

    system("cls");

    cout << "=== RUTAS, HORARIOS Y PRECIOS ===\n\n";

    for (int i = 0; i < NUM_CIUDADES; i++) {

        cout << "RUTA A " << CIUDADES_INTERNAS[i] << ":\n";

        cout << "  Precio (por kg): Bs. "
             << fixed << setprecision(2)
             << PRECIOS_CIUDAD[i] << endl;

        int numHorarios;

        const char* const* horarios = obtenerHorariosCiudad(
                                    CIUDADES_INTERNAS[i],
                                    numHorarios
                                );

        cout << "  Horarios: ";

        for (int j = 0; j < numHorarios; j++) {

            cout << horarios[j];

            if (j < numHorarios - 1) cout << ", ";
        }

        cout << endl << endl;
    }
}
