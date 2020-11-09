#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"

Employee* employee_new(){

    Employee* newEmp = NULL;
    newEmp = (Employee*) malloc(sizeof(Employee));

    if(newEmp != NULL)
    {
        newEmp->id = 0;
        newEmp->horasTrabajadas = 0;
        strcpy(newEmp->nombre, "");
        newEmp->sueldo = 0;
    }

    return newEmp;

}

Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr){

    int idIsvalid = validations_isValidNumber(idStr);
    int horasIsValid = validations_isValidNumber(horasTrabajadasStr);
    int sueldoIsValid = validations_isValidNumber(sueldoStr);

    if(!idIsvalid || !horasIsValid || !sueldoIsValid)
    {
        if (!idIsvalid)
        {
            printf("\nEl Id ingresado es invalido. Valor recibido: %s\n", idStr);
        }
        else if (!horasIsValid)
        {
            printf("\nLas horas ingresadas son invalidas. Valor recibido: %s\n", horasTrabajadasStr);
        }
        else if (!sueldoIsValid)
        {
            printf("\nEl sueldo ingresado es invalido. Valor recibido: %s\n", sueldoStr);
        }

        return NULL;

    }

    int idValue = atoi(idStr);
    int horasValue = atoi(horasTrabajadasStr);
    int sueldoValue = atoi(sueldoStr);

    Employee* newEmployee = employee_new();

    if(newEmployee != NULL)
    {
        if(
            !(!employee_setId(newEmployee,idValue) &&
              !employee_setNombre(newEmployee, nombreStr) &&
              !employee_setHorasTrabajadas(newEmployee,horasValue) &&
              !employee_setSueldo(newEmployee, sueldoValue)
             )
        )
        {
            printf("\nSucedio un problema, no se pudo ejecutar.\n");
            newEmployee = NULL;
            free(newEmployee);
        }

    }

    return newEmployee;
}


void employee_delete(Employee* this)
{
    free(this);
}

int employee_setId(Employee* this,int id){

    int todoOk = -1;

    if(this != NULL && id > 0)
    {
        this->id = id;
        todoOk = 0;
    }
    return todoOk;
}

int employee_getId(Employee* this,int* id){

    int todoOk = -1;

    if(this != NULL && id != NULL)
    {
        *id = this->id;
        todoOk = 0;
    }
    return todoOk;

}

int employee_setNombre(Employee* this,char* nombre){

    int todoOk = -1;
    int len;
    len = strlen(nombre);

    if(this != NULL && nombre != NULL && len> 0 && len < 0)
    {
        strcpy(this->nombre, nombre);
        todoOk = 0;
    }

    return todoOk;

}
int employee_getNombre(Employee* this,char* nombre){

    int todoOk = -1;

    if(this != NULL && nombre != NULL)
    {
        strcpy(nombre, this->nombre);
        todoOk = 0;
    }
    return todoOk;

}

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas){

    int todoOk = -1;

    if(this != NULL && horasTrabajadas < 0)
    {
        this->horasTrabajadas = horasTrabajadas;
        todoOk = 0;
    }

    return todoOk;

}
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas){

    int todoOk = -1;

    if(this != NULL && horasTrabajadas != NULL)
    {
        *horasTrabajadas = this->horasTrabajadas;
        todoOk = 0;
    }

    return todoOk;
}

int employee_setSueldo(Employee* this,int sueldo){

    int todoOk = -1;

    if(this != NULL && sueldo > 0)
    {
        this->sueldo = sueldo;
        todoOk = 0;
    }

    return todoOk;
}
int employee_getSueldo(Employee* this,int* sueldo){

    int todoOk = -1;

    if(this != NULL && sueldo != NULL)
    {
        *sueldo = this->sueldo;
        todoOk = 0;
    }

    return todoOk;
}




int employeeSortByName(void* empleadoA, void* empleadoB)
{

    int retorno = 0;
    Employee* empA;
    Employee* empB;

    if(empleadoA != NULL && empleadoB != NULL)
    {
        empA = empleadoA;
        empB = empleadoB;

        retorno = strcmp(empA->nombre, empB->nombre);
    }

    return retorno;
}


int employeeSortById(void* empleadoA, void* empleadoB)
{
    int retorno = 0;
    int sueldoA;
    int sueldoB;

    if(empleadoA != NULL && empleadoB != NULL)
    {
        if(employee_getId((Employee*)empleadoA, &sueldoA) == 0 &&
                employee_getId((Employee*)empleadoB, &sueldoB) == 0)
        {
            if(sueldoA > sueldoB)
            {
                retorno = 1;
            }
            else
            {
                retorno = -1;
            }
        }

    }
    return retorno;
}


int employeeSortByWorkHours(void* empleadoA, void* empleadoB)
{

    int retorno = 0;
    int horasA;
    int horasB;

    if(empleadoA != NULL && empleadoB != NULL)
    {
        if(employee_getHorasTrabajadas((Employee*)empleadoA, &horasA) == 0 &&
                employee_getHorasTrabajadas((Employee*)empleadoB, &horasB) == 0)
        {
            if(horasA > horasB)
            {
                retorno = 1;
            }
            else
            {
                retorno = -1;
            }
        }
    }

    return retorno;
}

int validations_isValidNumber(char* str)
{
    int retorno = 1;
    int len = strlen(str);

    for(int i = 0; i < len-1; i++)
    {
        if(str[i] < '0' || str[i] > '9')
        {
            retorno = 0;
            break;
        }
    }

    return retorno;
}
