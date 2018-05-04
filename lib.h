#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED

#   define LARGO_NOMBRE_USUARIO 50
#   define OCUPADO 1
#   define LIBRE 0
#   define USUARIO_NRO_MAX 100
#   define USUARIO_TITULO_ALTA DEFINIR_MACRO_STRING(ALTA DE USUARIO)
#   define USUARIO_TITULO_BAJA DEFINIR_MACRO_STRING(BAJA DE USUARIO)
#   define USUARIO_TITULO_MODIFICACION DEFINIR_MACRO_STRING(MODIFICACION DE USUARIO)

    typedef struct
    {
        char nombre[LARGO_NOMBRE_USUARIO];
        //------------
        int idUsuario;
        int estado;
    }eUsuario;


void eUsuario_init(eUsuario[], int limite);
int eUsuario_buscarPorId(eUsuario[], int limite, int id);
int eUsuario_siguienteId(eUsuario[], int limite);
int eUsuario_buscarLugarLibre(eUsuario listado[], int limite);
int eUsuario_estaVacio(eUsuario listado[], int limite);

void eUsuario_mostrarUno(eUsuario parametro);
void eUsuario_mostrarListado(eUsuario[], int limite);
void eUsuario_mostrarListadoConBorrados(eUsuario[], int limite);

void eUsuario_alta(eUsuario[], int limite);
void eUsuario_baja(eUsuario[], int limite);
void eUsuario_modificacion(eUsuario[], int limite);
void eUsuario_modificarUno(eUsuario[]);

void eUsuario_ordenar(eUsuario[], int limite, char orden[]);

void eUsuario_procesarMostrarListado(eUsuario[], int limite);


#define LARGO_NOMBRE_PRODUCTO 100
#define OCUPADO 1
#define LIBRE 0
#define PRODUCTO_NRO_MAX 1000
#define PRODUCTO_TITULO_ALTA DEFINIR_MACRO_STRING(PUBLICAR PRODUCTO)
#define PRODUCTO_TITULO_BAJA DEFINIR_MACRO_STRING(CANCELAR PUBLICACION)
#define PRODUCTO_TITULO_MODIFICACION DEFINIR_MACRO_STRING(MODIFICAR PUBLICACION)

    typedef struct
    {
        char nombre[LARGO_NOMBRE_PRODUCTO];
        int stock;
        //------------
        int idProducto;
        int idUsuario;
        int estado;
    }eProducto;

void eProducto_init(eProducto[], int limite);

int eProducto_buscarPorId(eProducto[], int limite, int id);

int eProducto_siguienteId(eProducto[], int limite);

int eProducto_buscarLugarLibre(eProducto listado[], int limite);

int eProducto_estaVacio(eProducto listado[], int limite);

void eProducto_mostrarUno(eProducto parametro);

void eProducto_mostrarListado(eProducto[], int limite);

void eProducto_mostrarListadoConBorrados(eProducto[], int limite);

void eProducto_alta(eProducto[], int limiteProductos, eUsuario[], int limiteUsuarios);

void eProducto_baja(eProducto[], int limite);

void eProducto_modificacion(eProducto[], int limite);

void eProducto_modificarUno(eProducto[]);

void eProducto_ordenar(eProducto[], int limite, char orden[]);

void eProducto_procesarMostrarListado(eProducto[], int limite);

typedef struct
{
    int calificacion;
    int cantidadVendida;
    //------------
    int idVenta;
    int idProducto;
}eVenta;


#endif // LIB_H_INCLUDED
