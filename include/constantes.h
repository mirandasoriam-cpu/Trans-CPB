#ifndef CONSTANTES_H
#define CONSTANTES_H

// ====== ARCHIVOS DE DATOS ======
const char* const Arch_envios = "envios13.csv";
const char* const Arch_buses  = "buses13.csv";

// ====== LIMITES DEL SISTEMA ======
const float CAPACIDAD_MAX_BUS      = 10000.0;
const int   NUM_CIUDADES           = 7;
const float PESO_MAX_ENVIO         = 500.0;
const float PESO_LIMITE_IMPUESTO   = 30.0;
const float PORCENTAJE_IMPUESTO    = 0.05;

// ====== CIUDADES ======
const char* const CIUDADES_INTERNAS[] = {
    "Santa Cruz",
    "Cochabamba",
    "Sucre",
    "Tarija",
    "Cobija",
    "Trinidad",
    "Oruro"
};

// ====== PRECIOS POR KG POR CIUDAD ======
const float PRECIOS_CIUDAD[7] = {5.4, 3.7, 4.4, 4.6, 10.0, 6.0, 3.7};

// ====== HORARIOS POR CIUDAD ======
const char* const HORARIOS_SANTACRUZ[]  = {"08:00", "19:00", "20:00", "21:00", "21:30"};
const char* const HORARIOS_COCHABAMBA[] = {"07:30", "10:00", "11:30", "16:00", "21:00", "21:30", "22:00", "22:30"};
const char* const HORARIOS_SUCRE[]      = {"18:00", "22:00"};
const char* const HORARIOS_TARIJA[]     = {"14:00", "17:00", "20:00"};
const char* const HORARIOS_COBIJA[]     = {"15:00", "20:30"};
const char* const HORARIOS_ORURO[]      = {"07:30", "10:30", "13:30", "15:30", "17:30"};
const char* const HORARIOS_TRINIDAD[]   = {"15:00", "21:00", "22:00"};

// ====== CANTIDAD DE HORARIOS POR CIUDAD ======
const int NUM_HORARIOS_SANTACRUZ  = 5;
const int NUM_HORARIOS_COCHABAMBA = 8;
const int NUM_HORARIOS_SUCRE      = 2;
const int NUM_HORARIOS_TARIJA     = 3;
const int NUM_HORARIOS_COBIJA     = 2;
const int NUM_HORARIOS_ORURO      = 5;
const int NUM_HORARIOS_TRINIDAD   = 3;

#endif
