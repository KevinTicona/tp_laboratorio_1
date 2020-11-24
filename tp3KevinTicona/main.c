#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"

#define PATH_TXT "data.csv"
#define PATH_BIN "data.bin"

/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/


int main()
{
    int option = 0;
    int opcionValid = 0;

    LinkedList* listaEmpleados = ll_newLinkedList();
    do
    {
        imprimir_Menu();
        opcionValid = getopcion(&option,"\nOpcion invalida\n", 1, 10);

        if(!opcionValid)
        {
            switch(option)
            {
            case 1:
                if(controller_loadFromText(PATH_TXT,listaEmpleados) == 0)
                {
                    printf("\nSe cargaron %d empleados desde el archivo %s\n", listaEmpleados->size, PATH_TXT);
                }
                else
                {
                    printf("\nOcurrio un problema en la carga de empleados desde el archivo %s\n", PATH_TXT);
                }
                break;
            case 2:
                if(controller_loadFromBinary(PATH_BIN, listaEmpleados) == 0)
                {
                    printf("\nSe cargaron %d empleados desde el archivo %s\n", listaEmpleados->size, PATH_BIN);
                }
                else
                {
                    printf("\nOcurrio un problema en la carga de empleados desde el archivo %s\n", PATH_BIN);
                }
                break;
            case 3:
                if(controller_addEmployee(listaEmpleados) != 0)
                {
                    printf("\nOcurrio un problema intente crear un empleado.\n");
                }
                break;
            case 4:
                controller_ListEmployee(listaEmpleados);
                if(controller_editEmployee(listaEmpleados) != 0)
                {
                    printf("\nOcurrio un problema al intentar modificar un empleado\n");
                }
                break;
            case 5:
                controller_ListEmployee(listaEmpleados);
                if(controller_removeEmployee(listaEmpleados)!=0)
                {
                    printf("\nOcurrio un problema al intentar eliminar un empleado.\n");
                }
                break;
            case 6:
                controller_ListEmployee(listaEmpleados);
                break;
            case 7:
                controller_sortEmployee(listaEmpleados);
                break;
            case 8:
                if(controller_saveAsText(PATH_TXT, listaEmpleados) == 0)
                {
                    printf("\nSe guardo %d empleados en el archivo %s.\n", listaEmpleados->size, PATH_TXT);
                }
                else
                {
                    printf("\nOcurrio un problema al guardar los empleados en el archivo %s.\n", PATH_TXT);
                }
                break;
            case 9:
                if(controller_saveAsBinary(PATH_BIN, listaEmpleados) == 0)
                {
                    printf("\nSe guardo %d empleados en el archivo %s.\n", listaEmpleados->size, PATH_BIN);
                }
                else
                {
                    printf("\nOcurrio un problema al guardar los empleados en el archivo %s.\n", PATH_BIN);
                }
                break;
            case 10:
                controller_freeResources(listaEmpleados);
                printf("\nSaliendo.\n");
                break;
            }
            system("pause");
        }
    }
    while(option != 10);

    return 0;
}
