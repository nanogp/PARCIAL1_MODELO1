#ifndef PRODUCTO_H_INCLUDED
#   define PRODUCTO_H_INCLUDED
#   define LARGO_NOMBRE_PRODUCTO 50
#   define OCUPADO 1
#   define LIBRE 0
#   define NRO_MAX_PRODUCTO 10
#   define NOMBRE_ESTRUCTURA PRODUCTO
#   define TITULO_GESTION DEFINIR_MACRO_STRING(GESTION DE PRODUCTO)
#   define TITULO_ALTA DEFINIR_MACRO_STRING(PUBLICAR PRODUCTO)
#   define TITULO_BAJA DEFINIR_MACRO_STRING(BAJA DE PRODUCTO)
#   define TITULO_MODIFICACION DEFINIR_MACRO_STRING(MODIFICACION DE PRODUCTO)

    typedef struct
    {
        char nombre[LARGO_NOMBRE_PRODUCTO];
        //------------
        int idGenerica;
        int estado;
    }eProducto;
#endif // PRODUCTO_H_INCLUDED

void eProducto_init(eProducto[], int limite);
int eProducto_buscarPorId(eProducto[], int limite, int id);
int eProducto_siguienteId(eProducto[], int limite);
int eProducto_buscarLugarLibre(eProducto listado[], int limite);
int eProducto_estaVacio(eProducto listado[], int limite);

void eProducto_mostrarUno(eProducto parametro);
void eProducto_mostrarListado(eProducto[], int limite);
void eProducto_mostrarListadoConBorrados(eProducto[], int limite);

void eProducto_alta(eProducto[], int limite);
void eProducto_baja(eProducto[], int limite);
void eProducto_modificacion(eProducto[], int limite);
void eProducto_modificarUno(eProducto[]);

void eProducto_ordenar(eProducto[], int limite, char orden[]);

void eProducto_gestion(eProducto listado[], int limite);
