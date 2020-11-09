#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile, LinkedList* pArrayListEmployee)
{
    int cantidadDatosLeidos;
    char id[50];
    char nombre[50];
    char horasTrabajadas[50];
    char sueldo[50];

    if (pFile == NULL || pArrayListEmployee == NULL)
    {
        return -1;
    }

    // Forzamos lectura de la primer linea del archivo ya que esta contiene los encabezados
    fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",id,nombre,horasTrabajadas,sueldo);

    do
    {
        cantidadDatosLeidos = fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", id, nombre, horasTrabajadas, sueldo);

        if (cantidadDatosLeidos == 4)
        {
            Employee* newEmployee = employee_newParametros(id,nombre,horasTrabajadas,sueldo);

            if (newEmployee != NULL)
            {
                // no me toma los linkedlist.a
                ll_add(pArrayListEmployee, newEmployee);
            }
        }
        else
        {
            printf("\nHubo un problema al leer los datos de una linea del archivo. La misma sera ignorada\n");
        }

    }
    while (!feof(pFile));

    return 0;
}


/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
    if (pFile == NULL || pArrayListEmployee == NULL)
    {
        return -1;
    }

    Employee* empleadoTemporal;

    while (!feof(pFile))
    {
        empleadoTemporal = (Employee*)malloc(sizeof(Employee));

        if (fread(empleadoTemporal, sizeof(Employee), 1, pFile) == 1)
        {
            ll_add(pArrayListEmployee, empleadoTemporal);
        }
    }

    return 0;
}
