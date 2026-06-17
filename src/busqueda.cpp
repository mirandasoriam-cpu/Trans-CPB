#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>

#include "busqueda.h"
#include "envios.h"
#include "constantes.h"

using namespace std;

// ====== LISTAR TODOS LOS ENVIOS ======
void listarEnvios(const vector<Envio>& envios) {

    system("cls");

    cout << string(60, '=') << endl;
    cout << "     LISTA DE ENVIOS (ORDENADO POR CODIGO)" << endl;
    cout << string(60, '=') << endl;

    if (envios.empty()) {

        cout << "No hay envios registrados.\n";

        return;
    }

    vector<Envio> enviosOrdenados = envios;

    sort(enviosOrdenados.begin(), enviosOrdenados.end(),

        [](const Envio& a, const Envio& b) {

            return strcmp(a.codigo, b.codigo) < 0;
        }
    );

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

    for (int i = 0; i < (int)enviosOrdenados.size(); i++) {

        const Envio& e = enviosOrdenados[i];

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
}

// ====== BUSCAR ENVIO POR CODIGO ======
void buscarPorCodigo(const vector<Envio>& envios) {

    system("cls");

    cout << "===== BUSCAR ENVIO POR CODIGO (Ano/Mes/Dia-#Envio) =====\n";

    if (envios.empty()) {

        cout << "No hay envios registrados.\n";

        return;
    }

    char codigo[20];

    cout << "Ingrese codigo de envio (ej: 20251211-001): ";

    cin >> codigo;

    bool encontrado = false;

    for (int i = 0; i < (int)envios.size(); i++) {

        if (strcmp(envios[i].codigo, codigo) == 0) {

            encontrado = true;

            const Envio& e = envios[i];

            cout << "\n=== DATOS DEL ENVIO ===\n";
            cout << "Codigo: " << e.codigo << endl;

            cout << "\n=== Remitente ===\n";
            cout << "Nombre: "   << e.remitente.nombre   << endl;

            if (strlen(e.remitente.ci) > 0)
                cout << "CI: " << e.remitente.ci << endl;

            cout << "Telefono: " << e.remitente.telefono << endl;

            if (strlen(e.remitente.correo) > 0)
                cout << "Correo: " << e.remitente.correo << endl;

            cout << "\n=== Destinatario ===\n";
            cout << "Nombre: "   << e.destinatario.nombre   << endl;

            if (strlen(e.destinatario.ci) > 0)
                cout << "CI: " << e.destinatario.ci << endl;

            cout << "Telefono: " << e.destinatario.telefono << endl;

            if (strlen(e.destinatario.correo) > 0)
                cout << "Correo: " << e.destinatario.correo << endl;

            cout << "\n=== DETALLES DEL ENVIO ===\n";
            cout << "Destino: " << e.destino  << endl;
            cout << "Peso: "    << e.peso     << " kg" << endl;
            cout << "Horario: " << e.horario  << endl;

            cout << fixed << setprecision(2);
            cout << "Costo base: Bs. " << e.costoBase << endl;

            if (e.impuesto > 0) {

                cout << "Impuesto: Bs. " << e.impuesto << endl;
            }

            cout << "COSTO TOTAL: Bs. " << e.costoTotal << endl;

            break;
        }
    }

    if (!encontrado) {

        cout << "\nEnvio no encontrado.\n";
    }
}

// ====== BUSCAR ENVIOS POR DESTINO ======
void buscarPorDestino(const vector<Envio>& envios) {

    system("cls");

    cout << string(60, '=') << endl;
    cout << "         BUSCAR ENVIOS POR DESTINO" << endl;
    cout << string(60, '=') << endl;

    if (envios.empty()) {

        cout << "No hay envios registrados.\n";

        return;
    }

    mostrarCiudades();

    int opcion;

    cout << "Seleccione ciudad (1-" << NUM_CIUDADES << "): ";

    cin >> opcion;

    if (opcion < 1 || opcion > NUM_CIUDADES) {

        cout << "Opcion invalida.\n";

        return;
    }

    char ciudadBuscada[30];

    strcpy(ciudadBuscada, CIUDADES_INTERNAS[opcion - 1]);

    cout << "\n=== ENVIOS A " << ciudadBuscada << " ===\n";

    int   contador   = 0;
    float pesoTotal  = 0;
    float costoTotal = 0;

    for (int i = 0; i < (int)envios.size(); i++) {

        if (strcmp(envios[i].destino, ciudadBuscada) == 0) {

            contador++;
            pesoTotal  += envios[i].peso;
            costoTotal += envios[i].costoTotal;

            cout << "\nEnvio #" << contador << ":\n";
            cout << "Codigo: "       << envios[i].codigo              << endl;
            cout << "Destinatario: " << envios[i].destinatario.nombre << endl;
            cout << "Horario: "      << envios[i].horario             << endl;
            cout << "Peso: "         << envios[i].peso                << " kg" << endl;
            cout << "Costo: Bs. "    << envios[i].costoTotal          << endl;
        }
    }

    if (contador == 0) {

        cout << "No hay envios a " << ciudadBuscada << ".\n";

    } else {

        float costoPromedio = costoTotal / contador;

        cout << "\n=== RESUMEN PARA " << ciudadBuscada << " ===\n";
        cout << "Total envios: "   << contador  << endl;
        cout << "Peso total: "     << pesoTotal << " kg\n";
        cout << "Costo total: "    << fixed << setprecision(2) << costoTotal    << " Bs." << endl;
        cout << "Costo promedio: " << fixed << setprecision(2) << costoPromedio << " Bs." << endl;
    }
}
