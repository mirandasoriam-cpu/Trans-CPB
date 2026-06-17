#include <iostream>
#include <iomanip>
#include <cstring>
#include <limits>

#include "crud.h"
#include "envios.h"
#include "archivos.h"
#include "buses.h"
#include "constantes.h"
#include "validaciones.h"
using namespace std;

// ====== AGREGAR NUEVO ENVIO ======
void agregarEnvio(vector<Envio>& envios,
                  vector<Bus>& buses,
                  int& totalEnviosRegistrados) {

    system("cls");

    cout << "=== NUEVO ENVIO ===\n";

    Envio nuevo;

    generarCodigo(nuevo.codigo, totalEnviosRegistrados);

    cout << "Codigo de envio generado: " << nuevo.codigo << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    ingresarPersona(nuevo.remitente, "Remitente");
    ingresarPersona(nuevo.destinatario, "Destinatario");

    bool pesoAceptado      = false;
    int  ciudadSeleccionada = -1;

    while (!pesoAceptado) {

        mostrarCiudades();

        int opcionCiudad;

        do {

            cout << "Seleccione ciudad destino (1-" << NUM_CIUDADES << "): ";

            cin >> opcionCiudad;

            if (opcionCiudad < 1 || opcionCiudad > NUM_CIUDADES) {

                cout << "Opcion invalida. Intente nuevamente.\n";
            }

        } while (opcionCiudad < 1 || opcionCiudad > NUM_CIUDADES);

        strcpy(nuevo.destino, CIUDADES_INTERNAS[opcionCiudad - 1]);

        ciudadSeleccionada = opcionCiudad - 1;

        mostrarHorariosCiudad(nuevo.destino);

        int numHorarios = obtenerNumHorariosCiudad(nuevo.destino);
        int opcionHorario;

        do {

            cout << "Seleccione horario (1-" << numHorarios << "): ";

            cin >> opcionHorario;

            if (opcionHorario < 1 || opcionHorario > numHorarios) {

                cout << "Opcion invalida. Intente nuevamente.\n";
            }

        } while (opcionHorario < 1 || opcionHorario > numHorarios);

        const char* horarioSeleccionado = obtenerHorarioPorIndice(
                                              nuevo.destino,
                                              opcionHorario - 1
                                          );

        if (horarioSeleccionado != NULL) {

            strcpy(nuevo.horario, horarioSeleccionado);

        } else {

            cout << "Error al obtener horario seleccionado.\n";

            return;
        }

        float pesoEnvio;

        cout << "Impuesto aplicable: 5% por cada kg extra sobre "
             << PESO_LIMITE_IMPUESTO << " kg\n";

        cout << "Peso del paquete (kg) [maximo "
             << PESO_MAX_ENVIO << " kg]: ";

        cin >> pesoEnvio;

        if (!validarPeso(pesoEnvio)) {

            cout << "\nError: Peso invalido. Debe ser mayor a 0 y maximo "
                 << PESO_MAX_ENVIO << " kg.\n";
            cout << "Volviendo a seleccion de ciudad...\n\n";

            cin.ignore();

            continue;
        }

        int indiceBus = buscarBusDisponible(
                            buses,
                            nuevo.destino,
                            nuevo.horario,
                            pesoEnvio
                        );

        if (indiceBus == -1) {

            cout << "\nError: No hay buses disponibles con capacidad suficiente.\n";
            cout << "Volviendo a seleccion de ciudad...\n\n";

            cin.ignore();

            continue;
        }

        nuevo.peso   = pesoEnvio;
        pesoAceptado = true;

        calcularCostoConImpuesto(nuevo, ciudadSeleccionada);

        actualizarCapacidadBus(buses, indiceBus, nuevo.peso, true, nuevo.codigo);
    }

    system("cls");

    cout << "=== RESUMEN DEL ENVIO ===\n";
    cout << "Codigo: "       << nuevo.codigo              << endl;
    cout << "Remitente: "    << nuevo.remitente.nombre    << endl;
    cout << "Destinatario: " << nuevo.destinatario.nombre << endl;
    cout << "Destino: "      << nuevo.destino             << endl;
    cout << "Horario: "      << nuevo.horario             << endl;
    cout << "Peso: "         << nuevo.peso << " kg"       << endl;

    cout << fixed << setprecision(2);

    if (nuevo.impuesto > 0) {

        float kgExtra = nuevo.peso - PESO_LIMITE_IMPUESTO;

        cout << "Kilos extra: " << kgExtra << " kg" << endl;
        cout << "Impuesto (5% sobre kilos extra): Bs. " << nuevo.impuesto << endl;
    }

    cout << "Costo: Bs. " << nuevo.costoTotal << endl;

    envios.push_back(nuevo);

    totalEnviosRegistrados++;

    guardarEnvios(envios);

    cout << "\nEnvio registrado exitosamente.\n";
}

// ====== ELIMINAR ENVIO ======
void eliminarEnvio(vector<Envio>& envios,
                   vector<Bus>& buses,
                   int& totalEnviosRegistrados) {

    system("cls");

    cout << "===== ELIMINAR ENVIO (Ano/Mes/Dia-#Envio) =====\n";

    if (envios.empty()) {

        cout << "No hay envios para eliminar.\n";

        return;
    }

    char codigo[20];

    cout << "Ingrese codigo del envio a eliminar (ej: 20251211-001): ";

    cin >> codigo;

    int indice = -1;

    for (int i = 0; i < (int)envios.size(); i++) {

        if (strcmp(envios[i].codigo, codigo) == 0) {

            indice = i;

            break;
        }
    }

    if (indice == -1) {

        cout << "Envio no encontrado.\n";

        return;
    }

    cout << "\nEnvio encontrado:\n";
    cout << "Destinatario: " << envios[indice].destinatario.nombre << endl;
    cout << "Destino: "      << envios[indice].destino             << endl;
    cout << "Horario: "      << envios[indice].horario             << endl;
    cout << "Costo: Bs. "    << envios[indice].costoTotal          << endl;
    cout << "Peso: "         << envios[indice].peso                << " kg" << endl;

    int indiceBus = -1;

    for (int i = 0; i < (int)buses.size(); i++) {

        if (strcmp(buses[i].ruta, envios[indice].destino) == 0 &&
            strcmp(buses[i].horario, envios[indice].horario) == 0) {

            indiceBus = i;

            break;
        }
    }

    if (indiceBus != -1) {

        actualizarCapacidadBus(buses, indiceBus, envios[indice].peso, false, nullptr);
    }

    envios.erase(envios.begin() + indice);

    totalEnviosRegistrados--;

    guardarEnvios(envios);

    cout << "Envio eliminado correctamente.\n";
}

// ====== MODIFICAR ENVIO (telefono/correo remitente; telefono destinatario) ======
void modificarEnvio(vector<Envio>& envios) {

    system("cls");

    cout << "===== MODIFICAR ENVIO =====\n";

    if (envios.empty()) {

        cout << "No hay envios registrados.\n";

        return;
    }

    char codigo[20];

    cout << "Ingrese codigo del envio a modificar (ej: 20251211-001): ";

    cin >> codigo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int indice = -1;

    for (int i = 0; i < (int)envios.size(); i++) {

        if (strcmp(envios[i].codigo, codigo) == 0) {

            indice = i;

            break;
        }
    }

    if (indice == -1) {

        cout << "Envio no encontrado.\n";

        return;
    }

    Envio& e = envios[indice];

    system("cls");

    cout << "=== DATOS ACTUALES DEL ENVIO ===\n";
    cout << "Codigo       : " << e.codigo                << "\n";
    cout << "Remitente    : " << e.remitente.nombre       << "\n";
    cout << "  Telefono   : " << e.remitente.telefono     << "\n";
    cout << "  Correo     : " << e.remitente.correo       << "\n";
    cout << "Destinatario : " << e.destinatario.nombre    << "\n";
    cout << "  Telefono   : " << e.destinatario.telefono  << "\n";
    cout << "Destino      : " << e.destino                << "\n";
    cout << "Horario      : " << e.horario                << "\n";
    cout << "Peso         : " << e.peso        << " kg\n";
    cout << "Costo total  : Bs. " << fixed << setprecision(2) << e.costoTotal << "\n";

    cout << "\n=== CAMPOS MODIFICABLES ===\n";
    cout << "1. Telefono del remitente\n";
    cout << "2. Correo del remitente\n";
    cout << "3. Telefono del destinatario\n";
    cout << "0. Cancelar\n";

    int opcion;

    cout << "Seleccione campo a modificar: ";

    cin >> opcion;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    char nuevoValor[50];
    bool modificado = false;

    switch (opcion) {

        case 1: {

            bool valido = false;

            while (!valido) {

                cout << "Nuevo telefono del remitente: ";
                cin.getline(nuevoValor, 16);

                if (validarTelefono(nuevoValor)) {

                    strncpy(e.remitente.telefono, nuevoValor, sizeof(e.remitente.telefono) - 1);
                    e.remitente.telefono[sizeof(e.remitente.telefono) - 1] = '\0';
                    valido    = true;
                    modificado = true;

                } else {

                    cout << "Error: Telefono invalido (solo digitos, minimo 7, maximo 15).\n";
                }
            }

            break;
        }

        case 2: {

            bool valido = false;

            while (!valido) {

                cout << "Nuevo correo del remitente: ";
                cin.getline(nuevoValor, 50);

                if (validarCorreo(nuevoValor)) {

                    strncpy(e.remitente.correo, nuevoValor, sizeof(e.remitente.correo) - 1);
                    e.remitente.correo[sizeof(e.remitente.correo) - 1] = '\0';
                    valido    = true;
                    modificado = true;

                } else {

                    cout << "Error: Correo invalido. Debe contener @ y terminar en .com\n";
                }
            }

            break;
        }

        case 3: {

            bool valido = false;

            while (!valido) {

                cout << "Nuevo telefono del destinatario: ";
                cin.getline(nuevoValor, 16);

                if (validarTelefono(nuevoValor)) {

                    strncpy(e.destinatario.telefono, nuevoValor, sizeof(e.destinatario.telefono) - 1);
                    e.destinatario.telefono[sizeof(e.destinatario.telefono) - 1] = '\0';
                    valido    = true;
                    modificado = true;

                } else {

                    cout << "Error: Telefono invalido (solo digitos, minimo 7, maximo 15).\n";
                }
            }

            break;
        }

        case 0:
            cout << "Modificacion cancelada.\n";
            return;

        default:
            cout << "Opcion invalida. No se realizaron cambios.\n";
            return;
    }

    if (modificado) {

        guardarEnvios(envios);

        cout << "\nEnvio modificado exitosamente.\n";

        cout << "\n=== DATOS ACTUALIZADOS ===\n";
        cout << "Remitente  Telefono : " << e.remitente.telefono    << "\n";
        cout << "Remitente  Correo   : " << e.remitente.correo      << "\n";
        cout << "Destinatario Telefono: " << e.destinatario.telefono << "\n";
    }
}
