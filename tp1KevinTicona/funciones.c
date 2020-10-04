#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
/** \brief funcion suma
 *
 * \param a float
 * \param b float
 * \return resultado float
 *
 */
float sumar (float a,float b)
{

    float resultado;

    resultado = a + b;

    return resultado;
}

/** \brief funcion restar
 *
 * \param   a float
 * \param   b float
 * \return  resultado float
 *
 */
float resta (float a, float b)
{

    float resultado;

    resultado = a - b;

    return resultado;

}

/** \brief funcion division validando que la b sea distinto de 0
 *
 * \param a float
 * \param b float
 * \return resultado en float
 *
 */
float division(float a, float b)
{

    float resultado;

    resultado = a / b;

    return resultado;
}

/** \brief funcion multiplicar
 *
 * \param a float
 * \param b float
 * \return resultado float
 *
 */
float multiplicacion (float a, float b)
{
    float resultado;

    resultado = a * b;

    return resultado;
}

/** \brief funcion factorial
 *
 * \param a int
 * \return int
 *
 */
int factorial(int a)
{

    int fact = 1;

    if(a < 1)
    {

        fact= - 1;
    }
    else
    {
        for(int i = a; i > 0; i--)
        {
            fact = fact * i;
            //fact *= i;
        }
    }

    return fact;
}

