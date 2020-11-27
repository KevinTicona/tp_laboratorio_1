#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../inc/validaciones.h"
#include "../inc/LinkedList.h"
#include "../inc/clientes.h"
#include "../inc/notebooks.h"

int validations_getOption(int* pResult, char* errorMsj, int min, int max)
{
    int error = -1;
    int opcion;
    int validate;
    if(pResult != NULL && errorMsj != NULL && min <= max)
    {
        do
        {
            printf("\nIngrese opcion: ");
            fflush(stdin);
            scanf("%d", &opcion);
            validate = isdigit(opcion);
            if((opcion >= min && opcion <= max) && !validate)
            {
                *pResult = opcion;
                error = 0;
            }
            else
            {
                printf("%s\n", errorMsj);
                system("pause");
            }
        }
        while(error != 0);
    }
    return error;
}

int validations_charOnly(char* str)
{
    int i = 0;
    while (str[i])
    {
        if (!isalpha(str[i]) && str[i] != ' ' && str[i] != '-'&& str[i] != '_')
        {
            return -1;
        }
        i++;
    }

    return 0;
}

int validations_isValidNumber(char* str)
{
    int retorno = 1;
    int len = strlen(str);

    for(int i = 0; i < len; i++)
    {
        if(str[i] < '0' || str[i] > '9')
        {
            retorno = 0;
            break;
        }
    }

    return retorno;
}

void validations_formatStr(char* str)
{
    int len;
    strlwr(str);
    str[0] = toupper(str[0]);
    len = strlen(str);
    for(int i = 0; i < len; i++)
    {
        if(str[i] == ' ')
        {
            i++;
            if(str[i] >= 'a' && str[i] <= 'z')
            {
                str[i] = toupper(str[i]);
            }
        }
    }
}

int validations_isValidName(char* nombre)
{
    int len = strlen(nombre);
    int valid = validations_charOnly(nombre);
    if(len > 0 && len < 100 && !valid)
    {
        return 1;
    }

    return 0;
}

int validations_isValidType(char* type)
{
    int len = strlen(type);
    int valid = validations_charOnly(type);

    if(!valid && len < 50 && len > 0)
    {
        validations_formatStr(type);
        if(
            strcmp(type, "Economica") == 0 ||
            strcmp(type, "Normal") == 0 ||
            strcmp(type, "Gamer") == 0
        )
        {
            return 1;
        }
    }

    return 0;
}

int validations_isValidSex(char* sexo)
{
    strlwr(sexo);
    if(strcmp(sexo,"m") == 0 || strcmp(sexo,"f") == 0)
    {
        return 1;
    }
    return 0;
}

int validations_isValidEdad(char* edad)
{
    int resultadoValido = validations_isValidNumber(edad);
    int intEdad;

    if(resultadoValido == 1)
    {
        intEdad = atoi(edad);
        if(intEdad >= 0 && intEdad <= 15)
        {
            return 1;
        }
    }

    return 0;
}

int validations_isValidPrecio(char* Precio)
{
    int resultadoValido = validations_isValidNumber(Precio);
    int auxPrecio;

    if(resultadoValido == 1)
    {
        auxPrecio = atoi(Precio);
        if(auxPrecio >= 0)
        {
            return 1;
        }
    }

    return 0;
}

int validations_isValidIdCliente(char* idCliente)
{
    int resultadoValido = validations_isValidNumber(idCliente);
    int auxId;

    if(resultadoValido == 1)
    {
        auxId = atoi(idCliente);
        if(auxId >= 1 && auxId <= 100)
        {
            return 1;
        }
    }

    return 0;
}

int validations_isValidID(char* id)
{
    int resultadoValido = validations_isValidNumber(id);
    int intID;

    if(resultadoValido == 1)
    {
        intID = atoi(id);
        if(intID >= 0)
        {
            return 1;
        }
    }

    return 0;
}
//-----------------------------------------------------------

