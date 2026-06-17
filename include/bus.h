#ifndef BUS_H
#define BUS_H

// ====== ESTRUCTURA BUS ======
struct Bus {
    char ruta[30];
    char horario[10];
    float capacidadTotal;
    float capacidadUsada;
    float capacidadRestante;
    int envios[100];
    int contadorEnvios;
};

#endif
