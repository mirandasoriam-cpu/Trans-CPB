#include <iostream>
#include <iomanip>
#include <cstring>
#include <ctime>

#include "reporte.h"
#include "constantes.h"

using namespace std;

// ====== GENERAR REPORTE COMPLETO ======
void generarReporte(const vector<Envio>& envios) {

    system("cls");

    cout << string(60, '=') << endl;
    cout << "           REPORTE DE ENVIOS" << endl;
    cout << string(60, '=') << endl;

    time_t ahora  = time(0);
    tm*    tiempo = localtime(&ahora);

    cout << "Fecha del reporte: "
         << tiempo->tm_mday << "/"
         << (tiempo->tm_mon + 1) << "/"
         << (tiempo->tm_year + 1900) << endl;

    cout << "Hora del reporte: "
         << tiempo->tm_hour << ":"
         << tiempo->tm_min << endl;

    cout << string(80, '-') << endl;

    if (envios.empty()) {

        cout << "No hay envios registrados para generar reporte.\n";

        return;
    }

    int   totalEnviosReporte    = 0;
    float pesoTotalReporte      = 0;
    float costoBaseTotalReporte = 0;
    float impuestoTotalReporte  = 0;
    float costoTotalReporte     = 0;

    for (int i = 0; i < NUM_CIUDADES; i++) {

        const char* ciudad = CIUDADES_INTERNAS[i];

        cout << "\nCIUDAD: " << ciudad << endl;
        cout << string(40, '-') << endl;

        int   enviosCiudad     = 0;
        float pesoCiudad       = 0;
        float costoBaseCiudad  = 0;
        float impuestoCiudad   = 0;
        float costoTotalCiudad = 0;

        for (int j = 0; j < (int)envios.size(); j++) {

            if (strcmp(envios[j].destino, ciudad) == 0) {

                enviosCiudad++;
                pesoCiudad       += envios[j].peso;
                costoBaseCiudad  += envios[j].costoBase;
                impuestoCiudad   += envios[j].impuesto;
                costoTotalCiudad += envios[j].costoTotal;

                cout << left
                     << setw(15) << envios[j].codigo
                     << setw(25) << envios[j].destinatario.nombre
                     << envios[j].peso << " kg"
                     << fixed << setprecision(2)
                     << "   " << envios[j].costoTotal << " Bs.";

                if (envios[j].impuesto > 0) {

                    cout << " [+" << envios[j].impuesto << " Bs. impuesto]";
                }

                cout << endl;
            }
        }

        if (enviosCiudad == 0) {

            cout << "No hay envios registrados para esta ciudad.\n";

        } else {

            cout << "\nRESUMEN " << ciudad << ":\n";
            cout << "  Envios: "           << enviosCiudad << endl;
            cout << "  Peso total: "       << pesoCiudad   << " kg\n";
            cout << "  Costo base total: " << fixed << setprecision(2) << costoBaseCiudad << " Bs.\n";

            if (impuestoCiudad > 0) {

                cout << "  Impuesto total: " << impuestoCiudad << " Bs.\n";
            }

            cout << "  Costo total: " << costoTotalCiudad << " Bs.\n";
        }

        totalEnviosReporte    += enviosCiudad;
        pesoTotalReporte      += pesoCiudad;
        costoBaseTotalReporte += costoBaseCiudad;
        impuestoTotalReporte  += impuestoCiudad;
        costoTotalReporte     += costoTotalCiudad;

        cout << endl;
    }

    cout << string(80, '=') << endl;
    cout << "RESUMEN GENERAL DEL REPORTE:\n";
    cout << string(40, '-') << endl;
    cout << "Total de envios: "         << totalEnviosReporte << endl;
    cout << "Peso total enviado: "      << pesoTotalReporte   << " kg\n";
    cout << "Costo base total: "        << fixed << setprecision(2) << costoBaseTotalReporte << " Bs.\n";
    cout << "Impuesto total aplicado: " << impuestoTotalReporte << " Bs.\n";
    cout << "Costo total general: "     << costoTotalReporte    << " Bs.\n";
    cout << string(80, '=') << endl;
}
