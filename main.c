#include <stdio.h>
#include <stdlib.h>
#include "General.h"
#include "Menu.h"
#include "lib.h"

/*
Se debe desarrollar un sistema (en ANSI C) de venta de productos al estilo
mercadolibre. En este sistema existirán usuarios, los cuales ingresarán utilizando
su nombre de usuario y password. Mediante la plataforma se podrá comprar y
vender productos, estos se encuentran definidos por un nombre y precio. La
porción del sistema que deberá realizarse se centrará en la venta de productos y
consta de un menú con las siguientes opciones:
1. ALTA DE USUARIO: Se piden los datos del usuario requeridos para que el
sistema pueda funcionar.
2. MODIFICAR DATOS DEL USUARIO: Se ingresa el ID del usuario, permitiendo
modificar sus datos.
3. BAJA DEL USUARIO: Se ingresa el ID del usuario y eliminará junto con todos
sus productos a la venta.
4. PUBLICAR PRODUCTO: Se ingresará el ID del usuario y se pedirán los datos
del producto a publicar (nombre, precio y stock)
5. MODIFICAR PUBLICACIÓN: Se ingresará el ID del usuario y se listarán los
productos de dicho usuario mostrando todos sus campos (id, nombre, precio,
cantidad vendida y stock), luego ingresar el ID del producto y se pedirá que se
ingrese un nuevo precio y stock.
6. CANCELAR PUBLICACIÓN: Se ingresará el ID del usuario y se listarán los
productos de dicho usuario mostrando todos sus campos (id, nombre, precio,
cantidad vendida y stock), luego ingresar el ID del producto que se quiere
cancelar su publicación.
7. COMPRAR PRODUCTO: Se ingresará el ID del producto a comprar, y en el
caso que haya stock se realizará la compra, en dicho caso se ingresará una
calificación para el vendedor.
8. LISTAR PUBLICACIONES DE USUARIO: Se ingresa el ID del usuario y se
mostrará una lista de productos indicando: id, nombre, precio, cantidad vendida y
stock.
9. LISTAR PUBLICACIONES: Se mostrará una lista de productos indicando: id,
nombre, precio, cantidad vendida, stock y nombre del usuario.
10. LISTAR USUARIOS: Se mostrará una lista de usuarios con la calificación
promedio de cada uno.
Nota 0: El sistema soportará una capacidad máxima de 100 usuarios y 1000 productos.
Nota 1: Se deberá desarrollar una biblioteca lib.c y lib.h la cual contendrá las funciones (Alta, Baja,
Modificar, etc.).
Nota 2: El código deberá tener comentarios con la documentación de cada una de las funciones y
respetar las reglas de estilo de la cátedra.
*/



int main()
{
    eMenu menuPrincipal = {
                            11, //cantidad de opciones
                            {1,2,3,4,5,6,7,8,9,10,11}, //codigos
                            {"1. ALTA DE USUARIO","2. MODIFICAR DATOS DEL USUARIO","3. BAJA DEL USUARIO","4. PUBLICAR PRODUCTO","5. MODIFICAR PUBLICACIÓN","6. CANCELAR PUBLICACIÓN","7. COMPRAR PRODUCTO","8. LISTAR PUBLICACIONES DE USUARIO","9. LISTAR PUBLICACIONES","10. LISTAR USUARIOS","11. SALIR"}, //descripciones
                            {"MENU GENERICO"} //titulo del menu
                            };
    int opcion;
    char salirDelPrograma = 'N';

    //ARRAYS DE ESTRUCTURAS
    eUsuario listadoUsuarios[USUARIO_NRO_MAX] = {};
    eProducto listadoProductos[PRODUCTO_NRO_MAX] = {};
    eVenta listadoVentas[PRODUCTO_NRO_MAX] = {};

    //INCIALIZAR
    eUsuario_init(listadoUsuarios, USUARIO_NRO_MAX);
    eProducto_init(listadoProductos, PRODUCTO_NRO_MAX);

    do
    {
        ejecutarEnConsola(LIMPIAR_PANTALLA);
        opcion = pedirOpcion(menuPrincipal);
        switch(opcion)
        {
            case 1:
                eUsuario_alta(listadoUsuarios, USUARIO_NRO_MAX);
                break;
            case 2:
                eUsuario_modificacion(listadoUsuarios, USUARIO_NRO_MAX);
                break;
            case 3:
                eUsuario_baja(listadoUsuarios, USUARIO_NRO_MAX);
                break;
            case 4:
                eProducto_alta(listadoProductos, PRODUCTO_NRO_MAX, listadoUsuarios, USUARIO_NRO_MAX);
                break;
            case 5:
                eProducto_modificacion(listadoProductos, PRODUCTO_NRO_MAX);
                break;
            case 6:
                eProducto_baja(listadoProductos, PRODUCTO_NRO_MAX);
                break;
            case 7:
                //compra
                imprimirEnPantalla(menuPrincipal.descripciones[opcion-1]);ejecutarEnConsola(HACER_PAUSA);
                break;
            case 8:
                //lista public usuario
                imprimirEnPantalla(menuPrincipal.descripciones[opcion-1]);ejecutarEnConsola(HACER_PAUSA);
                break;
            case 9:
                eProducto_procesarMostrarListado(listadoProductos, PRODUCTO_NRO_MAX);
                break;
            case 10:
                eUsuario_procesarMostrarListado(listadoUsuarios, USUARIO_NRO_MAX);
                break;
            case 11:
                salirDelPrograma = pedirConfirmacion("Confirma que desea salir del programa?");
                break;
        }

    }
    while(salirDelPrograma == 'N');
    return 0;
}
