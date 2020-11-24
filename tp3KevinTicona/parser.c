#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile, LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    Employee* this;
    char id[50];
    char nombre[50];
    char horasTrabajadas[50];
    char sueldo[50];

	if(pFile != NULL && pArrayListEmployee)
	{
		retorno = 0;
		fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",id,nombre,horasTrabajadas,sueldo);
		do
		{
			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",id,nombre,horasTrabajadas,sueldo) == 4)
			{
				this = employee_new();

				if(this != NULL &&
				   !employee_setIdStr(this,id) &&
				   !employee_setNombre(this,nombre) &&
				   !employee_setHorasTrabajadasStr(this,horasTrabajadas) &&
				   !employee_setSueldoStr(this,sueldo))
				{

					ll_add(pArrayListEmployee,this);
				}
			}

		}while(!feof(pFile));
	}

    return retorno;
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
	int retorno = -1;

	Employee* this;

	if(pFile != NULL && pArrayListEmployee != NULL)
	{
		do
		{
			this = employee_new();
			if(this != NULL)
			{
				if(fread(this,sizeof(Employee),1,pFile))
				{
					ll_add(pArrayListEmployee,this);
				}else
				{
					employee_delete(this);
				}
			}
		}while(!feof(pFile));

		retorno = 0;
	}

    return retorno;
}
