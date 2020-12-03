#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"
#include "../inc/clientes.h"
#include "../inc/validaciones.h"


eCliente* cliente_new()
{
    eCliente* newCliente = (eCliente*) malloc(sizeof(eCliente));

    if(newCliente != NULL)
    {
        newCliente->id = 0;
        strcpy(newCliente->nombre, "");
        strcpy(newCliente->sexo, "");
    }
    return newCliente;
}

eCliente* cliente_newParams(char* id, char* nombre, char* sexo)
{
    int validIdResult = validations_isValidNumber(id);
    int validId;

    if(!validIdResult)
    {
        printf("\nEl Id del Cliente es invalido. Valor recibido: %s\n", id);
        return NULL;
    }

    validId = atoi(id);

    eCliente* newCliente = cliente_new();

    if(newCliente != NULL)
    {
        if(!(!cliente_setId(newCliente,validId) &&
                !cliente_setNombre(newCliente,nombre) &&
                !cliente_setSexo(newCliente,sexo)
            ))
        {
            printf("\nOcurrio un problema al inicializar las propiedades del nuevo Cliente. El mismo no sera creado.\n");
            newCliente = NULL;
            free(newCliente);
        }
    }
    return newCliente;
}

void cliente_delete(eCliente* this)
{
    free(this);
}

int cliente_setId(eCliente* this,int id)
{
    int error = -1;

    if(this != NULL && id > 0)
    {
        this->id = id;
        error = 0;
    }

    return error;
}

int cliente_getId(eCliente* this,int* id)
{
    int error = -1;

    if(this != NULL && id != NULL)
    {
        *id = this->id;
        error = 0;
    }
    return error;
}

int cliente_setNombre(eCliente* this,char* nombre)
{
    int error = -1;

    if(this != NULL && nombre != NULL && validations_isValidName(nombre))
    {
        strcpy(this->nombre, nombre);
        error = 0;
    }

    return error;
}

int cliente_getNombre(eCliente* this,char* nombre)
{
    int error = -1;

    if(this != NULL && nombre != NULL)
    {
        strcpy(nombre, this->nombre);
        error = 0;
    }
    return error;
}

int cliente_setSexo(eCliente* this,char* sexo)
{
    int error = -1;

    if(validations_isValidSex(sexo))
    {
        strcpy(this->sexo, sexo);
        error = 0;
    }

    return error;
}

int cliente_getSexo(eCliente* this,char* sexo)
{
    int error = -1;

    if(this != NULL && sexo != NULL)
    {
        strcpy(sexo, this->sexo);
        error = 0;
    }
    return error;
}

eCliente* cliente_searchByID(LinkedList* this,int id)
{
    eCliente* auxCliente;
    int len = ll_len(this);
    int index = 0;
    Node* currentNode = this->pFirstNode;

    if(this != NULL)
    {
        while (index < len)
        {
            auxCliente = (eCliente*)ll_get(this,index);

            if(auxCliente->id == id)
            {
                break;
            }

            currentNode = currentNode->pNextNode;
            index++;
        }
    }
    return auxCliente;
}
