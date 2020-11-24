#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"

static int esNumerica(char* cadena,int limite);

Employee* employee_new()
{

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

Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr)
{

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

int employee_setId(Employee* this,int id)
{

    int todoOk = -1;

    if(this != NULL && id > 0)
    {
        this->id = id;
        todoOk = 0;
    }
    return todoOk;
}

int employee_getId(Employee* this,int* id)
{

    int todoOk = -1;

    if(this != NULL && id != NULL)
    {
        *id = this->id;
        todoOk = 0;
    }
    return todoOk;

}

int employee_setNombre(Employee* this,char* nombre)
{

    int todoOk = -1;
    int len;
    len = strlen(nombre);

    if(this != NULL && nombre != NULL && len> 0 && len < 120)
    {
        strcpy(this->nombre, nombre);
        todoOk = 0;
    }

    return todoOk;

}

int employee_getNombre(Employee* this,char* nombre)
{

    int todoOk = -1;

    if(this != NULL && nombre != NULL)
    {
        strcpy(nombre, this->nombre);
        todoOk = 0;
    }
    return todoOk;

}

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{

    int todoOk = -1;

    if(this != NULL && !(horasTrabajadas < 0))
    {
        this->horasTrabajadas = horasTrabajadas;
        todoOk = 0;
    }

    return todoOk;

}

int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{

    int todoOk = -1;

    if(this != NULL && horasTrabajadas != NULL)
    {
        *horasTrabajadas = this->horasTrabajadas;
        todoOk = 0;
    }

    return todoOk;
}

int employee_setSueldo(Employee* this,int sueldo)
{

    int todoOk = -1;

    if(this != NULL && sueldo > 0)
    {
        this->sueldo = sueldo;
        todoOk = 0;
    }

    return todoOk;
}

int employee_getSueldo(Employee* this,int* sueldo)
{

    int todoOk = -1;

    if(this != NULL && sueldo != NULL)
    {
        *sueldo = this->sueldo;
        todoOk = 0;
    }

    return todoOk;
}

int employee_SortByName(void* empleadoA, void* empleadoB)
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


int employee_SortById(void* empleadoA, void* empleadoB)
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


int employee_SortByWorkHours(void* empleadoA, void* empleadoB)
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

int employee_SortBySalary(void* empleadoA, void* empleadoB)
{
    int retorno = 0;
    int sueldoA;
    int sueldoB;

    if(empleadoA != NULL && empleadoB != NULL)
    {
        if(employee_getSueldo((Employee*)empleadoA, &sueldoA) == 0 &&
                employee_getSueldo((Employee*)empleadoB, &sueldoB) == 0)
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

int employee_getIdStr(Employee* this,char* id)
{
    int retorno = -1;
    if(this != NULL && id != NULL)
    {
        sprintf(id,"%d",this->id);
        retorno = 0;
    }
    return retorno;
}

int employee_getSueldoStr(Employee* this,char* sueldo)
{
    int retorno = -1;
    if(this != NULL && sueldo != NULL)
    {
        sprintf(sueldo,"%d",this->sueldo);
        retorno = 0;
    }
    return retorno;
}

int employee_getHorasTrabajadasStr(Employee* this,char* horasTrabajadas)
{
    int retorno = -1;
    if(this != NULL && horasTrabajadas != NULL)
    {
        sprintf(horasTrabajadas,"%d",this->horasTrabajadas);
        retorno = 0;
    }
    return retorno;
}

int employee_setIdStr(Employee* this,char* id)
{
    int retorno = -1;
    if(this != NULL && id != NULL)
    {
        if(esNumerica(id,1000))
        {
            this->id = atoi(id);
            retorno = 0;
        }
    }
    return retorno;
}

int employee_setSueldoStr(Employee* this,char* sueldo)
{
    int retorno = -1;
    if(this != NULL && sueldo != NULL)
    {
        if(esNumerica(sueldo,1000))
        {
            this->sueldo = atoi(sueldo);
            retorno = 0;
        }
    }
    return retorno;
}

int employee_setHorasTrabajadasStr(Employee* this,char* horasTrabajadas)
{
    int retorno = -1;
    if(this != NULL && horasTrabajadas != NULL)
    {
        if(esNumerica(horasTrabajadas,1000))
        {
            this->horasTrabajadas = atoi(horasTrabajadas);
            retorno = 0;
        }
    }
    return retorno;
}

void imprimir_UnEmpleado(Employee* unEmployee)
{
    printf("\n%4d %20s                  %4d            %4d\n",
           unEmployee->id,
           unEmployee->nombre,
           unEmployee->horasTrabajadas,
           unEmployee->sueldo);
}

void imprimir_Emcabezado()
{
    system("cls");
    printf("  ID              Nombre             Horas Trabajadas    Salario \n");
    printf("-----------------------------------------------------------------\n");
}

void imprimir_MenuDeModificaciones()
{
    printf("\n\n");
    printf("1- Modificar nombre.\n");
    printf("2- Modificar horas trabajadas.\n");
    printf("3- Modificar sueldo.\n");
    printf("4- Volver atras.\n");
    printf("Ingrese una opcion:");
}

int imprimir_Empleados(LinkedList* pArrayListEmployee)
{
    int actualNodeIndex = 0;
    int llSize = ll_len(pArrayListEmployee);

    Employee* actualEmployee;
    Node* actualNode = pArrayListEmployee->pFirstNode;

    system("cls");
    printf("                          Empleados                           \n");
    printf("  ID             Nombre            Horas Trabajadas    Salario \n");
    printf("----------------------------------------------------------------\n");

    while (actualNodeIndex < llSize)
    {
        actualEmployee = (Employee*)ll_get(pArrayListEmployee, actualNodeIndex);

        imprimir_UnEmpleado(actualEmployee);

        actualNode = actualNode->pNextNode;
        actualNodeIndex++;
    }

    return 0;
}

void imprimir_MenuDeOrdenamiento()
{
    system("cls");
    printf("                  Menu de Ordenamiento de los Empleados                 \n");
    printf("-------------------------------------------------------------------------\n");
    printf("1- Ordenar por nombre.\n");
    printf("2- Ordenar por ID.\n");
    printf("3- Ordenar por horas trabajadas.\n");
    printf("4- Ordenar por sueldo.\n");
    printf("5- Volver atras.\n");
    printf("Ingrese una opcion:");
}

void imprimir_Menu()
{
    system("cls");
    printf("                              Menu Empleado ABM                                \n");
    printf("--------------------------------------------------------------------------------\n");
    printf("1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).\n");
    printf("2. Cargar los datos de los empleados desde el archivo data.bin (modo binario).\n");
    printf("3. Alta de empleado.\n");
    printf("4. Modificar datos de empleado.\n");
    printf("5. Baja de empleado.\n");
    printf("6. Listar empleados.\n");
    printf("7. Ordenar empleados.\n");
    printf("8. Guardar los datos de los empleados en el archivo data.csv (modo texto).\n");
    printf("9. Guardar los datos de los empleados en el archivo data.bin (modo binario).\n");
    printf("10. Salir.\n");
}

int getopcion(int* pResult, char* errorMsj, int min, int max)
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

static int esNumerica(char* cadena,int limite)
{

    int retorno = 1;
    int i = 0;

    if(cadena != NULL && limite > 0)
    {
        retorno = 1;
        if(cadena[0] == '-' || cadena[0] == '+')
        {
            i = 1;
        }
        for(; cadena[i] != '\0'; i++)
        {
            if(cadena[i] < '0' || cadena[i] > '9' )
            {
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}
