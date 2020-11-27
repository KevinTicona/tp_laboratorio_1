#ifndef VALIDACIONES_H_INCLUDED
#define VALIDACIONES_H_INCLUDED

/** \brief Recorre una lista de test para linked list y los va ejecutando
 *
 * \param int test numero de test
 *
 */
void validations_testLL(int test);

/** \brief Valida un input de una opcion con un numero entero
 *
 * \param int* pResult puntero a resultado
 * \param char* errorMsj mensaje de error
 * \param int min minimo
 * \param int max maximo
 * \return int Retorna (-1) si hay Error [Tamaño invalido, puntero
 *  NULL o minimo mayor que maximo] - (0) si esta todo Ok
 *
 */
int validations_getOption(int* pResult, char* errorMsj, int min, int max);

/** \brief Valida que un string solo tenga caracteres alfabeticos
 *
 * \param char str[]
 * \return int Retorna (-1) para error [uno o mas caracteres no alfabeticos]
 * - (0) si esta todo Ok
 *
 */
 int validations_charOnly(char* str);

 /** \brief Valida que un nombre tenga formato correcto
 *
 * \param char* name
 * \return Retorna FALSE (0) si hay errores, TRUE(1) Si esta todo OK.
 *
 */
 int validations_isValidName(char* nombre);

 /** \brief Valida que un literal de cadena sea un entero.
 *
 * \param Char str
 * \return Retorna FALSE (0) si hay errores, TRUE(1) Si esta todo OK.
 *
 */
 int validations_isValidNumber(char* str);

 /** \brief Otorga formato a un nombre
 *
 * \param char* Str string a formatear
 *
 */
void validations_formatStr(char* str);

 /** \brief Valida que un ID sea valido.
 *
 * \param Char* id
 * \return Retorna [1] Si esta todo OK, [0] si hay errores
 *
 */
 int validations_isValidID(char* id);

/** \brief Valida que un tipo sea valido.
 *
 * \param Char* tipo
 * \return Retorna [1] Si esta todo OK, [0] si hay errores
 *
 */
 int validations_isValidType(char* type);

/** \brief Valida que un sexo sea valido.
 *
 * \param Char* sexo
 * \return Retorna [1] Si esta todo OK, [0] si hay errores
 *
 */
 int validations_isValidSex(char* sex);

 /** \brief Valida que una edad sea valida.
 *
 * \param Char* edad
 * \return Retorna [1] Si esta todo OK, [0] si hay errores
 *
 */
 int validations_isValidEdad(char* edad);

  /** \brief Valida que un id_dueno sea valido.
 *
 * \param Char* id_dueno
 * \return Retorna [1] Si esta todo OK, [0] si hay errores
 *
 */
 int validations_isValid_IDDueno(char* idDueno);


int validations_isValidIdCliente(char* idCliente);

int validations_isValidPrecio(char* Precio);

int validations_isValidID(char* id);

#endif // VALIDACIONES_H_INCLUDED
