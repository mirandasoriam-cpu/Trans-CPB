#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "envio.h"
#include "bus.h"
#include "archivos.h"
#include "buses.h"
#include "crud.h"
#include "busqueda.h"
#include "ordenacion.h"
#include "reporte.h"
#include "utilidades.h"
#include "constantes.h"

using namespace std;

// ====== VARIABLE GLOBAL: TOTAL DE ENVIOS ======
int totalEnviosRegistrados = 0;

// ====== FUNCION PRINCIPAL ======
int main() {

    srand(time(nullptr));

    vector<Envio> envios = cargarEnvios();
    vector<Bus>   buses  = cargarBuses();

    inicializarBuses(buses);

    mostrarCaratula();

    cout << "Envios cargados: "       << envios.size()     << endl;
    cout << "Capacidad por bus: "     << CAPACIDAD_MAX_BUS << " kg\n";
    cout << "Peso maximo por envio: " << PESO_MAX_ENVIO     << " kg\n";
    cout << "Impuesto aplicable: 5% por cada kg extra sobre "
         << PESO_LIMITE_IMPUESTO << " kg\n";

    cout << "\nPresione Enter para continuar...";

    cin.get();

    int opcion;

    do {

        mostrarMenu();

        cin >> opcion;

        switch (opcion) {

            case 1:
                agregarEnvio(envios, buses, totalEnviosRegistrados);
                pausa();
                break;

            case 2:
                listarEnvios(envios);
                pausa();
                break;

            case 3:
                buscarPorCodigo(envios);
                pausa();
                break;

            case 4:
                buscarPorDestino(envios);
                pausa();
                break;

            case 5:
                modificarEnvio(envios);
                pausa();
                break;

            case 6:
                eliminarEnvio(envios, buses, totalEnviosRegistrados);
                pausa();
                break;

            case 7:
                ordenarPorCiudad(envios);
                pausa();
                break;

            case 8:
                mostrarEstadoBuses(buses);
                pausa();
                break;

            case 9:
                mostrarRutasHorarios();
                pausa();
                break;

            case 10:
                generarReporte(envios);
                pausa();
                break;

            case 11:
                intercalarEnvios(envios);
                pausa();
                break;

            case 0:
                system("cls");
                mostrarCaratula();

                cout << "Guardando datos...\n";

                guardarEnvios(envios);
                guardarBuses(buses);

                cout << "Datos guardados correctamente.\n";
                cout << "Total de envios registrados: " << envios.size() << endl;
                cout << "\nSaliendo del programa...\n";

                break;

            default:
                cout << "\nOpcion invalida. Intente nuevamente.\n";
                pausa();
                break;
        }

    } while (opcion != 0);

    return 0;
}
