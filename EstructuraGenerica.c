#include "Producto.h"
#include "General.h"
#include "Menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void eProducto_init(eProducto listado[], int limite)
{
	int i;

	if(limite > 0 && listado != NULL)
	{
		for(i=0 ; i<limite ; i++)
		{
			listado[i].estado= LIBRE;
			listado[i].idGenerica= 0;
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
				if(listado[i].idGenerica > retorno)
				{
					 retorno = listado[i].idGenerica;
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
			if(listado[i].estado == OCUPADO && listado[i].idGenerica == id)
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
	 printf("\n %s - %d - %d", parametro.nombre, parametro.idGenerica, parametro.estado);

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

void pedirNombre(char *retorno)
{
	char mensajeReingreso[100];
    strcat(mensajeReingreso, "\nReingrese un nombre de hasta ");
	strcat(mensajeReingreso, (char *)LARGO_NOMBRE_PRODUCTO);
	strcat(mensajeReingreso, " caracteres");

	pedirStringValido(retorno, "\nIngrese nombre: ", mensajeReingreso, LARGO_NOMBRE_PRODUCTO);
}

eProducto eProducto_pedirIngreso(eProducto listado[], int limite)
{
	eProducto retorno;

	retorno.idGenerica = eProducto_siguienteId(listado, limite);

	pedirNombre((char *)&(retorno.nombre));

    //retorno.demasCampos

	retorno.estado = OCUPADO;

	return retorno;
}

void eProducto_alta(eProducto listado[], int limite)
{
	eProducto registro;
	char confirmacion;
	int posicion;

	posicion = eProducto_buscarLugarLibre(listado, limite);
	if(posicion < 0)
	{
		imprimirEnPantalla("\nNo hay m s lugares disponibles para altas de Producto.");
	}
	else
	{
		ejecutarEnConsola(LIMPIAR_PANTALLA);
		imprimirTitulo(TITULO_ALTA);
		registro = eProducto_pedirIngreso(listado, limite);
		eProducto_mostrarUno(registro);

		confirmacion = pedirConfirmacion("Confirma que los datos ingresados son correctos?");

		if(confirmacion == 'S')
		{
			listado[posicion] = registro;
			//aca se ordenaria la lista
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
        imprimirTitulo(TITULO_BAJA);

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
            registro->idGenerica = pedirIntValido("Ingrese nuevo ID", "El ID debe ser un n£mero entero mayor que cero", 1, 99999999);
            break;
        case 2:
            pedirNombre((char *)&registro->nombre);
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
    imprimirTitulo(TITULO_MODIFICACION);

    registro.idGenerica = pedirIntValido("\n\nIngrese el ID de Producto a modificar: ", "El ID debe ser un n¡mero mayor que cero", 1, 99999999);

    posicion = eProducto_buscarPorId(listado, limite, registro.idGenerica);
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
				if(listado[i].idGenerica > listado[j].idGenerica)
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
				if(listado[i].idGenerica < listado[j].idGenerica)
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

void eProducto_gestion(eProducto listado[], int limite)
{
    eMenu menuProducto = {
                            4, //cantidad de opciones
                            {1,2,3,9}, //codigos
                            {"1. Alta","2. Baja","3. Modificaci¢n","9. Volver al men£ principal"}, //descripciones
                            {TITULO_GESTION} //titulo del menu
                            };
    int opcion;
    char volverAlMain = 'N';

    do
    {
        ejecutarEnConsola(LIMPIAR_PANTALLA);
        opcion = pedirOpcion(menuProducto);
        switch(opcion)
        {
            case 1:
                eProducto_alta(listado, limite);
                break;
            case 2:
                eProducto_baja(listado, limite);
                break;
            case 3:
                eProducto_modificacion(listado, limite);
                break;
            case 4:
                imprimirEnPantalla(menuProducto.descripciones[opcion-1]);ejecutarEnConsola(HACER_PAUSA);
                break;
            case 9:
                volverAlMain = 'S';
                break;
        }

    }
    while(volverAlMain == 'N');
}
