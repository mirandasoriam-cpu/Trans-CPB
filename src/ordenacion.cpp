#include <iostream>
#include <iomanip>
#include <cstring>

#include "ordenacion.h"
#include "archivos.h"
#include "constantes.h"

using namespace std;

// ====== BUBBLE SORT: ORDENAR ENVIOS POR CIUDAD ======
void ordenarPorCiudad(vector<Envio>& envios) {

    if (envios.empty()) {

        cout << "No hay envios para ordenar.\n";

        return;
    }

    int n = (int)envios.size();

    // Bubble Sort por destino; empate se rompe por codigo
    for (int i = 0; i < n - 1; i++) {

        bool intercambio = false;

        for (int j = 0; j < n - 1 - i; j++) {

            int cmp = strcmp(envios[j].destino, envios[j + 1].destino);

            bool debeIntercambiar = false;

            if (cmp > 0) {

                debeIntercambiar = true;

            } else if (cmp == 0) {

                debeIntercambiar = strcmp(envios[j].codigo, envios[j + 1].codigo) > 0;
            }

            if (debeIntercambiar) {

                Envio temp    = envios[j];
                envios[j]     = envios[j + 1];
                envios[j + 1] = temp;

                intercambio = true;
            }
        }

        // Optimizacion: si no hubo intercambio, ya esta ordenado
        if (!intercambio) break;
    }

    guardarEnvios(envios);

    system("cls");

    cout << string(60, '=') << endl;
    cout << "       ENVIOS ORDENADOS POR CIUDAD (Bubble Sort)" << endl;
    cout << string(60, '=') << endl;

    cout << left
         << setw(15) << "CODIGO"
         << setw(25) << "DESTINATARIO"
         << setw(15) << "DESTINO"
         << setw(10) << "PESO"
         << setw(10) << "HORARIO"
         << setw(15) << "COSTO TOTAL" << endl;

    cout << string(90, '-') << endl;

    float pesoTotal  = 0;
    float costoTotal = 0;

    for (int i = 0; i < (int)envios.size(); i++) {

        const Envio& e = envios[i];

        cout << left
             << setw(15) << e.codigo
             << setw(25) << e.destinatario.nombre
             << setw(15) << e.destino
             << setw(10) << e.peso
             << setw(10) << e.horario
             << fixed << setprecision(2) << e.costoTotal << " Bs." << endl;

        pesoTotal  += e.peso;
        costoTotal += e.costoTotal;
    }

    cout << "\n=== RESUMEN ===\n";
    cout << "Total de envios: " << envios.size() << endl;
    cout << "Peso total: "      << pesoTotal     << " kg\n";
    cout << "Costo total: "     << fixed << setprecision(2) << costoTotal << " Bs." << endl;

    cout << "\nNota: Los envios han sido ordenados por ciudad (Bubble Sort) y guardados.\n";
}
