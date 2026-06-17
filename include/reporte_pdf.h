#ifndef REPORTE_PDF_H
#define REPORTE_PDF_H

/*
 * Modulo: reporte_pdf.h
 * Proposito: Genera un archivo PDF con el reporte estructurado de envios.
 *            No requiere librerias externas; escribe el formato PDF directamente.
 * Parametros de entrada: vector de envios (solo lectura)
 * Retorno: void (crea el archivo reporte_envios.pdf en data/)
 */

#include <vector>
#include "../include/envio.h"

using namespace std;

// ====== GENERAR REPORTE EN PDF ======
// Crea data/reporte_envios.pdf con listado estructurado de envios,
// resumen por ciudad y totales generales.
void generarReportePDF(const vector<Envio>& envios);

#endif
