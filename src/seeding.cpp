/*
 * Modulo: seeding.cpp
 * Proposito: Carga automatica de 10 registros de prueba cuando el sistema
 *            detecta que el archivo de datos esta vacio en la primera ejecucion.
 *            Permite probar busqueda binaria, ordenacion y reportes inmediatamente.
 */

#include <iostream>
#include <cstring>
#include <cstdio>

#include "../include/seeding.h"
#include "../include/archivos.h"
#include "../include/buses.h"
#include "../include/constantes.h"

using namespace std;

// ====== VERIFICAR SI SE NECESITA SEEDING ======
// Proposito: Determina si hay menos de 10 envios cargados.
// Parametros: envios - vector actual
// Retorno: true si hay menos de 10 registros
bool necesitaSeeding(const vector<Envio>& envios) {

    return (int)envios.size() < 10;
}

// ====== HELPER: CONSTRUIR UN ENVIO DE PRUEBA ======
// Proposito: Arma un struct Envio con los datos pasados como parametros.
// Parametros: todos los campos del envio por valor
// Retorno: struct Envio listo para insertar
static Envio construirEnvio(const char* codigo,
                              const char* remNombre, const char* remCI,
                              const char* remTel,    const char* remCorreo,
                              const char* desNombre, const char* desCI,
                              const char* desTel,    const char* desCorreo,
                              const char* destino,   float peso,
                              const char* horario,   int indiceCiudad) {

    Envio e;

    strncpy(e.codigo,                codigo,    sizeof(e.codigo) - 1);
    strncpy(e.remitente.nombre,      remNombre, sizeof(e.remitente.nombre) - 1);
    strncpy(e.remitente.ci,          remCI,     sizeof(e.remitente.ci) - 1);
    strncpy(e.remitente.telefono,    remTel,    sizeof(e.remitente.telefono) - 1);
    strncpy(e.remitente.correo,      remCorreo, sizeof(e.remitente.correo) - 1);
    strncpy(e.destinatario.nombre,   desNombre, sizeof(e.destinatario.nombre) - 1);
    strncpy(e.destinatario.ci,       desCI,     sizeof(e.destinatario.ci) - 1);
    strncpy(e.destinatario.telefono, desTel,    sizeof(e.destinatario.telefono) - 1);
    strncpy(e.destinatario.correo,   desCorreo, sizeof(e.destinatario.correo) - 1);
    strncpy(e.destino,               destino,   sizeof(e.destino) - 1);
    strncpy(e.horario,               horario,   sizeof(e.horario) - 1);

    // Nulls al final
    e.codigo[sizeof(e.codigo)-1]                       = '\0';
    e.remitente.nombre[sizeof(e.remitente.nombre)-1]   = '\0';
    e.remitente.ci[sizeof(e.remitente.ci)-1]           = '\0';
    e.remitente.telefono[sizeof(e.remitente.telefono)-1] = '\0';
    e.remitente.correo[sizeof(e.remitente.correo)-1]   = '\0';
    e.destinatario.nombre[sizeof(e.destinatario.nombre)-1]   = '\0';
    e.destinatario.ci[sizeof(e.destinatario.ci)-1]           = '\0';
    e.destinatario.telefono[sizeof(e.destinatario.telefono)-1] = '\0';
    e.destinatario.correo[sizeof(e.destinatario.correo)-1]   = '\0';
    e.destino[sizeof(e.destino)-1] = '\0';
    e.horario[sizeof(e.horario)-1] = '\0';

    e.peso = peso;

    float precioPorKg = PRECIOS_CIUDAD[indiceCiudad];
    e.costoBase = precioPorKg * peso;

    if (peso > PESO_LIMITE_IMPUESTO) {
        float kgExtra = peso - PESO_LIMITE_IMPUESTO;
        e.impuesto = precioPorKg * kgExtra * PORCENTAJE_IMPUESTO;
    } else {
        e.impuesto = 0.0f;
    }

    e.costoTotal = e.costoBase + e.impuesto;

    return e;
}

// ====== CARGAR DATOS DE PRUEBA ======
// Proposito: Inserta 10 envios de prueba con datos bolivianos reales,
//            cubriendo distintas ciudades, horarios y pesos (con y sin impuesto).
// Parametros: envios y buses por referencia, totalEnviosRegistrados por referencia
void cargarDatosPrueba(vector<Envio>& envios,
                        vector<Bus>& buses,
                        int& totalEnviosRegistrados) {

    cout << "\n[SEEDING] Cargando 10 registros de prueba...\n";

    // 10 envios de prueba  (ciudad, horario y precio deben coincidir con constantes.h)
    // Indices: 0=Santa Cruz, 1=Cochabamba, 2=Sucre, 3=Tarija, 4=Cobija, 6=Oruro, 5=Trinidad

    struct DatoPrueba {
        const char* codigo;
        const char* remNombre; const char* remCI; const char* remTel; const char* remCorreo;
        const char* desNombre; const char* desCI; const char* desTel; const char* desCorreo;
        const char* destino; float peso; const char* horario; int indiceCiudad;
    };

    DatoPrueba datos[10] = {
        {"20260101-001","Carlos Mamani Quispe","7654321","71234567","carlos.mamani@gmail.com",
         "Maria Lopez","8901234","76543210","","Santa Cruz",15.0f,"08:00",0},

        {"20260101-002","Ana Flores Condori","4567890","78901234","ana.flores@hotmail.com",
         "Roberto Gutierrez","","69876543","roberto.g@gmail.com","Cochabamba",8.5f,"07:30",1},

        {"20260101-003","Luis Quispe Torrez","9012345","76549012","lquispe@gmail.com",
         "Carmen Vargas","","78123456","","Sucre",42.0f,"18:00",2},

        {"20260101-004","Sofia Mendoza Alva","3456789","77890123","sofia.m@yahoo.com",
         "Pedro Rojas","5678901","71234890","pedrorojas@gmail.com","Tarija",5.0f,"14:00",3},

        {"20260101-005","Jorge Aguilar Nina","6789012","79012345","jaguilar@gmail.com",
         "Lucia Blanco","","77654321","","Cochabamba",75.0f,"10:00",1},

        {"20260101-006","Patricia Choque Ramos","1234567","74561234","pchoque@gmail.com",
         "Eduardo Salinas","2345678","73456789","","Santa Cruz",20.0f,"19:00",0},

        {"20260101-007","Marco Villca Layme","5678901","72345678","mvillca@gmail.com",
         "Rosa Soria","","76789012","","Oruro",10.0f,"07:30",6},

        {"20260101-008","Elena Apaza Cruz","8901234","75678901","eapaza@gmail.com",
         "Gabriel Torres","9876543","74567890","gtorres@gmail.com","Cobija",3.5f,"15:00",4},

        {"20260101-009","Hugo Callisaya Lima","2345678","71122334","hcallisaya@gmail.com",
         "Isabel Mamani","","73344556","","Cochabamba",55.0f,"21:00",1},

        {"20260101-010","Beatriz Condori Poma","4321098","78877665","beatriz.c@gmail.com",
         "Raul Herrera","6543210","72211334","rherrera@gmail.com","Santa Cruz",30.0f,"21:00",0}
    };

    for (int i = 0; i < 10; i++) {

        Envio e = construirEnvio(
            datos[i].codigo,
            datos[i].remNombre, datos[i].remCI, datos[i].remTel, datos[i].remCorreo,
            datos[i].desNombre, datos[i].desCI, datos[i].desTel, datos[i].desCorreo,
            datos[i].destino,   datos[i].peso,  datos[i].horario, datos[i].indiceCiudad
        );

        // Asignar al bus correspondiente
        int indiceBus = buscarBusDisponible(buses, e.destino, e.horario, e.peso);

        if (indiceBus != -1) {
            actualizarCapacidadBus(buses, indiceBus, e.peso, true, e.codigo);
        }

        envios.push_back(e);
        totalEnviosRegistrados++;
    }

    guardarEnvios(envios);
    guardarBuses(buses);

    cout << "[SEEDING] 10 registros cargados exitosamente.\n";
    cout << "Presione Enter para continuar...\n";
    cin.get();
}
