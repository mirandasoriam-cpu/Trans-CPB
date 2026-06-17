/*
 * Modulo: reporte_pdf.cpp
 * Proposito: Genera un archivo PDF sin librerias externas, escribiendo
 *            directamente la sintaxis del formato PDF 1.4.
 *            El PDF contiene: caratula, listado de envios por ciudad,
 *            y resumen general con totales.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cstring>
#include <ctime>

#include "../include/reporte_pdf.h"
#include "../include/constantes.h"

using namespace std;

// ====== TIPO AUXILIAR: LISTA DE OFFSETS DE OBJETOS ======
// Necesario para la tabla xref al final del PDF
struct OffsetObj {
    long posicion;
};

// ====== ESCAPAR TEXTO PARA PDF ======
// Reemplaza parentesis y backslash que son especiales en strings PDF
static string escaparPDF(const char* texto) {

    string r;

    for (int i = 0; texto[i] != '\0'; i++) {

        unsigned char c = (unsigned char)texto[i];

        if      (c == '(')  r += "\\(";
        else if (c == ')')  r += "\\)";
        else if (c == '\\') r += "\\\\";
        else if (c >= 32 && c < 128) r += (char)c;
        else r += '?';   // caracteres no ASCII -> reemplazar
    }

    return r;
}

// ====== CLASE AUXILIAR: ESCRITOR PDF ======
// Maneja los offsets de objetos y el stream de contenido de pagina
struct PdfWriter {

    ofstream f;
    vector<long> offsets;   // offset de cada objeto (base 1)
    int totalObjetos;

    PdfWriter() : totalObjetos(0) {}

    // Abrir archivo
    bool abrir(const char* ruta) {
        f.open(ruta, ios::binary | ios::trunc);
        return f.is_open();
    }

    // Registrar inicio de un nuevo objeto y guardar su offset
    void iniciarObjeto() {
        offsets.push_back(f.tellp());
        totalObjetos++;
        f << totalObjetos << " 0 obj\n";
    }

    void cerrarObjeto() {
        f << "endobj\n\n";
    }

    long posActual() {
        return (long)f.tellp();
    }
};

// ====== GENERAR REPORTE EN PDF ======
void generarReportePDF(const vector<Envio>& envios) {

    const char* rutaPDF = "data/reporte_envios.pdf";

    // ---- Preparar fecha ----
    time_t ahora   = time(0);
    tm*    tiempo  = localtime(&ahora);
    char   fechaBuf[30];
    sprintf(fechaBuf, "%02d/%02d/%04d  %02d:%02d",
            tiempo->tm_mday, tiempo->tm_mon + 1, tiempo->tm_year + 1900,
            tiempo->tm_hour, tiempo->tm_min);

    // ---- Construir el contenido de texto de la pagina ----
    // Usamos el operador BT/ET de PDF para bloques de texto.
    // Fuente: Helvetica (estandar, no requiere embeber).
    // Cada linea: "Tf" (fuente+tamano), "Td" (mover cursor), "Tj" (mostrar texto).

    ostringstream contenido;

    // --- Titulo ---
    contenido << "BT\n";
    contenido << "/F1 16 Tf\n";
    contenido << "220 780 Td\n";
    contenido << "(TRANS CPB) Tj\n";
    contenido << "ET\n";

    contenido << "BT\n";
    contenido << "/F1 11 Tf\n";
    contenido << "160 760 Td\n";
    contenido << "(Sistema de Envios Interdepartamentales) Tj\n";
    contenido << "ET\n";

    contenido << "BT\n";
    contenido << "/F2 9 Tf\n";
    contenido << "200 745 Td\n";
    contenido << "(Fecha: " << escaparPDF(fechaBuf) << ") Tj\n";
    contenido << "ET\n";

    // Linea separadora (rectangulo fino)
    contenido << "0.5 w\n";
    contenido << "50 738 m 545 738 l S\n";

    // --- Encabezado de tabla ---
    contenido << "BT\n";
    contenido << "/F1 8 Tf\n";
    contenido << "50 725 Td\n";
    contenido << "(CODIGO) Tj\n";
    contenido << "150 725 Td\n";
    contenido << "(-100 0) Td\n";
    contenido << "ET\n";

    // Encabezados de columna
    int colCodigo = 50,  colRem = 150, colDest = 270,
        colDestino = 350, colPeso = 420, colCosto = 470;
    int yHeader = 725;

    contenido << "BT\n/F1 8 Tf\n";
    contenido << colCodigo  << " " << yHeader << " Td (CODIGO) Tj\n";
    contenido << "ET\n";
    contenido << "BT\n/F1 8 Tf\n";
    contenido << colRem     << " " << yHeader << " Td (REMITENTE) Tj\n";
    contenido << "ET\n";
    contenido << "BT\n/F1 8 Tf\n";
    contenido << colDest    << " " << yHeader << " Td (DESTINATARIO) Tj\n";
    contenido << "ET\n";
    contenido << "BT\n/F1 8 Tf\n";
    contenido << colDestino << " " << yHeader << " Td (CIUDAD) Tj\n";
    contenido << "ET\n";
    contenido << "BT\n/F1 8 Tf\n";
    contenido << colPeso    << " " << yHeader << " Td (PESO) Tj\n";
    contenido << "ET\n";
    contenido << "BT\n/F1 8 Tf\n";
    contenido << colCosto   << " " << yHeader << " Td (COSTO Bs.) Tj\n";
    contenido << "ET\n";

    // Linea bajo encabezado
    contenido << "0.3 w\n";
    contenido << "50 720 m 545 720 l S\n";

    // --- Filas de envios ---
    int y = 710;
    int fila = 0;
    float costoTotalGeneral = 0;
    float pesoTotalGeneral  = 0;

    for (int i = 0; i < (int)envios.size() && y > 80; i++) {

        const Envio& e = envios[i];

        // Fondo alternado (gris muy claro en filas pares)
        if (fila % 2 == 0) {
            contenido << "0.95 0.95 0.95 rg\n";
            contenido << "50 " << (y - 3) << " 495 12 re f\n";
            contenido << "0 0 0 rg\n";
        }

        // Truncar textos largos para que quepan
        char remCorto[20], desCorto[20];
        strncpy(remCorto, e.remitente.nombre,    18); remCorto[18] = '\0';
        strncpy(desCorto, e.destinatario.nombre, 18); desCorto[18] = '\0';

        char pesoBuf[12], costoBuf[12];
        sprintf(pesoBuf,  "%.1f kg", e.peso);
        sprintf(costoBuf, "%.2f",    e.costoTotal);

        contenido << "BT\n/F2 7 Tf\n";
        contenido << colCodigo  << " " << y << " Td (" << escaparPDF(e.codigo)         << ") Tj\n";
        contenido << "ET\n";
        contenido << "BT\n/F2 7 Tf\n";
        contenido << colRem     << " " << y << " Td (" << escaparPDF(remCorto)          << ") Tj\n";
        contenido << "ET\n";
        contenido << "BT\n/F2 7 Tf\n";
        contenido << colDest    << " " << y << " Td (" << escaparPDF(desCorto)          << ") Tj\n";
        contenido << "ET\n";
        contenido << "BT\n/F2 7 Tf\n";
        contenido << colDestino << " " << y << " Td (" << escaparPDF(e.destino)         << ") Tj\n";
        contenido << "ET\n";
        contenido << "BT\n/F2 7 Tf\n";
        contenido << colPeso    << " " << y << " Td (" << escaparPDF(pesoBuf)           << ") Tj\n";
        contenido << "ET\n";
        contenido << "BT\n/F2 7 Tf\n";
        contenido << colCosto   << " " << y << " Td (" << escaparPDF(costoBuf)          << ") Tj\n";
        contenido << "ET\n";

        costoTotalGeneral += e.costoTotal;
        pesoTotalGeneral  += e.peso;

        y -= 12;
        fila++;
    }

    // Linea de cierre de tabla
    contenido << "0.3 w\n";
    contenido << "50 " << (y + 5) << " m 545 " << (y + 5) << " l S\n";

    // --- Totales ---
    y -= 8;
    char totalEnvBuf[20], totalPesoBuf[20], totalCostBuf[20];
    sprintf(totalEnvBuf,  "%d envios",   (int)envios.size());
    sprintf(totalPesoBuf, "%.2f kg",     pesoTotalGeneral);
    sprintf(totalCostBuf, "Bs. %.2f",   costoTotalGeneral);

    contenido << "BT\n/F1 8 Tf\n";
    contenido << "50 " << y << " Td (TOTAL: " << escaparPDF(totalEnvBuf) << ") Tj\n";
    contenido << "ET\n";
    contenido << "BT\n/F1 8 Tf\n";
    contenido << colPeso  << " " << y << " Td (" << escaparPDF(totalPesoBuf) << ") Tj\n";
    contenido << "ET\n";
    contenido << "BT\n/F1 8 Tf\n";
    contenido << colCosto << " " << y << " Td (" << escaparPDF(totalCostBuf) << ") Tj\n";
    contenido << "ET\n";

    // --- Resumen por ciudad ---
    y -= 25;

    contenido << "0.5 w\n";
    contenido << "50 " << (y + 12) << " m 545 " << (y + 12) << " l S\n";

    contenido << "BT\n/F1 9 Tf\n";
    contenido << "50 " << y << " Td (RESUMEN POR CIUDAD) Tj\n";
    contenido << "ET\n";

    y -= 14;

    for (int c = 0; c < NUM_CIUDADES && y > 40; c++) {

        int    cnt  = 0;
        float  peso = 0, costo = 0;

        for (int i = 0; i < (int)envios.size(); i++) {
            if (strcmp(envios[i].destino, CIUDADES_INTERNAS[c]) == 0) {
                cnt++;
                peso  += envios[i].peso;
                costo += envios[i].costoTotal;
            }
        }

        if (cnt == 0) continue;

        char linBuf[80];
        sprintf(linBuf, "%s: %d envios | %.1f kg | Bs. %.2f",
                CIUDADES_INTERNAS[c], cnt, peso, costo);

        contenido << "BT\n/F2 8 Tf\n";
        contenido << "60 " << y << " Td (" << escaparPDF(linBuf) << ") Tj\n";
        contenido << "ET\n";

        y -= 12;
    }

    // Pie de pagina
    contenido << "BT\n/F2 7 Tf\n";
    contenido << "200 30 Td (Trans CPB - Reporte generado automaticamente) Tj\n";
    contenido << "ET\n";

    // ---- Escribir el PDF ----
    PdfWriter pdf;

    if (!pdf.abrir(rutaPDF)) {
        cout << "\nError: No se pudo crear el archivo PDF en " << rutaPDF << "\n";
        return;
    }

    // Cabecera PDF
    pdf.f << "%PDF-1.4\n";
    pdf.f << "%\xE2\xE3\xCF\xD3\n";  // comentario binario (marca archivos como binarios)

    // Objeto 1: Catalogo
    pdf.iniciarObjeto();
    pdf.f << "<< /Type /Catalog /Pages 2 0 R >>\n";
    pdf.cerrarObjeto();

    // Objeto 2: Pages (raiz del arbol de paginas)
    pdf.iniciarObjeto();
    pdf.f << "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n";
    pdf.cerrarObjeto();

    // Objeto 3: Page
    pdf.iniciarObjeto();
    pdf.f << "<< /Type /Page\n";
    pdf.f << "   /Parent 2 0 R\n";
    pdf.f << "   /MediaBox [0 0 595 842]\n";    // A4
    pdf.f << "   /Contents 4 0 R\n";
    pdf.f << "   /Resources << /Font << /F1 5 0 R /F2 6 0 R >> >>\n";
    pdf.f << ">>\n";
    pdf.cerrarObjeto();

    // Objeto 4: Stream de contenido de la pagina
    string streamStr = contenido.str();
    pdf.iniciarObjeto();
    pdf.f << "<< /Length " << streamStr.size() << " >>\n";
    pdf.f << "stream\n";
    pdf.f << streamStr;
    pdf.f << "\nendstream\n";
    pdf.cerrarObjeto();

    // Objeto 5: Fuente Helvetica-Bold (F1 - titulos)
    pdf.iniciarObjeto();
    pdf.f << "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica-Bold\n";
    pdf.f << "   /Encoding /WinAnsiEncoding >>\n";
    pdf.cerrarObjeto();

    // Objeto 6: Fuente Helvetica (F2 - cuerpo)
    pdf.iniciarObjeto();
    pdf.f << "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica\n";
    pdf.f << "   /Encoding /WinAnsiEncoding >>\n";
    pdf.cerrarObjeto();

    // Tabla xref
    long xrefPos = pdf.posActual();
    pdf.f << "xref\n";
    pdf.f << "0 " << (pdf.totalObjetos + 1) << "\n";
    pdf.f << "0000000000 65535 f \n";

    for (int i = 0; i < (int)pdf.offsets.size(); i++) {
        pdf.f << setfill('0') << setw(10) << pdf.offsets[i] << " 00000 n \n";
    }

    // Trailer
    pdf.f << "trailer\n";
    pdf.f << "<< /Size " << (pdf.totalObjetos + 1) << " /Root 1 0 R >>\n";
    pdf.f << "startxref\n";
    pdf.f << xrefPos << "\n";
    pdf.f << "%%EOF\n";

    pdf.f.close();

    cout << "\nReporte PDF generado exitosamente: " << rutaPDF << "\n";
    cout << "Total de envios incluidos: " << envios.size() << "\n";
    cout << "Puede abrir el archivo con cualquier lector de PDF (Adobe Reader, etc.).\n";
}
