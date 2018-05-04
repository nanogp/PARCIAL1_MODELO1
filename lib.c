#include "lib.h"
#include "Menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void eUsuario_init(eUsuario listado[], int limite)
{
	int i;

	if(limite > 0 && listado != NULL)
	{
		for(i=0 ; i<limite ; i++)
		{
			listado[i].estado= LIBRE;
			listado[i].idUsuario= 0;
		}
	}
}

int eUsuario_buscarLugarLibre(eUsuario listado[], int limite)
{
	int retorno = -1;
	int i;

    if(eUsuario_estaVacio(listado, limite) == 1)
    {
        retorno = 0; //devuelvo la primera posicion
    }
    else
    {
        if(limite > 0 && listado != NULL)
        {
            retorno = -2;
            for(i=0 ; i<limite ; i++)
            {
                if(listado[i].estado == LIBRE)
                {
                    retorno = i;
                    break;
                }
            }
        }
    }
	return retorno;
}

int eUsuario_estaVacio(eUsuario listado[], int limite)
{
    int retorno = 1;
    int i;

    for(i=0 ; i<limite ; i++)
    {
        if(listado[i].estado == OCUPADO)
        {
            retorno = 0;
            break;//con el primer ocupado ya se que no esta vacio
        }
    }

    return retorno;
}

int eUsuario_siguienteId(eUsuario listado[], int limite)
{
	int retorno = 0;
	int i;

	if(limite > 0 && listado != NULL)
	{
		for(i=0; i<limite; i++)
		{
			if(listado[i].estado == OCUPADO)
			{
				if(listado[i].idUsuario > retorno)
				{
					 retorno = listado[i].idUsuario;
				}
			}
		}
	}

	return retorno+1;
}

int eUsuario_buscarPorId(eUsuario listado[], int limite, int id)
{
	int retorno = -1;
	int i;

	if(limite > 0 && listado != NULL)
	{
		retorno = -2;
		for(i=0 ; i<limite ; i++)
		{
			if(listado[i].estado == OCUPADO && listado[i].idUsuario == id)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

void eUsuario_mostrarUno(eUsuario parametro)
{
	 printf("\n %-3d - %-20s", parametro.idUsuario, parametro.nombre);
}

void eUsuario_mostrarListado(eUsuario listado[], int limite)
{
	int i;

    if(eUsuario_estaVacio(listado, limite) == 0)
    {
        printf("\n ID  - nombre");
        if(limite > 0 && listado != NULL)
        {
            for(i=0; i<limite; i++)
            {
                if(listado[i].estado==OCUPADO)
                {
                    eUsuario_mostrarUno(listado[i]);
                }
            }
        }
    }
    else
    {
        imprimirEnPantalla("\nNada para mostrar! \n\nLa lista esta vacia o todos los registros se dieron de baja.");
    }
}

void eUsuario_procesarMostrarListado(eUsuario listado[], int limite)
{
    ejecutarEnConsola(LIMPIAR_PANTALLA);
    imprimirTitulo("LISTADO DE USUARIOS");

    eUsuario_mostrarListado(listado, limite);

    ejecutarEnConsola(HACER_PAUSA);
}

void eUsuario_mostrarListadoConBorrados(eUsuario listado[], int limite)
{
	int i;
	if(limite > 0 && listado != NULL)
	{
		for(i=0; i<limite; i++)
		{
			if(listado[i].estado == LIBRE)
			{
				printf("\n[LIBRE]");
			}
			eUsuario_mostrarUno(listado[i]);
		}
	}
}

void eUsuario_pedirNombre(char *retorno)
{
	pedirStringValido(retorno, "\nIngrese nombre: ", "\nNombre muy largo. Reingrese el nombre: ", LARGO_NOMBRE_USUARIO);
}

eUsuario eUsuario_pedirIngreso(eUsuario listado[], int limite)
{
	eUsuario retorno;

	retorno.idUsuario = eUsuario_siguienteId(listado, limite);

	eUsuario_pedirNombre((char *)&(retorno.nombre));

    //retorno.demasCampos

	retorno.estado = OCUPADO;

	return retorno;
}

void eUsuario_alta(eUsuario listado[], int limite)
{
	eUsuario registro;
	char confirmacion;
	int posicion;

	posicion = eUsuario_buscarLugarLibre(listado, limite);
	if(posicion < 0)
	{
		imprimirEnPantalla("\nNo hay m s lugares disponibles para altas de Usuario.");
	}
	else
	{
		ejecutarEnConsola(LIMPIAR_PANTALLA);
		imprimirTitulo(USUARIO_TITULO_ALTA);
		registro = eUsuario_pedirIngreso(listado, limite);
		eUsuario_mostrarUno(registro);

		confirmacion = pedirConfirmacion("Confirma que los datos ingresados son correctos?");

		if(confirmacion == 'S')
		{
			listado[posicion] = registro;
			//aca se ordenaria la lista
			imprimirEnPantalla("\nEl Usuario se dio de alta.");
		}
		else
		{
			imprimirEnPantalla("\nSe cancelà la gestiàn.");
		}
	}
	ejecutarEnConsola(HACER_PAUSA);
}

void eUsuario_baja(eUsuario listado[], int limite)
{
    int id;
    char confirmacion;
    char continuarGestion = 'N';
    int posicion;

    do
    {
        ejecutarEnConsola(LIMPIAR_PANTALLA);
        imprimirTitulo(USUARIO_TITULO_BAJA);

        if(eUsuario_estaVacio(listado, limite) == 1)
        {
            imprimirEnPantalla("\n\nLa lista esta vacia o todos los registros se dieron de baja.");
        }
        else
        {
            eUsuario_mostrarListado(listado, limite);
            id = pedirInt("\n\nIngrese el ID a dar de baja: ");

            posicion = eUsuario_buscarPorId(listado, limite, id);
            if(posicion < 0)
            {
                imprimirEnPantalla("\nEl ID de Usuario ingresado por par metro no existe.");
                continuarGestion = pedirConfirmacion("Desea reintentar la gesti¢n?");
            }
            else
            {
                eUsuario_mostrarUno(listado[posicion]);

                confirmacion = pedirConfirmacion("Confirma que desea dar de baja dicho Usuario?");

                if(confirmacion == 'S')
                {
                    listado[posicion].estado = LIBRE;
                    imprimirEnPantalla("\nEl Usuario se dio de baja.");
                    continuarGestion = 'N';
                }
                else
                {
                    imprimirEnPantalla("\nSe cancelà la gestiàn.");
                }
            }
        }
    }
    while(continuarGestion =='S');

    ejecutarEnConsola(HACER_PAUSA);
}

void eUsuario_modificarUno(eUsuario *registro)
{
    eMenu menuModificar = {
                            6, //cantidad de opciones
                            {1,2,3,4,5,9}, //codigos
                            {"1. Legajo","2. Nombre","3. Nota 1","4. Nota 2","5. Rehabilitar","9. Cancelar"}, //descripciones
                            {"\nQu‚ desea modificar?"} //titulo del menu
                           };
    int opcion;

    ejecutarEnConsola(LIMPIAR_PANTALLA);
    imprimirTitulo("MODIFICANDO REGISTRO");
    imprimirEnPantalla("\nDatos a modificar:");
    eUsuario_mostrarUno(*registro);

    opcion = pedirOpcion(menuModificar);
    switch(opcion)
    {
        case 1:
            registro->idUsuario = pedirIntValido("Ingrese nuevo ID", "El ID debe ser un n£mero entero mayor que cero", 1, 99999999);
            break;
        case 2:
            eUsuario_pedirNombre((char *)&registro->nombre);
            break;
        /*
        case 3:
            registro->campoM
            break;
        case 4:
            registro->campoN
            break;
        */
        case 5:
            registro->estado = OCUPADO;
            break;
        case 9:
            break;
    }
}

void eUsuario_modificacion(eUsuario listado[], int limite)
{
    eUsuario registro;
    char confirmacion;
    int posicion;

    ejecutarEnConsola(LIMPIAR_PANTALLA);
    imprimirTitulo(USUARIO_TITULO_MODIFICACION);

    if(eUsuario_estaVacio(listado, limite) == 1)
    {
        imprimirEnPantalla("\n\nLa lista esta vacia o todos los registros se dieron de baja.");
    }
    else
    {
        registro.idUsuario = pedirIntValido("\n\nIngrese el ID de Usuario a modificar: ", "El ID debe ser un n¡mero mayor que cero", 1, 99999999);

        posicion = eUsuario_buscarPorId(listado, limite, registro.idUsuario);
        if(posicion < 0)
        {
            imprimirEnPantalla("\nEl ID de Usuario ingresado por par metro no existe.");
        }
        else
        {
            //traigo el registro del id elegido para no pisar directo sobre el listado
            registro = listado[posicion];

            eUsuario_modificarUno(&registro);

            /*
            if(aca se pregunta si hubo cambios que requieran reprocesos)
            {
                se recalcularian promedios por ej.
            }
            */
            ejecutarEnConsola(LIMPIAR_PANTALLA);

            imprimirEnPantalla("Usuario actual:");
            eUsuario_mostrarUno(listado[posicion]);

            imprimirEnPantalla("Usuario nuevo:");
            eUsuario_mostrarUno(registro);

            confirmacion = pedirConfirmacion("Confirma que los datos ingresados son correctos?");

            if(confirmacion == 'S')
            {
                listado[posicion] = registro;
                //aca podria ordenarse con los datos nuevos;
                imprimirEnPantalla("\nEl Usuario se modificà.");
            }
            else
            {
                imprimirEnPantalla("\nSe cancelà la gestiàn.");
            }
        }
    }
    ejecutarEnConsola(HACER_PAUSA);
}

void eUsuario_ordenar(eUsuario listado[], int limite, char orden[])
{
	int i;
	int j;
	eUsuario aux;

	if(strcmp(orden, "idAsc") == 0)
	{
		for(i=0 ; i<limite-1 ; i++)
		{
			for(j=i+1 ; j<limite ; j++)
			{
				if(listado[i].idUsuario > listado[j].idUsuario)
				{
					aux = listado[i];
					listado[i] = listado[j];
					listado[j] = aux;
				}
			}
		}
	}
	else if(strcmp(orden, "idDesc") == 0)
	{
		for(i=0 ; i<limite-1 ; i++)
		{
			for(j=i+1 ; j<limite ; j++)
			{
				if(listado[i].idUsuario < listado[j].idUsuario)
				{
					aux = listado[i];
					listado[i] = listado[j];
					listado[j] = aux;
				}
			}
		}
	}
	else if(strcmp(orden, "nombreAsc") == 0)
	{
		for(i=0 ; i<limite-1 ; i++)
		{
			for(j=i+1 ; j<limite ; j++)
			{
				if(strcmp(listado[i].nombre, listado[j].nombre) > 0)
				{
					aux = listado[i];
					listado[i] = listado[j];
					listado[j] = aux;
				}
			}
		}
	}
	else if(strcmp(orden, "nombreDesc") == 0)
	{
		for(i=0 ; i<limite-1 ; i++)
		{
			for(j=i+1 ; j<limite ; j++)
			{
				if(strcmp(listado[i].nombre, listado[j].nombre) < 0)
				{
					aux = listado[i];
					listado[i] = listado[j];
					listado[j] = aux;
				}
			}
		}
	}
}



void eProducto_init(eProducto listado[], int limite)
{
	int i;

	if(limite > 0 && listado != NULL)
	{
		for(i=0 ; i<limite ; i++)
		{
			listado[i].estado= LIBRE;
			listado[i].idProducto= 0;
		}
	}
}

int eProducto_buscarLugarLibre(eProducto listado[], int limite)
{
	int retorno = -1;
	int i;

    if(eProducto_estaVacio(listado, limite) == 1)
    {
        retorno = 0; //devuelvo la primera posicion
    }
    else
    {
        if(limite > 0 && listado != NULL)
        {
            retorno = -2;
            for(i=0 ; i<limite ; i++)
            {
                if(listado[i].estado == LIBRE)
                {
                    retorno = i;
                    break;
                }
            }
        }
    }
	return retorno;
}

int eProducto_estaVacio(eProducto listado[], int limite)
{
    int retorno = 1;
    int i;

    for(i=0 ; i<limite ; i++)
    {
        if(listado[i].estado == OCUPADO)
        {
            retorno = 0;
            break;//con el primer ocupado ya se que no esta vacio
        }
    }

    return retorno;
}

int eProducto_siguienteId(eProducto listado[], int limite)
{
	int retorno = 0;
	int i;

	if(limite > 0 && listado != NULL)
	{
		for(i=0; i<limite; i++)
		{
			if(listado[i].estado == OCUPADO)
			{
				if(listado[i].idProducto > retorno)
				{
					 retorno = listado[i].idProducto;
				}
			}
		}
	}

	return retorno+1;
}

int eProducto_buscarPorId(eProducto listado[], int limite, int id)
{
	int retorno = -1;
	int i;

	if(limite > 0 && listado != NULL)
	{
		retorno = -2;
		for(i=0 ; i<limite ; i++)
		{
			if(listado[i].estado == OCUPADO && listado[i].idProducto == id)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

void eProducto_mostrarUno(eProducto parametro)
{
	 printf("\n %-3d - %-20s - %d", parametro.idProducto, parametro.nombre, parametro.stock);

}

void eProducto_mostrarListado(eProducto listado[], int limite)
{
	int i;

    if(eProducto_estaVacio(listado, limite) == 0)
    {
        if(limite > 0 && listado != NULL)
        {
            for(i=0; i<limite; i++)
            {
                if(listado[i].estado==OCUPADO)
                {
                    eProducto_mostrarUno(listado[i]);
                }
            }
        }
    }
    else
    {
        imprimirEnPantalla("\nNada para mostrar! \n\nLa lista esta vacia o todos los registros se dieron de baja.");
    }
}

void eProducto_procesarMostrarListado(eProducto listado[], int limite)
{
    ejecutarEnConsola(LIMPIAR_PANTALLA);
    imprimirTitulo("LISTADO DE PUBLICACIONES");

    eProducto_mostrarListado(listado, limite);

    ejecutarEnConsola(HACER_PAUSA);
}

void eProducto_mostrarListadoConBorrados(eProducto listado[], int limite)
{
	int i;
	if(limite > 0 && listado != NULL)
	{
		for(i=0; i<limite; i++)
		{
			if(listado[i].estado == LIBRE)
			{
				printf("\n[LIBRE]");
			}
			eProducto_mostrarUno(listado[i]);
		}
	}
}

void eProducto_pedirNombre(char *retorno)
{
	pedirStringValido(retorno, "\nIngrese nombre: ", "\nNombre muy largo. Reingrese el nombre: ", LARGO_NOMBRE_PRODUCTO);
}

int eProducto_pedirStock()
{
    return pedirIntValido("\nIngrese el stock", "\nEl stock debe ser un numero entero no negativo", 0, 10^7);
}

eProducto eProducto_pedirIngreso(eProducto listado[], int limite)
{
	eProducto retorno;

	retorno.idProducto = eProducto_siguienteId(listado, limite);

	eProducto_pedirNombre((char *)&(retorno.nombre));

	retorno.stock = eProducto_pedirStock();

    //retorno.demasCampos

	retorno.estado = OCUPADO;

	return retorno;
}

int eProducto_pedirIdUsuario(eUsuario listado[], int limite)
{
    int retorno;
    int posicion;

    do
    {
        eUsuario_mostrarListado(listado, limite);
        retorno = pedirIntValido("\nIngrese un ID de usuario", "Reingrese un ID valido. Deber ser un numero entero mayor que cero: ", 1, 10^7);
        posicion = eUsuario_buscarPorId(listado, limite, retorno);
        if(posicion < 0)
        {
            imprimirEnPantalla("\nNo se encontro un usuario con el ID ingresado.");
            ejecutarEnConsola(HACER_PAUSA);
        }
    }
    while(posicion < 0);

    return retorno;
}

void eProducto_alta(eProducto listadoProductos[], int limiteProductos, eUsuario listadoUsuarios[], int limiteUsuarios)
{
	eProducto registro;
	char confirmacion;
	int posicion;

	posicion = eProducto_buscarLugarLibre(listadoProductos, limiteProductos);
	if(posicion < 0)
	{
		imprimirEnPantalla("\nNo hay m s lugares disponibles para altas de Producto.");
	}
	else
	{
		ejecutarEnConsola(LIMPIAR_PANTALLA);
		imprimirTitulo(PRODUCTO_TITULO_ALTA);

		registro.idUsuario = eProducto_pedirIdUsuario(listadoUsuarios, limiteUsuarios);
		registro = eProducto_pedirIngreso(listadoProductos, limiteProductos);

		eProducto_mostrarUno(registro);
		confirmacion = pedirConfirmacion("Confirma que los datos ingresados son correctos?");

		if(confirmacion == 'S')
		{
			listadoProductos[posicion] = registro;
			eProducto_ordenar(listadoProductos, limiteProductos, "nombreAsc");
			imprimirEnPantalla("\nEl Producto se dio de alta.");
		}
		else
		{
			imprimirEnPantalla("\nSe cancelà la gestiàn.");
		}
	}
	ejecutarEnConsola(HACER_PAUSA);
}

void eProducto_baja(eProducto listado[], int limite)
{
    int id;
    char confirmacion;
    char continuarGestion = 'N';
    int posicion;

    do
    {
        ejecutarEnConsola(LIMPIAR_PANTALLA);
        imprimirTitulo(PRODUCTO_TITULO_BAJA);

        eProducto_mostrarListado(listado, limite);
        id = pedirInt("\n\nIngrese el ID a dar de baja: ");

        posicion = eProducto_buscarPorId(listado, limite, id);
        if(posicion < 0)
        {
            if(listado[posicion].estado == LIBRE)
            {
                imprimirEnPantalla("\nEl Producto ya se encontraba dado de baja");
            }
            else
            {
                eProducto_mostrarUno(listado[posicion]);

                confirmacion = pedirConfirmacion("Confirma que desea dar de baja dicho Producto?");

                if(confirmacion == 'S')
                {
                    listado[posicion].estado = LIBRE;
                    imprimirEnPantalla("\nEl Producto se dio de baja.");
                    continuarGestion = 'N';
                }
                else
                {
                    imprimirEnPantalla("\nSe cancelà la gestiàn.");
                }
            }
        }
        else
        {
            imprimirEnPantalla("\nEl ID de Producto ingresado por par metro no existe.");
            continuarGestion = pedirConfirmacion("Desea reintentar la gesti¢n?");
        }
    }
    while(continuarGestion =='S');

    ejecutarEnConsola(HACER_PAUSA);
}

void eProducto_modificarUno(eProducto *registro)
{
    eMenu menuModificar = {
                            6, //cantidad de opciones
                            {1,2,3,4,5,9}, //codigos
                            {"1. Legajo","2. Nombre","3. Nota 1","4. Nota 2","5. Rehabilitar","9. Cancelar"}, //descripciones
                            {"\nQu‚ desea modificar?"} //titulo del menu
                           };
    int opcion;

    ejecutarEnConsola(LIMPIAR_PANTALLA);
    imprimirTitulo("MODIFICANDO REGISTRO");
    imprimirEnPantalla("\nDatos a modificar:");
    eProducto_mostrarUno(*registro);

    if(registro->estado == 0)
    {
        imprimirEnPantalla("El Producto se encuentra dado de baja.");
    }

    opcion = pedirOpcion(menuModificar);
    switch(opcion)
    {
        case 1:
            registro->idProducto = pedirIntValido("Ingrese nuevo ID", "El ID debe ser un n£mero entero mayor que cero", 1, 99999999);
            break;
        case 2:
            eProducto_pedirNombre((char *)&registro->nombre);
            break;
        /*
        case 3:
            registro->campoM
            break;
        case 4:
            registro->campoN
            break;
        */
        case 5:
            registro->estado = OCUPADO;
            break;
        case 9:
            break;
    }
}

void eProducto_modificacion(eProducto listado[], int limite)
{
    eProducto registro;
    char confirmacion;
    int posicion;

    ejecutarEnConsola(LIMPIAR_PANTALLA);
    imprimirTitulo(PRODUCTO_TITULO_MODIFICACION);

    registro.idProducto = pedirIntValido("\n\nIngrese el ID de Producto a modificar: ", "El ID debe ser un n¡mero mayor que cero", 1, 99999999);

    posicion = eProducto_buscarPorId(listado, limite, registro.idProducto);
    if(posicion != -1)
    {
        //traigo el registro del id elegido para no pisar directo sobre el listado
        registro = listado[posicion];

        eProducto_modificarUno(&registro);

        if(listado[posicion].estado != registro.estado)
        {
            confirmacion = pedirConfirmacion("Confirma que desea rehabilitar al Producto?");
        }
        else
        {
            /*
            if(aca se pregunta si hubo cambios que requieran reprocesos)
            {
                se recalcularian promedios por ej.
            }
            */
            ejecutarEnConsola(LIMPIAR_PANTALLA);

            imprimirEnPantalla("Producto actual:");
            eProducto_mostrarUno(listado[posicion]);

            imprimirEnPantalla("Producto nuevo:");
            eProducto_mostrarUno(registro);

            confirmacion = pedirConfirmacion("Confirma que los datos ingresados son correctos?");
        }

        if(confirmacion == 'S')
        {
            listado[posicion] = registro;
            //aca podria ordenarse con los datos nuevos;
            imprimirEnPantalla("\nEl Producto se modificà.");
        }
        else
        {
            imprimirEnPantalla("\nSe cancelà la gestiàn.");
        }
    }
    else
    {
        imprimirEnPantalla("\nEl ID de Producto ingresado por par metro no existe.");
    }
    ejecutarEnConsola(HACER_PAUSA);
}

void eProducto_ordenar(eProducto listado[], int limite, char orden[])
{
	int i;
	int j;
	eProducto aux;

	if(strcmp(orden, "idAsc") == 0)
	{
		for(i=0 ; i<limite-1 ; i++)
		{
			for(j=i+1 ; j<limite ; j++)
			{
				if(listado[i].idProducto > listado[j].idProducto)
				{
					aux = listado[i];
					listado[i] = listado[j];
					listado[j] = aux;
				}
			}
		}
	}
	else if(strcmp(orden, "idDesc") == 0)
	{
		for(i=0 ; i<limite-1 ; i++)
		{
			for(j=i+1 ; j<limite ; j++)
			{
				if(listado[i].idProducto < listado[j].idProducto)
				{
					aux = listado[i];
					listado[i] = listado[j];
					listado[j] = aux;
				}
			}
		}
	}
	else if(strcmp(orden, "nombreAsc") == 0)
	{
		for(i=0 ; i<limite-1 ; i++)
		{
			for(j=i+1 ; j<limite ; j++)
			{
				if(strcmp(listado[i].nombre, listado[j].nombre) > 0)
				{
					aux = listado[i];
					listado[i] = listado[j];
					listado[j] = aux;
				}
			}
		}
	}
	else if(strcmp(orden, "nombreDesc") == 0)
	{
		for(i=0 ; i<limite-1 ; i++)
		{
			for(j=i+1 ; j<limite ; j++)
			{
				if(strcmp(listado[i].nombre, listado[j].nombre) < 0)
				{
					aux = listado[i];
					listado[i] = listado[j];
					listado[j] = aux;
				}
			}
		}
	}
}
