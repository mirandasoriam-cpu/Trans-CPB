#ifndef ENVIO_H
#define ENVIO_H

#include "persona.h"

// ====== ESTRUCTURA ENVIO ======
struct Envio {
    char codigo[20];
    Persona remitente;
    Persona destinatario;
    char destino[30];
    float peso;
    char horario[10];
    float costoBase;
    float impuesto;
    float costoTotal;
};

#endif
