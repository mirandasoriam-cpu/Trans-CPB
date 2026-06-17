#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>

#include "archivos.h"
#include "constantes.h"

using namespace std;

// ====== VARIABLE GLOBAL: TOTAL DE ENVIOS ======
extern int totalEnviosRegistrados;

// ====== CARGAR ENVIOS DESDE ARCHIVO CSV ======
vector<Envio> cargarEnvios() {

    vector<Envio> v;

    ifstream f(Arch_envios);

    if (!f) return v;

    string linea;

    // Saltar cabecera
    getline(f, linea);

    while (getline(f, linea)) {

        if (linea.empty()) continue;

        istringstream ss(linea);
        string campo;
        Envio e;

        // codigo
        getline(ss, campo, ',');
        strncpy(e.codigo, campo.c_str(), sizeof(e.codigo) - 1);
        e.codigo[sizeof(e.codigo) - 1] = '\0';

        // remitente.nombre
        getline(ss, campo, ',');
        strncpy(e.remitente.nombre, campo.c_str(), sizeof(e.remitente.nombre) - 1);
        e.remitente.nombre[sizeof(e.remitente.nombre) - 1] = '\0';

        // remitente.ci
        getline(ss, campo, ',');
        strncpy(e.remitente.ci, campo.c_str(), sizeof(e.remitente.ci) - 1);
        e.remitente.ci[sizeof(e.remitente.ci) - 1] = '\0';

        // remitente.telefono
        getline(ss, campo, ',');
        strncpy(e.remitente.telefono, campo.c_str(), sizeof(e.remitente.telefono) - 1);
        e.remitente.telefono[sizeof(e.remitente.telefono) - 1] = '\0';

        // remitente.correo
        getline(ss, campo, ',');
        strncpy(e.remitente.correo, campo.c_str(), sizeof(e.remitente.correo) - 1);
        e.remitente.correo[sizeof(e.remitente.correo) - 1] = '\0';

        // destinatario.nombre
        getline(ss, campo, ',');
        strncpy(e.destinatario.nombre, campo.c_str(), sizeof(e.destinatario.nombre) - 1);
        e.destinatario.nombre[sizeof(e.destinatario.nombre) - 1] = '\0';

        // destinatario.ci
        getline(ss, campo, ',');
        strncpy(e.destinatario.ci, campo.c_str(), sizeof(e.destinatario.ci) - 1);
        e.destinatario.ci[sizeof(e.destinatario.ci) - 1] = '\0';

        // destinatario.telefono
        getline(ss, campo, ',');
        strncpy(e.destinatario.telefono, campo.c_str(), sizeof(e.destinatario.telefono) - 1);
        e.destinatario.telefono[sizeof(e.destinatario.telefono) - 1] = '\0';

        // destinatario.correo
        getline(ss, campo, ',');
        strncpy(e.destinatario.correo, campo.c_str(), sizeof(e.destinatario.correo) - 1);
        e.destinatario.correo[sizeof(e.destinatario.correo) - 1] = '\0';

        // destino
        getline(ss, campo, ',');
        strncpy(e.destino, campo.c_str(), sizeof(e.destino) - 1);
        e.destino[sizeof(e.destino) - 1] = '\0';

        // peso
        getline(ss, campo, ',');
        e.peso = stof(campo);

        // horario
        getline(ss, campo, ',');
        strncpy(e.horario, campo.c_str(), sizeof(e.horario) - 1);
        e.horario[sizeof(e.horario) - 1] = '\0';

        // costoBase
        getline(ss, campo, ',');
        e.costoBase = stof(campo);

        // impuesto
        getline(ss, campo, ',');
        e.impuesto = stof(campo);

        // costoTotal
        getline(ss, campo, ',');
        e.costoTotal = stof(campo);

        v.push_back(e);

        totalEnviosRegistrados++;
    }

    f.close();

    return v;
}

// ====== GUARDAR ENVIOS EN ARCHIVO CSV ======
void guardarEnvios(const vector<Envio>& v) {

    ofstream f(Arch_envios, ios::trunc);

    if (!f) {

        cout << "Error al guardar el archivo" << endl;

        return;
    }

    // Cabecera
    f << "codigo,"
      << "rem_nombre,rem_ci,rem_telefono,rem_correo,"
      << "dest_nombre,dest_ci,dest_telefono,dest_correo,"
      << "destino,peso,horario,costoBase,impuesto,costoTotal\n";

    for (int i = 0; i < (int)v.size(); i++) {

        const Envio& e = v[i];

        f << e.codigo           << ","
          << e.remitente.nombre   << ","
          << e.remitente.ci       << ","
          << e.remitente.telefono << ","
          << e.remitente.correo   << ","
          << e.destinatario.nombre   << ","
          << e.destinatario.ci       << ","
          << e.destinatario.telefono << ","
          << e.destinatario.correo   << ","
          << e.destino        << ","
          << e.peso           << ","
          << e.horario        << ","
          << e.costoBase      << ","
          << e.impuesto       << ","
          << e.costoTotal     << "\n";
    }

    f.close();
}

// ====== CARGAR BUSES DESDE ARCHIVO CSV ======
vector<Bus> cargarBuses() {

    vector<Bus> v;

    ifstream f(Arch_buses);

    if (!f) return v;

    string linea;

    // Saltar cabecera
    getline(f, linea);

    while (getline(f, linea)) {

        if (linea.empty()) continue;

        istringstream ss(linea);
        string campo;
        Bus b;

        // ruta
        getline(ss, campo, ',');
        strncpy(b.ruta, campo.c_str(), sizeof(b.ruta) - 1);
        b.ruta[sizeof(b.ruta) - 1] = '\0';

        // horario
        getline(ss, campo, ',');
        strncpy(b.horario, campo.c_str(), sizeof(b.horario) - 1);
        b.horario[sizeof(b.horario) - 1] = '\0';

        // capacidadTotal
        getline(ss, campo, ',');
        b.capacidadTotal = stof(campo);

        // capacidadUsada
        getline(ss, campo, ',');
        b.capacidadUsada = stof(campo);

        // capacidadRestante
        getline(ss, campo, ',');
        b.capacidadRestante = stof(campo);

        // contadorEnvios
        getline(ss, campo, ',');
        b.contadorEnvios = stoi(campo);

        // envios[100] - guardados como lista separada por '|'
        getline(ss, campo, ',');
        memset(b.envios, 0, sizeof(b.envios));

        if (!campo.empty()) {

            istringstream ssEnvios(campo);
            string valorStr;
            int idx = 0;

            while (getline(ssEnvios, valorStr, '|') && idx < 100) {

                b.envios[idx++] = stoi(valorStr);
            }
        }

        v.push_back(b);
    }

    f.close();

    return v;
}

// ====== GUARDAR BUSES EN ARCHIVO CSV ======
void guardarBuses(const vector<Bus>& v) {

    ofstream f(Arch_buses, ios::trunc);

    if (!f) {

        cout << "Error al guardar archivo de buses" << endl;

        return;
    }

    // Cabecera
    f << "ruta,horario,capacidadTotal,capacidadUsada,capacidadRestante,contadorEnvios,envios\n";

    for (int i = 0; i < (int)v.size(); i++) {

        const Bus& b = v[i];

        f << b.ruta             << ","
          << b.horario          << ","
          << b.capacidadTotal   << ","
          << b.capacidadUsada   << ","
          << b.capacidadRestante << ","
          << b.contadorEnvios   << ",";

        // Guardar arreglo envios[100] como valores separados por '|'
        bool primero = true;

        for (int j = 0; j < 100; j++) {

            if (b.envios[j] != 0) {

                if (!primero) f << "|";

                f << b.envios[j];

                primero = false;
            }
        }

        f << "\n";
    }

    f.close();
}

// ====== INTERCALAR DOS ARCHIVOS CSV DE ENVIOS ======
// Divide envios en manana (<14:00) y tarde (>=14:00),
// los guarda en archivos separados y luego los fusiona
// ordenados por codigo usando intercalacion (merge).

static bool esHorarioManana(const char* horario) {

    // Formato "HH:MM"
    int horas   = (horario[0] - '0') * 10 + (horario[1] - '0');
    int minutos = (horario[3] - '0') * 10 + (horario[4] - '0');

    return (horas * 60 + minutos) < (14 * 60);
}

static void guardarSubconjunto(const vector<Envio>& sub,
                                const char* archivo) {

    ofstream f(archivo, ios::trunc);

    if (!f) {

        cout << "Error al crear " << archivo << "\n";

        return;
    }

    f << "codigo,"
      << "rem_nombre,rem_ci,rem_telefono,rem_correo,"
      << "dest_nombre,dest_ci,dest_telefono,dest_correo,"
      << "destino,peso,horario,costoBase,impuesto,costoTotal\n";

    for (int i = 0; i < (int)sub.size(); i++) {

        const Envio& e = sub[i];

        f << e.codigo              << ","
          << e.remitente.nombre    << ","
          << e.remitente.ci        << ","
          << e.remitente.telefono  << ","
          << e.remitente.correo    << ","
          << e.destinatario.nombre   << ","
          << e.destinatario.ci       << ","
          << e.destinatario.telefono << ","
          << e.destinatario.correo   << ","
          << e.destino     << ","
          << e.peso        << ","
          << e.horario     << ","
          << e.costoBase   << ","
          << e.impuesto    << ","
          << e.costoTotal  << "\n";
    }

    f.close();
}

void intercalarEnvios(vector<Envio>& envios) {

    if (envios.empty()) {

        cout << "No hay envios para intercalar.\n";

        return;
    }

    vector<Envio> manana;
    vector<Envio> tarde;

    for (int i = 0; i < (int)envios.size(); i++) {

        if (esHorarioManana(envios[i].horario)) {

            manana.push_back(envios[i]);

        } else {

            tarde.push_back(envios[i]);
        }
    }

    // Guardar archivos temporales por turno
    guardarSubconjunto(manana, "envios_manana.csv");
    guardarSubconjunto(tarde,  "envios_tarde.csv");

    cout << "Archivos generados:\n";
    cout << "  envios_manana.csv -> " << manana.size() << " envios (antes de las 14:00)\n";
    cout << "  envios_tarde.csv  -> " << tarde.size()  << " envios (14:00 en adelante)\n\n";

    // Ordenar cada grupo por codigo (necesario para merge ordenado)
    for (int i = 0; i < (int)manana.size() - 1; i++) {
        for (int j = 0; j < (int)manana.size() - 1 - i; j++) {
            if (strcmp(manana[j].codigo, manana[j+1].codigo) > 0) {
                Envio tmp = manana[j]; manana[j] = manana[j+1]; manana[j+1] = tmp;
            }
        }
    }

    for (int i = 0; i < (int)tarde.size() - 1; i++) {
        for (int j = 0; j < (int)tarde.size() - 1 - i; j++) {
            if (strcmp(tarde[j].codigo, tarde[j+1].codigo) > 0) {
                Envio tmp = tarde[j]; tarde[j] = tarde[j+1]; tarde[j+1] = tmp;
            }
        }
    }

    // Intercalacion (merge) por codigo
    vector<Envio> fusionados;
    int im = 0, it = 0;

    while (im < (int)manana.size() && it < (int)tarde.size()) {

        if (strcmp(manana[im].codigo, tarde[it].codigo) <= 0) {

            fusionados.push_back(manana[im++]);

        } else {

            fusionados.push_back(tarde[it++]);
        }
    }

    while (im < (int)manana.size()) fusionados.push_back(manana[im++]);
    while (it < (int)tarde.size())  fusionados.push_back(tarde[it++]);

    // Mostrar resultado
    system("cls");

    cout << string(70, '=') << "\n";
    cout << "   RESULTADO DE INTERCALACION: envios_manana + envios_tarde\n";
    cout << string(70, '=') << "\n";

    cout << left
         << setw(15) << "CODIGO"
         << setw(22) << "REMITENTE"
         << setw(12) << "DESTINO"
         << setw(8)  << "HORARIO"
         << setw(8)  << "TURNO"
         << setw(12) << "COSTO" << "\n";

    cout << string(80, '-') << "\n";

    for (int i = 0; i < (int)fusionados.size(); i++) {

        const Envio& e = fusionados[i];
        const char* turno = esHorarioManana(e.horario) ? "Manana" : "Tarde";

        cout << left
             << setw(15) << e.codigo
             << setw(22) << e.remitente.nombre
             << setw(12) << e.destino
             << setw(8)  << e.horario
             << setw(8)  << turno
             << fixed << setprecision(2) << e.costoTotal << " Bs.\n";
    }

    cout << string(80, '-') << "\n";
    cout << "Total intercalados: " << fusionados.size() << " envios\n";
    cout << "  (Manana: " << manana.size() << " | Tarde: " << tarde.size() << ")\n";
    cout << "\nArchivos CSV separados guardados: envios_manana.csv / envios_tarde.csv\n";

    // Guardar resultado intercalado en el archivo principal y actualizar memoria
    envios = fusionados;
    guardarEnvios(envios);

    cout << "Archivo principal actualizado: " << Arch_envios << "\n";
}
