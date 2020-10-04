#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "arrayEmployees.h"

#ifndef ARRAYEMPLOYEES_C_INCLUDED
#define ARRAYEMPLOYEES_C_INCLUDED

/** \brief To indicate that all position in the array are empty,
 * this function put the flag (isEmpty) in TRUE in all
 * position of the array
 * \param list Employee* Pointer to array of employees
 * \param len int Array length
 * \return int Return (1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */

int initEmployees(eEmployee list[], int len)
{
    int error = 1;

    if(list !=NULL && len > 0 && len <= 1000)
    {
        for(int i = 0; i<len; i++)
        {
            list[i].isEmpty = 1;
        }
        error = 0;
    }
    return error;
}
/** \brief add in a existing list of employees the values received as parameters
 * in the first empty position
 * \param list employee*
 * \param len int
 * \param id int
 * \return int Return (1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 */

int addEmployee(eEmployee list[], int len, int id)
{

    int error = 1;
    int indice;
    int flag;

    eEmployee nuevaPersona;

    if(list!=NULL && len> 0 && len <= 1000&& id >= 0)
    {

        system("cls");
        printf(" *** Alta de Personas ***\n");

        indice = findFree(list, len);
        if(indice== -1)
        {
            printf("El sistema esta completo.\n");
        }
        else
        {
            nuevaPersona.id = id;
            nuevaPersona.isEmpty = 0;

            printf("Ingrese nombre: ");
            fflush(stdin);
            gets(nuevaPersona.name);
            flag = validarCadena(nuevaPersona.name);

            while(strlen(nuevaPersona.name) ==0 || strlen(nuevaPersona.name)> 20 || flag != 0 )
            {
                printf("\nDato invalido. ReIngrese el nombre: ");
                fflush(stdin);
                gets(nuevaPersona.name);
                flag = validarCadena(nuevaPersona.name);
            }

            printf("Ingrese Apellido: ");
            fflush(stdin);
            gets(nuevaPersona.lastName);
            flag = validarCadena(nuevaPersona.lastName);

            while(strlen(nuevaPersona.lastName) == 0 || strlen(nuevaPersona.lastName)> 20 || flag != 0 )
            {
                printf("\nDato invalido. ReIngrese el Apellido: ");
                fflush(stdin);
                gets(nuevaPersona.lastName);
                flag = validarCadena(nuevaPersona.lastName);
            }

            printf("Ingrese salario: ");
            scanf("%f", &nuevaPersona.salary);

            printf("Ingrese sectore: ");
            scanf("%d", &nuevaPersona.sector);

            list[indice] = nuevaPersona;
            error = 0;
        }

    }

    return error;
}

/** \brief Remove a Employee by Id (put isEmpty Flag in 1)
 *
 * \param list Employee*
 * \param len int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a employee] - (0) if Ok
 *
 */

int removeEmployee(eEmployee list[], int len)
{
    int error = -1;
    int id;
    int indice ;
    char confirma;

    if(list!=NULL && len>0 && len <=1000)
    {
        system("cls");
        printf("   *** Baja de Personas ****\n\n");

        printEmployees(list,len);

        printf("Ingrese el ID: ");
        scanf("%d",&id);
        indice = findEmployeeById(list, len, id);
        if(indice == -1)
        {

            printf("No existe una persona con ese ID.\n\n");
        }
        else
        {
            printEmployee(list[indice]);
            printf("Para confirmar S para Cancelas N: ");
            fflush(stdin);
            scanf("%c", &confirma);
            confirma = tolower(confirma);
            if( confirma == 's')
            {
                list[indice].isEmpty=1;
                error= 0;
            }
            else if( confirma == 'n' )
            {
                printf("La baja se ha cancelado por el usuario...\n\n");
                error= 0;
            }
        }
    }
    return error;
}

/** \brief print the content of employees array
 *
 * \param list Employee*
 * \param length int
 * \return int
 *
 */
int printEmployees(eEmployee list[], int length)
{
    int flag = 0;
    int error = 1;

    if(list!=NULL && length> 0 && length <=1000)
    {
        system("cls");
        printf("     ID       Nombre      Apellido     Salario    Sector \n");
        printf("---------------------------------------------------------\n");
        for(int i=0; i <length; i ++)
        {
            if(list[i].isEmpty==0)
            {
                printEmployee(list[i]);
                flag = 1;
            }
        }
        if(flag == 0)
        {
            printf("No hay empleados en la lista\n");
        }
        printf("\n\n");
        error = 0;
    }
    return error;
}

/** \brief print the content of employee array
 *
 * \param list Employee []
 *   takes the user's data and displays it on the screen
 */
void printEmployee(eEmployee Emplo)
{
    orderName(Emplo.name);
    orderName(Emplo.lastName);

    printf("%5d     %10s     %10s     %7.2f      %4d\n",Emplo.id, Emplo.name, Emplo.lastName, Emplo.salary, Emplo.sector);
}

/** \brief find an Employee by Id en returns the index position in array.
 *
 * \param list Employee*
 * \param len int
 * \param id int
 * \return Return employee index position or (-1) if [Invalid length or NULL
pointer received or employee not found]
 *
 */

int findEmployeeById(eEmployee list[], int len, int id)
{
    int indice = -1;
    if(list!= NULL && len > 0 && len <=1000)
    {
        for(int i=0; i<len; i++)
        {
            if(list[i].id == id && list[i].isEmpty == 0)
            {
                indice = i;
                break;
            }
        }
    }
    return indice;
}
/** \brief Search the array if there are places available to enter data
 *
 * \param list Employee []
 * \param len int
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */

int findFree(eEmployee list[], int len)
{
    int indice = -1;

    for(int i=0; i<len; i++)
    {
        if(list[i].isEmpty==1)
        {
            indice = i;
            break;
        }
    }
    return indice;
}

/** \brief Sort the elements in the array of employees, the argument order
indicate UP or DOWN order
 *
 * \param list Employee*
 * \param len int
 * \param order int [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */

int sortEmployees(eEmployee list[], int len, int criterioS, int criterioA) // 1 para ascendiente y 0 para decendiente
{
    eEmployee auxEmployee;
    int error = -1;


    if(list!= NULL && len > 0 && len <=1000 && criterioS >= 0 && criterioS <= 1 && criterioA >= 0  && criterioA <=1)
    {
        for(int i = 0; i<len -1 ; i++)
        {
            for (int j = i+1; j<len; j++ )
            {
                //a- comparando personas del mismo Apellido desempata el Sector
                //b- comprando personas de distinto sexo
                if(list[i].lastName> list[j].lastName && criterioS == 1 )
                {
                    auxEmployee = list[i];
                    list[i] = list[j];
                    list[j] = auxEmployee;
                }
                else if(list[i].lastName < list[j].lastName && criterioS == 0 )
                {
                    auxEmployee = list[i];
                    list[i] = list[j];
                    list[j] = auxEmployee;
                }
                else if (list[i].lastName == list[j].lastName && list[i].sector > list[j].sector && criterioA == 1 )
                {
                    auxEmployee = list[i];
                    list[i] = list[j];
                    list[j] = auxEmployee;
                }
                else if (list[i].lastName == list[j].lastName && list[i].sector > list[j].sector && criterioA == 0 )
                {
                    auxEmployee = list[i];
                    list[i] = list[j];
                    list[j] = auxEmployee;
                }
            }
        }
        error = 0;
    }
    return error;
}
/** \brief Option menu
 *
 * \return int Return the value entered by the user
 *
 */

int menuEmployee()
{

    int opcion = 0;

    system("cls");
    printf("1- Altas.\n");
    printf("2- Modificar.\n");
    printf("3- Baja.\n");
    printf("4- Informar.\n");
    printf("5- Salir");

    printf("\n Eliga una de las Opciones: ");
    fflush(stdin);
    scanf("%d",&opcion);
    system("cls");

    if( opcion < 1 || opcion > 5)
    {
        printf("\n La opcion ingresada es incorrecta.\n");
        system("pause");
    }

    return opcion;
}

int validarNumero(char num[])
{

    int i = 0;
    int sw = 0;
    int j;
    j=strlen(num);

    while(i<j && sw == 0)
    {
        if(isdigit(num[i])!=0)
        {
            i++;
        }
        else
        {
            sw = 1;
        }
    }
    return sw;
}

/** \brief Validate that if what is entered is an array of characters
 *
* \return int Return (-1) if Error [Invalid length] - (0) if Ok
 *
 */

int validarCadena(char cadena[])
{

    int i = 0;
    int sw = 0;
    int j;
    j=strlen(cadena);

    while(i<j && sw == 0)
    {
        if(isalpha(cadena[i])!=0)
        {
            i++;
        }
        else
        {
            sw = 1;
        }
    }
    return sw;
}

/** \brief Take the character array and put the first character in uppercase
 */
void orderName(char name[])
{

    int len;
    strlwr(name);
    name[0] = toupper(name[0]);
    len = strlen(name);
    for(int i = 0; i < len; i++)
    {
        if(name[i] == ' ')
        {
            i++;
            if(name[i] >= 'a' && name[i] <= 'z')
            {
                name[i] = toupper(name[i]);
            }
        }
    }
}

/** \brief Opens a menu to make any modification, takes the data from the one selected by the user and modifies it
 *
 * \param list Employee []
 * \param len int
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */
int modificarEmplyee(eEmployee list[], int len)
{

    eEmployee nuevoEmpleado;

    int flag;
    int error = -1;
    int id;
    int indice;
    int opcion = 0;

    if(list !=NULL && len > 0 && len <= 1000)
    {

        printEmployees(list,len);
        printf("Ingrese el ID del Empleado que quiere modificar: ");
        scanf("%d",&id);
        indice = findEmployeeById(list,len,id);
        system ("cls");
        if(indice == -1)
        {

            printf("\nNo hay personas con ese ID.\n");
        }
        else
        {
            printf("     ID       Nombre       Apellido      Salario    Sector \n");
            printf("---------------------------------------------------------\n");
            printEmployee(list[indice]);
            printf(" -- Modificar --\n");
            printf("1- Nombre\n");
            printf("2- Apellido\n");
            printf("3- Salario\n");
            printf("4- Sector\n");
            printf("Ingrese el numero de lo que quiere modificar: ");
            scanf("%d",&opcion);

            switch(opcion)
            {
            case 1:
                printf("Ingrese nombre: ");
                fflush(stdin);
                gets(nuevoEmpleado.name);
                flag = validarCadena(nuevoEmpleado.name);

                while(strlen(nuevoEmpleado.name) > 20 || flag != 0 )
                {
                    printf("Dato invalido. ReIngrese el nombre: ");
                    fflush(stdin);
                    gets(nuevoEmpleado.name);
                    flag = validarCadena(nuevoEmpleado.name);
                }
                strcpy(list[indice].name,nuevoEmpleado.name);
                break;
            case 2:
                printf("Ingrese el Apellido: ");
                fflush(stdin);
                gets(nuevoEmpleado.lastName);
                flag = validarCadena(nuevoEmpleado.lastName);
                while(strlen(nuevoEmpleado.lastName) > 20 || flag != 0)
                {
                    printf("ReIngrese el Apellido: ");
                    fflush(stdin);
                    gets(nuevoEmpleado.lastName);
                    flag = validarCadena(nuevoEmpleado.lastName);
                }
                strcpy(list[indice].lastName,nuevoEmpleado.lastName);
                break;
            case 3:
                printf("Ingrese nuevo Salario: ");
                scanf("%f",&list[indice].salary);
                break;
            case 4:
                printf("Ingrese el nuevo del nuevo sector: ");
                scanf("%d",&list[indice].sector);
                break;
            default:
                printf("Dato invalido.\n");
                break;
            }
            error = 0;
        }
    }
    return error;
}

/** \brief Total and average salaries, and how many employees are above the average salary
 *
 * \param list Employee []
 * \param len int
 *
 */
void totalPromedioSuperan(eEmployee list[], int len)
{
    int contador = 0;
    float totalPromedio = 0;
    float acumulador = 0;
    int contador2 = 0;

    if(list != NULL && len > 0 && len <= 1000)
    {
        for(int i = 0; i < len; i++)
        {
            if(list[i].isEmpty == 0)
            {
                contador++;
                acumulador = list[i].salary + acumulador;
            }
        }

        totalPromedio = acumulador/ contador;
    }
    if(list != NULL && len > 0 && len <= 1000)
    {
        for(int i = 0; i < len; i++)
        {
            if(list[i].isEmpty == 0 && list[i].salary >= totalPromedio)
            {
                contador2++;
            }
        }
        totalPromedio = acumulador/ contador;
    }

    printf("Total de salario de los empleados:  %.2f\n",acumulador);
    printf("Promedio de los salario de los empleados: %.2f\n",totalPromedio);
    printf("El total de empleados que superan el promedio son: %d\n",contador2);

}

#endif // ARRAYEMPLOYEES_C_INCLUDED
