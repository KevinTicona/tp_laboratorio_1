#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"


/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path, LinkedList* pArrayListEmployee)
{
    int retorno = 1;
    FILE *pFile = fopen(path,"r");

    if(pFile != NULL && path != NULL && pArrayListEmployee)
    {
        if(!parser_EmployeeFromText(pFile, pArrayListEmployee))
        {
            retorno = 0;
        }
        fclose(pFile);
    }
    return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path, LinkedList* pArrayListEmployee)
{
    int retorno = 1;

    FILE *pFile = fopen(path,"rb");

    if(pFile != NULL && path != NULL && pArrayListEmployee != NULL)
    {
        if(!parser_EmployeeFromBinary(pFile, pArrayListEmployee))
        {
            retorno = 0;
        }
        fclose(pFile);
    }
    return retorno;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{

    if(ll_isEmpty(pArrayListEmployee) != 0)
    {
        printf("\nNo hay ningun empleado agregado.\n");
        return  -1;
    }

    Employee* newEmployee = NULL;

    do
    {
        int newId;
        char newIdStr[50];
        char nombreStr[50];
        char sueldoStr[50];
        char horasStr[50];

        printf("\nIngrese nombre: ");
        fflush(stdin);
        gets(nombreStr);

        printf("\nIngrese horas trabajadas: ");
        fflush(stdin);
        gets(horasStr);

        printf("\nIngrese sueldo: ");
        fflush(stdin);
        gets(sueldoStr);

        Node* actualNode = pArrayListEmployee->pFirstNode;

        while(actualNode->pNextNode !=NULL)
        {
            actualNode = actualNode->pNextNode;
        }

        Employee* ultimoEmployee = (Employee*)actualNode->pElement;

        newId = ultimoEmployee->id + 1;
        itoa(newId, newIdStr, 10);

        newEmployee = employee_newParametros(newIdStr, nombreStr, horasStr, sueldoStr);

        if(newEmployee != NULL)
        {
            ll_add(pArrayListEmployee, newEmployee);
            printf("\n El empleado se creo exitosamente.");
        }
        else
        {
            printf("\nOcurrio un error. El empleado no fue creado.\n");
        }
    }
    while(newEmployee == NULL);

    return 0;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    char employeeIdStr[50];
    char nombreStr[50];

    int employyeIdModifi;
    int idValid;
    int actualNodeIndex;
    int llSize;
    int opcion;
    int opcionValid;
    int horas;
    int sueldo;
    int horasValid;
    int sueldoValid;

    Employee* actualEmployee;
    Node* actualNode;

    if(ll_isEmpty(pArrayListEmployee) != 0)
    {
        printf("\nNo hay ningun empleado agregado.\n");
        return  -1;
    }

    do
    {
        printf("\nIngrese el Id del Empleado que desea Modificar: \n");
        fflush(stdin);
        gets(employeeIdStr);

        idValid = validations_isValidNumber(employeeIdStr);

        if(!idValid)
        {
            printf("\n El Id ingresado es invalido.\n");
        }
    }
    while(!idValid);

    employyeIdModifi = atoi(employeeIdStr);

    actualNodeIndex = 0;

    llSize = ll_len(pArrayListEmployee);

    actualNode = pArrayListEmployee->pFirstNode;

    while(actualNodeIndex < llSize)
    {
        actualEmployee = (Employee*)ll_get(pArrayListEmployee, actualNodeIndex);

        if(actualEmployee->id == employyeIdModifi)
        {
            imprimir_Emcabezado();
            imprimir_UnEmpleado(actualEmployee);
            imprimir_MenuDeModificaciones();

            opcionValid = getopcion(&opcion,"\nOpcion invalida.\n", 1, 4);

            if(!opcionValid)
            {
                switch(opcion)
                {
                case 1:
                    printf("Ingrese el nuevo nombre: ");
                    fflush(stdin);
                    gets(nombreStr);
                    if(!employee_setNombre(actualEmployee, nombreStr))
                    {
                        printf("\nModificacion realizada con exito.\n");
                    }
                    else
                    {
                        printf("\nNombre invalido.\n");
                    }
                    break;

                case 2:
                    printf("\nIngrese cantidad de horas:\n");
                    fflush(stdin);
                    horasValid = scanf("%d",&horas);
                    while(!horasValid || horas < 0)
                    {
                        printf("\nDato Invalido. Ingrese cantidad de horas: ");
                        fflush(stdin);
                        horasValid = scanf("%d",&horas);
                    }
                    employee_setHorasTrabajadas(actualEmployee,horas);
                    printf("\nModificacion realizada con exito.\n");
                    break;
                case 3:
                    printf("\nIngrese el nuevo sueldo:\n");
                    fflush(stdin);
                    sueldoValid = scanf("%d",&sueldo);
                    while(sueldoValid || sueldo < 0)
                    {
                        printf("Dato invalido. Ingrese de nuevo el Sueldo: ");
                        fflush(stdin);
                        sueldoValid = scanf("%d",&sueldo);
                    }
                    employee_setSueldo(actualEmployee,sueldo);
                    printf("\nModificacion exitosa.\n");
                    break;
                case 4:
                    printf("\nRegresando al menu Anterior\n");
                    break;
                }
            }
            return 0;
        }
        actualNode = actualNode->pNextNode;
        actualNodeIndex++;
    }
    printf("\nNo se encontra un empleado con ese Id\n");

    return -1;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    int idValid;
    int actualNodeIndex;
    int llSize;
    int employeIdDelete;
    char employeIdDeleteStr[50];
    char confirmation;

    Employee* actualEmployee;
    Node* actualNode;

    if(ll_isEmpty(pArrayListEmployee) == 1)
    {
        printf("\nNo hay ningun empleado agregado.\n");
        return -1;
    }

    do
    {
        printf("\nIngrese el Id del Empleado que desea Remover: \n");
        fflush(stdin);
        gets(employeIdDeleteStr);

        idValid = validations_isValidNumber(employeIdDeleteStr);

        if(!idValid)
        {
            printf("\n El Id ingresado es invalido.\n");
        }
    }
    while(!idValid);

    llSize = ll_len(pArrayListEmployee);
    employeIdDelete = atoi(employeIdDeleteStr);
    actualNode = pArrayListEmployee->pFirstNode;


    while(actualNodeIndex <llSize)
    {
        actualEmployee = (Employee*)ll_get(pArrayListEmployee, actualNodeIndex);

        if(actualEmployee->id == employeIdDelete)
        {
            imprimir_Emcabezado();
            imprimir_UnEmpleado(actualEmployee);
            printf("Confirmar baja? s - si; n - no\n");
            fflush(stdin);
            scanf("%c", &confirmation);
            confirmation = tolower(confirmation);
            while(confirmation != 's' && confirmation != 'n')
            {
                printf("Opción invalida. s - si; n - no\n");
                fflush(stdin);
                scanf("%c", &confirmation);
                confirmation = tolower(confirmation);
            }

            if(confirmation == 's')
            {
                ll_remove(pArrayListEmployee, actualNodeIndex);
                printf("\n El Empleado con Id %d ha sido eliminado.\n", employeIdDelete);
            }
            else if(confirmation == 'n')
            {
                 printf("La baja fue cancelada por el usuario.\n");
            }
            return 0;
        }

        actualNode = actualNode->pNextNode;
        actualNodeIndex++;
    }

    printf("\nNo se encontro a ningun Empleado con el ID %d que ingreso.\n", employeIdDelete);

    return -1;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    if(ll_isEmpty(pArrayListEmployee) == 1)
    {
        printf("\nNo hay ningun empleado registrado en el sistema.\n");
        return  0;
    }

    imprimir_Empleados(pArrayListEmployee);

    return 1;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    int opcionValid = 0;
    int opcion = 0;

    if(ll_isEmpty(pArrayListEmployee) == 1)
    {
        printf("\nNo hay ningun empleado registrado en el sistema.\n");
        return  0;
    }

    do
    {
        imprimir_MenuDeOrdenamiento();
        opcionValid = getopcion(&opcion,"\nOpcion invalida.\n", 1, 5);
        if(!opcionValid)
        {
            switch(opcion)
            {
            case 1:
                printf("Ordenando por Nombres...");
                ll_sort(pArrayListEmployee, employee_SortByName, 1);
                printf("\nEmpleados ordenados por nombres!\n");
                system("pause");
                controller_ListEmployee(pArrayListEmployee);
                break;
            case 2:
                printf("Ordenando por Id...");
                ll_sort(pArrayListEmployee, employee_SortById, 1);
                printf("\nEmpleados ordenados por ID!\n");
                system("pause");
                controller_ListEmployee(pArrayListEmployee);
                break;
            case 3:
                printf("Ordenando por Horas Trabajadas...");
                ll_sort(pArrayListEmployee, employee_SortByWorkHours, 1);
                printf("\nEmpleados ordenados por horas trabajas!\n");
                system("pause");
                controller_ListEmployee(pArrayListEmployee);
                break;
            case 4:
                printf("Ordenando por Sueldo...");
                ll_sort(pArrayListEmployee, employee_SortBySalary, 1);
                printf("\nEmpleados ordenados por sueldo!\n");
                system("pause");
                controller_ListEmployee(pArrayListEmployee);
                break;
            case 5:
                printf("Volviendo al menu principal.");
                break;
            }
            system("pause");
        }
    }
    while(opcion != 5);

    return 1;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path, LinkedList* pArrayListEmployee)
{
    FILE *pFile;
    pFile = fopen(path, "w");

    if (pFile == NULL || pArrayListEmployee == NULL)
    {
        return -1;
    }

    int actualNodeIndex = 0;
    int llSize = ll_len(pArrayListEmployee);

    Employee* actualEmployee;
    Node* actualNode = pArrayListEmployee->pFirstNode;

    fprintf(pFile, "id,nombre,horasTrabajas,sueldo\n");

    while(actualNodeIndex < llSize)
    {
        actualEmployee = (Employee*)ll_get(pArrayListEmployee, actualNodeIndex);

        fprintf(pFile, "%d,%s,%d,%d\n",
                actualEmployee->id,
                actualEmployee->nombre,
                actualEmployee->horasTrabajadas,
                actualEmployee->sueldo);

        actualNode = actualNode->pNextNode;
        actualNodeIndex++;
    }

    fclose(pFile);

    printf("\nLos cambios se guardaron con exito!\n");

    return 0;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path, LinkedList* pArrayListEmployee)
{
    FILE* pFile = fopen(path, "wb");

    if (pFile == NULL || pArrayListEmployee == NULL)
    {
        return -1;
    }

    int actualNodeIndex;
    int llSize = ll_len(pArrayListEmployee);

    Employee* actualEmployee;
    Node* actualNode = pArrayListEmployee->pFirstNode;

    while(actualNodeIndex < llSize)
    {
        actualEmployee = (Employee*)ll_get(pArrayListEmployee, actualNodeIndex);

        fwrite(actualEmployee, sizeof(Employee), 1, pFile);

        actualNode = actualNode->pNextNode;
        actualNodeIndex++;
    }

    fclose(pFile);

    printf("\nLos cambios se guardaron con exito!\n");

    return 0;
}

int controller_freeResources(LinkedList* pArrayListEmployee)
{
    Node* actualNode = pArrayListEmployee->pFirstNode;
    Node* AuxNode;

    while(actualNode != NULL)
    {
        AuxNode = actualNode;
        actualNode = actualNode->pNextNode;
        free(AuxNode);
    }

    ll_deleteLinkedList(pArrayListEmployee);

    return 1;
}
