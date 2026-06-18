#include <iostream>
#include <string>
#include <limits>

#include "utilidades.h"

using namespace std;

// ====== CENTRAR TEXTO EN CONSOLA ======
void centrarTexto(const string& texto, int ancho = 60) {

    int espacios = (ancho - texto.length()) / 2;

    if (espacios > 0) cout << string(espacios, ' ');

    cout << texto << endl;
}

// ====== MOSTRAR CARATULA DEL SISTEMA ======
void mostrarCaratula() {

    system("cls");

    cout << string(60, '=') << endl;

    centrarTexto("TRANS CPB", 60);
    centrarTexto("SISTEMA DE ENVIOS POR BUS", 60);
    centrarTexto("ENVIOS DESDE SEDE EN LA PAZ", 60);

    cout << string(60, '=') << endl;

    centrarTexto("Sistema de gestion de envios interdepartamentales", 60);
    centrarTexto("para paquetes mediante buses de carga", 60);

    cout << string(60, '=') << endl << endl;
}

// ====== MOSTRAR MENU PRINCIPAL ======
void mostrarMenu() {

    system("cls");

    centrarTexto("MENU PRINCIPAL", 60);

    cout << string(60, '=') << endl;

    centrarTexto(" 1. Agregar nuevo envio",              60);
    centrarTexto(" 2. Listar todos los envios",           60);
    centrarTexto(" 3. Buscar envio por codigo (lineal)",  60);
    centrarTexto(" 4. Buscar envios por destino",         60);
    centrarTexto(" 5. Busqueda binaria por codigo",       60);
    centrarTexto(" 6. Modificar envio",                   60);
    centrarTexto(" 7. Eliminar envio",                    60);
    centrarTexto(" 8. Ordenar por ciudad (Bubble Sort)",  60);
    centrarTexto(" 9. Comparar algoritmos de ordenacion", 60);
    centrarTexto("10. Mostrar estado de buses",           60);
    centrarTexto("11. Mostrar rutas y horarios",          60);
    centrarTexto("12. Generar reporte completo",          60);
    centrarTexto("13. Intercalar archivos por jornada",   60);
    centrarTexto("14. Exportar reporte a PDF",             60);
    centrarTexto(" 0. Salir",                             60);


    cout << string(60, '=') << endl;

    centrarTexto("Seleccione una opcion: ", 60);
}

// ====== PAUSA: ESPERAR ENTER ======
void pausa() {

    cout << "\nPresione Enter para continuar...";

    cin.ignore();
    cin.get();
}
