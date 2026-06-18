# Trans CPB — Sistema de Envios Interdepartamentales

## Caratula

| Campo           | Detalle                                      |
|-----------------|----------------------------------------------|
| **Asignatura**  | Programacion I — SIS-112                     |
| **Docente**     | Pamela Shirley Valenzuela Fernandez          |
| **Universidad** | UCB San Pablo — Facultad de Ingenieria       |
| **Gestion**     | 1/2026                                       |

---

## Descripcion del dominio

Trans CPB gestiona envios de paquetes por bus entre La Paz y las principales ciudades de Bolivia (Santa Cruz, Cochabamba, Sucre, Tarija, Cobija, Trinidad y Oruro).

### Structs principales

| Struct   | Campos clave                                                                  |
|----------|-------------------------------------------------------------------------------|
| `Persona`| nombre[50], ci[12], telefono[16], correo[50]                                  |
| `Envio`  | codigo[20], remitente (Persona), destinatario (Persona), destino[30], peso, horario[10], costoBase, impuesto, costoTotal |
| `Bus`    | ruta[30], horario[10], capacidadTotal/Usada/Restante, envios[100], contadorEnvios |

---

## Estructura del proyecto

```
Trans_CPB_Examen/
├── include/          -> Archivos .h  
├── src/              -> Archivos .cpp 
├── data/             -> Archivos CSV de datos
├── main.cpp          -> Solo llamadas a funciones
└── README.md
```

---

## Compilacion y ejecucion

### Con Dev-C++ 
1. Abrir `TransCPB.dev`
2. Ir a **Execute → Compile & Run** 

### Con g++ en consola (desde la raiz del proyecto)
```bash
g++ main.cpp src/*.cpp -Iinclude -o TransCPB.exe
TransCPB.exe
```

---

## Guia de uso rapido

| Opcion | Funcion                                      |
|--------|----------------------------------------------|
| 1      | Agregar nuevo envio (genera codigo automatico) |
| 2      | Listar todos los envios registrados           |
| 3      | Busqueda lineal por codigo de guia           |
| 4      | Busqueda por ciudad destino                  |
| **5**  | **Busqueda binaria** (iterativa o recursiva, con metricas de comparaciones) |
| 6      | Modificar telefono/correo del remitente o telefono del destinatario |
| 7      | Eliminar envio por codigo                    |
| 8      | Ordenar por ciudad usando Bubble Sort optimizado |
| **9**  | **Comparar Bubble Sort vs Merge Sort** con metricas de eficiencia |
| 10     | Estado de capacidad de cada bus             |
| 11     | Ver rutas, horarios y precios               |
| 12     | Reporte completo por ciudad                 |
| 13     | Intercalar archivos manana/tarde por codigo |
| 0      | Guardar y salir                             |

**Seeding automatico:** si el archivo de datos tiene menos de 10 registros al iniciar, el sistema carga 10 envios de prueba automaticamente.

---

## Decisiones de diseno

- **Parametros por referencia** en `agregarEnvio`, `modificarEnvio`, `cargarDatosPrueba` y todos los modulos de ordenacion/busqueda que retornan metricas.
- **Retorno multiple** implementado en `busquedaBinariaIterativa` y `busquedaBinariaRecursiva` (retornan indice y cantidad de comparaciones por referencia).
- **Bubble Sort** elegido como algoritmo base por su implementacion intuitiva y la optimizacion de corte temprano cuando el arreglo ya esta ordenado.
- **Merge Sort** usado en la comparacion porque es mas eficiente en arreglos grandes y es el algoritmo natural de intercalacion.
- **CSV** en lugar de binario para facilitar la inspeccion directa de los datos y la portabilidad.
