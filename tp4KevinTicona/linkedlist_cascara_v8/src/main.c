/*
    utest example : Unit test examples.
    Copyright (C) <2018>  <Mauricio Davila>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../inc/controller.h"
#include "../inc/LinkedList.h"
#include "../inc/parser.h"
#include "../inc/notebooks.h"
#include "../inc/clientes.h"
#include "../inc/validaciones.h"

#define PATH_NOTEBOOKS_TXT "notebooks.csv"
#define PATH_CLIENTES_TXT "clientes.csv"

#define PATH_NOTEBOOKS_BIN "notebooks.bin"
#define PATH_CLIENTES_BIN "clientes.bin"
/*typedef struct{
    int id;
    char nombre[20];
    char sexo;
    float sueldo;
}eEmpleado;
*/
/*void mostrarEmpleados(LinkedList* lista){
    int tam = ll_len(lista);
    eEmpleado* emp;
    for(int i =0; i < tam; i++){
        emp= (eEmpleado*) ll_get(lista, i);
        printf("%d %s %c %.2f\n", emp->id, emp->nombre, emp->sexo, emp->sueldo);
    }
    printf("\n\n");
}*/

/*int filtrarVarones(void* elemento){
    int rta = 0;
    eEmpleado* e =(eEmpleado*) elemento;
    if(e->sexo == 'm'){
        rta  = 1;
    }
    return rta;
}*/



int main(void)
{

    /*startTesting(1);  // ll_newLinkedList
    startTesting(2);  // ll_len
    startTesting(3);  // getNode - test_getNode
    startTesting(4);  // addNode - test_addNode
    startTesting(5);  // ll_add
    startTesting(6);  // ll_get
    startTesting(7);  // ll_set
    startTesting(8);  // ll_remove
    startTesting(9);  // ll_clear
    startTesting(10); // ll_deleteLinkedList
    startTesting(11); // ll_indexOf
    startTesting(12); // ll_isEmpty
    startTesting(13); // ll_push
    startTesting(14); // ll_pop
    startTesting(15); // ll_contains
    startTesting(16); // ll_containsAll
    startTesting(17); // ll_subList
    startTesting(18); // ll_clone
    startTesting(19); // ll_sort
    */

    int option;
    int selection;

    LinkedList* listNotebook = ll_newLinkedList();
    LinkedList* listCliente = ll_newLinkedList();

    if(listNotebook == NULL || listCliente == NULL)
    {
        return -1;
        printf("\nNo se ha conseguido espacio en memoria para poder agregar listas.\n");
    }

    do
    {
        menu_main();
        selection = validations_getOption(
                        &option,
                        "\nOpcion invalida, vuelva a intentar.\n",
                        1,
                        18
                    );
        if(!selection)
        {
            switch(option)
            {
            case 1:
                if(!controller_loadNotebooksFromBinary(PATH_NOTEBOOKS_TXT,listNotebook) && !controller_loadClientesFromBinary(PATH_CLIENTES_TXT,listCliente))
                {
                    printf("\nSe han cargado %d Notebooks desde el archivo %s\n", ll_len(listNotebook), PATH_NOTEBOOKS_TXT);
                    printf("\nSe han cargado %d Clientes desde el archivo %s\n", ll_len(listCliente), PATH_CLIENTES_TXT);
                }
                break;
            case 2:
                if(!controller_loadNotebooksFromBinary(PATH_NOTEBOOKS_BIN,listNotebook) && !controller_loadClientesFromBinary(PATH_CLIENTES_BIN,listCliente))
                {
                    printf("\nSe han cargado %d Notebooks desde el archivo %s\n", ll_len(listNotebook), PATH_NOTEBOOKS_BIN);
                    printf("\nSe han cargado %d Clientes desde el archivo %s\n", ll_len(listCliente), PATH_CLIENTES_BIN);
                }
                break;
            case 3:
                if(!controller_addNotebook(listNotebook, listCliente))
                {
                    printf("\nNotebook agregada con exito, total de Notebooks: %d\n", ll_len(listNotebook));
                }
                else
                {
                    printf("\nOcurrio un problema al intentar agregar la mascota, vuelva a intentarlo mas tarde.\n");
                }
                break;
            case 4:
                if(!controller_editeNotebook(listNotebook,listCliente))
                {
                    printf("\nOperacion realizada con exito.\n");
                }
                else
                {
                    printf("\nOcurrio un problema al intentar modificar la mascota, vuelva a intentarlo mas tarde.\n");
                }
                break;
            case 5:
                if(!controller_removeNotebook(listNotebook,listCliente))
                {
                    printf("\nOperacion realizada con exito.\n");
                }
                else
                {
                    printf("\nOcurrio un problema al intentar eliminar la mascota, vuelva a intentarlo mas tarde.\n");
                }
                break;
            case 6:
                if(!controller_removeNotebookPop(listNotebook,listCliente))
                {
                    printf("\nOperacion realizada con exito.\n");
                }
                else
                {
                    printf("\nOcurrio un problema al intentar eliminar la mascota, vuelva a intentarlo mas tarde.\n");
                }
                break;
            case 7:
                controller_ListNotebooks(listNotebook,listCliente);
                break;
            case 8:
                controller_ListClientes(listCliente);
                break;
            case 9:
                if(!controller_sortNotebooks(listNotebook,listCliente))
                {
                    printf("\nOperacion realizada con exito.\n");
                }
                else
                {
                    printf("\nOcurrio un problema al realizar el ordenamiento, vuelva a intentar.\n");
                }
                break;
            case 10:
                if(!controller_filterNotebooks(listNotebook,listCliente))
                {
                    printf("\nOperacion realizada con exito.\n");
                }
                else
                {
                    printf("\nOcurrio un problema al realizar el filtrado, vuelva a intentar.\n");
                }
                break;
            case 11:
                if(!controller_cloneList(listNotebook,listCliente))
                {
                    printf("\nLista clonada exitosamente\n");
                }
                else
                {
                    printf("\nOcurrio un problema al clonar la lista, vuelva a intentar.\n");
                }
                break;
            case 12:
                if(!controller_containsList(listNotebook,listCliente))
                {
                    printf("\nEvaluacion realizada exitosamente\n");
                }
                else
                {
                    printf("\nOcurrio un problema al realizar la evaluacion, vuelva a intentar.\n");
                }
                break;
            case 13:
                if(!controller_makeSubList(listNotebook,listCliente))
                {
                    printf("\nSub-lista creada exitosamente\n");
                }
                else
                {
                    printf("\nOcurrio un problema al crear la sub-lista, vuelva a intentar.\n");
                }
                break;
            case 14:
                if(!controller_settingNotebook(listNotebook,listCliente))
                {
                    printf("\nSe ha colocado la notebook en el indice indicado con exito.\n");
                }
                else
                {
                    printf("\nOcurrio un problema, vuelva a intentar.\n");
                }
                break;
            case 15:
                if(!controller_pushNotebook(listNotebook,listCliente))
                {
                    printf("\nSe ha colocado la notebook en el indice indicado con exito.\n");
                }
                else
                {
                    printf("\nOcurrio un problema, vuelva a intentar.\n");
                }
                break;
            case 16:
                if(!controller_saveNotebooksAsText(PATH_NOTEBOOKS_TXT,listNotebook) && !controller_saveClientesAsText(PATH_CLIENTES_TXT,listCliente))
                {
                    printf("\nSe han guardado %d Notebooks en el archivo %s.\n", listNotebook->size, PATH_NOTEBOOKS_TXT);
                    printf("\nSe han guardado %d Clientes en el archivo %s.\n", listCliente->size, PATH_CLIENTES_TXT);
                }
                break;
            case 17:
                if(!controller_saveNotebooksAsBinary(PATH_NOTEBOOKS_BIN,listNotebook) && !controller_saveClientesAsBinary(PATH_CLIENTES_BIN,listCliente))
                {
                    printf("\nSe han guardado %d Notebooks en el archivo %s.\n", listNotebook->size, PATH_NOTEBOOKS_BIN);
                    printf("\nSe han guardado %d Clientes en el archivo %s.\n", listCliente->size, PATH_CLIENTES_BIN);
                }
                break;
            case 18:
                controller_freeResources(listNotebook);
                controller_freeResources(listCliente);
                printf("\nSaliendo...\n");
                break;
            }
            system("pause");
        }
    }
    while(option != 18);

    return 0;
}

































