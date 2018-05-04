#ifndef GENERAL_H_INCLUDED
#   define GENERAL_H_INCLUDED
#   define DEFINIR_MACRO_STRING(nombre_macro) #nombre_macro
#   define LIMPIAR_PANTALLA DEFINIR_MACRO_STRING(cls)
#   define HACER_PAUSA DEFINIR_MACRO_STRING(pause)
#   define LARGO_TITULO 1000
#endif // GENERAL_H_INCLUDED

/** \brief corre comandos en la consola del sistema operativo
 *
 * \param  lineaDeComando const char*: el string del comando
 * \return void
 *
 */
void ejecutarEnConsola(const char *);


/** \brief pide confirmacion por S o N al usuario y devuelve la letra validada
 *
 * \param  mensajeAlUsuario const char*: mensaje al usuario
 * \return char: S o N validado
 *
 */
char pedirConfirmacion(const char *);


/** \brief pide que se ingrese un numero entero
 *
 * \param mensajeIngreso char[] const: el mensaje al usuario
 * \return int: el numero entero
 *
 */
int pedirInt(const char[]);


/** \brief pide que se ingrese un numero int y lo valida
 *
  * \param mensajeIngreso char[] const: el mensaje al usuario
  * \param mensajeReingreso char[] const: el mensaje al usuario en caso de error
 * \param limiteInferior const int: valor inferior válido
 * \param limiteSuperior const int: valor superior válido
 * \return int: el número validado
 *
 */
int pedirIntValido(const char[], const char[], const int, const int);


/** \brief pide que se ingrese un numero float
 *
 * \param mensajeIngreso char[] const: el mensaje al usuario
 * \return float: el numero float
 *
 */
float pedirFloat(const char[]);


/** \brief pide que se ingrese un numero float y lo valida
 *
  * \param mensajeIngreso char[] const: el mensaje al usuario
  * \param mensajeReingreso char[] const: el mensaje al usuario en caso de error
 * \param limiteInferior const float: valor inferior válido
 * \param limiteSuperior const float: valor superior válido
 * \return float: el número validado
 *
 */
float pedirFloatValido(const char[], const char[], const float, const float);


/** \brief pide que se ingrese una cadena de texto y la asigna a una variable
 *
 * \param retorno char*: la variable donde se retorna la cadena ingresada
 * \param mensajeIngreso char[] const: el mensaje al usuario
 * \return void
 *
 */
void pedirString(char *, const char[]);


/** \brief pide que se ingrese una cadena de texto, valida su tamaño y la asigna a una variable
 *
 * \param retorno char*: la variable donde se retorna la cadena ingresada
 * \param mensajeIngreso char[] const: el mensaje al usuario
 * \param mensajeReingreso char[] const: el mensaje al usuario en caso de error
 * \param limite int: el límite para la cantidad de caracteres
 * \return void
 *
 */
void pedirStringValido(char *, const char[], const char[], const int limite);


/** \brief calcula el promedio entre dos numeros float
 *
 * \param numero1 float: el primer numero
 * \param numero2 float: el segundo numero
 * \return float: el promedio entre ambos numeros
 *
 */
float calcularPromedio(float, float);


/** \brief busca coincidencia de un valor entero dentro de un array
 *
 * \param buscar const int: el numero entero a buscar
 * \param array[] const int: el array donde buscar
 * \param cant const int: la cantidad de elementos del array
 * \return int la posicion del elemento buscado. -1 en caso de no encontrarlo
 *
 */
int buscarEnArrayInt(const int, const int[], const int);


/** \brief escribe el texto recibido con un printf
 *
 * \param texto const char*: la cadena de texto a mostrar
 * \return void
 *
 */
void imprimirEnPantalla(const char *);


/** \brief Recibe un texto y lo decora como título
 *
 * \param  char*: el texto a decorar
 * \return void
 *
 */
void generarTitulo(char *);


/** \brief Recibe un texto y lo muestra decorado como título
 *
 * \param  const char*: el texto a mostrar
 * \return void
 *
 */
void imprimirTitulo(const char *);
