#ifndef MENU_H_INCLUDED
#   define MENU_H_INCLUDED
#   define LARGO_ITEM_MENU 50
#   define NRO_MAX_OPCIONES_MENU 11

    typedef struct
    {
        int cantOpciones;
        int codigos[NRO_MAX_OPCIONES_MENU];
        char descripciones[NRO_MAX_OPCIONES_MENU][LARGO_ITEM_MENU];
        char titulo[LARGO_ITEM_MENU];
    } eMenu;

#endif // MENU_H_INCLUDED


/** \brief muestra en pantalla un tipo de dato menu
 *
 * \param menu const eMenu: el menu a mostrar
 * \return void
 *
 */
void mostrarMenu(const eMenu menu);


/** \brief pide al usuario que elija una opcion de menu recibido como parametro
 *
 * \param menu const eMenu: el menu de opciones a mostrar al usuario para pedir y validar la opcion seleccionada
 * \return int: el numero de opcion validada
 *
 */
int pedirOpcion(const eMenu menu);
