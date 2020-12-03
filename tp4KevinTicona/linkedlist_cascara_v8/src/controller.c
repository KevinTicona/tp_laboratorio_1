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

int controller_loadNotebooksFromText(char* path, LinkedList* pLinkedListNotebooks)
{
    int retorno = -1;
    FILE *pFile = fopen(path, "r");

    if (pFile == NULL)
    {
        printf("\nEl archivo en la ruta %s no existe.\n", path);
        return retorno;
    }

    ll_clear(pLinkedListNotebooks);

    retorno = parser_notebooksFromText(pFile, pLinkedListNotebooks);

    fclose(pFile);

    return retorno;
}

int controller_loadClientesFromText(char* path, LinkedList* pLinkedListClientes)
{
    int retorno = -1;
    FILE *pFile = fopen(path, "r");

    if (pFile == NULL)
    {
        printf("\nEl archivo en la ruta %s no existe.\n", path);
        return retorno;
    }

    ll_clear(pLinkedListClientes);

    retorno = parser_clientesFromText(pFile, pLinkedListClientes);

    fclose(pFile);

    return retorno;
}

int controller_loadNotebooksFromBinary(char* path, LinkedList* pLinkedListNotebooks)
{
    int retorno = -1;
    FILE *pFile = fopen(path, "rb");

    if (pFile == NULL)
    {
        printf("\nEl archivo en la ruta %s no existe.\n", path);
        return retorno;
    }

    ll_clear(pLinkedListNotebooks);

    retorno = parser_notebooksFromBinary(pFile,pLinkedListNotebooks);

    fclose(pFile);

    return retorno;
}

int controller_loadClientesFromBinary(char* path, LinkedList* pLinkedListClientes)
{
    int retorno = -1;
    FILE *pFile = fopen(path, "rb");

    if (pFile == NULL)
    {
        printf("\nEl archivo en la ruta %s no existe.\n", path);
        return retorno;
    }

    ll_clear(pLinkedListClientes);

    retorno = parser_clientesFromBinary(pFile, pLinkedListClientes);

    fclose(pFile);

    return retorno;
}


int controller_addNotebook(LinkedList* pLinkedListNotebooks, LinkedList* pLinkedListClientes)
{
    if(ll_isEmpty(pLinkedListNotebooks) != 0)
    {
        printf("\nSe deben cargar los datos antes de agregar una Notebook en la lista.\n");
        return -1;
    }

    eNotebook* newNotebook = NULL;
    int id;
    char idChar[50];
    char marca[100];
    char tipo[50];
    char precio[50];
    char idCliente[50];

    // Ingresar y validar datos
    notebooks_ValidMarca(marca);
    notebooks_ValidTipo(tipo);
    notebooks_ValidPrecio(precio);
    //imprimir dueños
    system("cls");
    menu_printClientes(pLinkedListClientes);
    notebooks_ValidIdCliente(idCliente);

    // Id autoincremental
    Node* currentNode = pLinkedListNotebooks->pFirstNode;

    while (currentNode->pNextNode != NULL)
    {
        currentNode = currentNode->pNextNode;
    }

    // Al terminar el while, currentNode será el último Nodo en nuestra Linked List
    // Luego de encontrar la ultima mascota en la Linked List, utilizamos su Id y le agregamos 1.
    eNotebook* ultimaNote = (eNotebook*)currentNode->pElement;
    notebooks_getId(ultimaNote,&id);
    id += 1;
    itoa(id, idChar, 10);

    //Creamos la mascota con los datos recibidos
    newNotebook = note_newParams(idChar,marca,tipo,precio,idCliente);

    if(newNotebook != NULL)
    {
        ll_add(pLinkedListNotebooks,newNotebook);
    }

    return 0;
}

int controller_editeNotebook(LinkedList* pLinkedListNotebooks, LinkedList* pLinkedListClientes)
{
    if(ll_isEmpty(pLinkedListNotebooks) != 0)
    {
        printf("\nSe deben cargar los datos antes de editar una Notebook en la lista.\n");
        return -1;
    }

    eNotebook* auxNotebook = NULL;

    int validarEntero;
    int id;
    int selection;
    int option;
    int auxPrecio;
    char idStr[50];
    char marcaStr[100];
    char tipoStr[30];
    char precioStr[30];
    char confirmation;

    //Validar ingreso de datos
    system("cls");
    menu_printNotebooks(pLinkedListNotebooks,pLinkedListClientes);
    printf("\nIngrese el ID de la Notebook que desea modificar: ");
    fflush(stdin);
    gets(idStr);
    validarEntero = validations_isValidID(idStr);
    while(validarEntero != 1)
    {
        printf("\nId invalido. Ingrese el ID de la Notebook que desea modificar: ");
        fflush(stdin);
        gets(idStr);
        validarEntero = validations_isValidID(idStr);
    }

    //Buscamos por ID verificando que exista esa mascota
    id = atoi(idStr);
    if(id > 0 && id <= ll_len(pLinkedListNotebooks))
    {
        auxNotebook = notebooks_searchByID(pLinkedListNotebooks, id);
        do
        {
            system("cls");
            menu_encabezadoNotebook();
            menu_printNotebook(pLinkedListClientes,auxNotebook);
            menu_modificaciones();
            selection = validations_getOption(
                            &option,
                            "\nOpcion invalida. Vuelva a intentarlo.\n",
                            1,
                            4);
            if(!selection)
            {
                switch(option)
                {
                case 1:
                {
                    //Pedir dato
                    notebooks_ValidMarca(marcaStr);
                    char nombreAnterior[100];
                    notebooks_setModelo(auxNotebook,nombreAnterior);
                    //mostrar dato
                    printf("\nMarca ingresado: %s\nMarca anterior: %s\n",marcaStr,nombreAnterior);
                    //Confirmar modificacion
                    menu_confirmacion(&confirmation);

                    if(confirmation == 's')
                    {
                        notebooks_setModelo(auxNotebook,marcaStr);
                        printf("\nSe ha modificado la Marca.\n");
                        break;
                    }
                    else if(confirmation == 'n')
                    {
                        printf("\nModificacion cancelada por usuario.\n");
                        break;
                    }
                }
                break;
                case 2:
                {
                    notebooks_ValidTipo(tipoStr);
                    char tipoAnterior[100];
                    notebooks_getTipo(auxNotebook,tipoAnterior);
                    printf("\nTipo ingresado: %s\nTipo anterior: %s\n",tipoStr,tipoAnterior);

                    menu_confirmacion(&confirmation);

                    if(confirmation == 's')
                    {
                        notebooks_setTipo(auxNotebook,tipoStr);
                        printf("\nSe ha modificado el Tipo.\n");
                        break;
                    }
                    else if(confirmation == 'n')
                    {
                        printf("\nModificacion cancelada por usuario.\n");
                        break;
                    }
                }
                break;
                case 3:
                {
                    notebooks_ValidPrecio(precioStr);
                    auxPrecio = atoi(precioStr);
                    int precioAnterior;
                    notebooks_getPrecio(auxNotebook,&precioAnterior);
                    printf("\nPrecio ingresada: %d\nPrecio anterior: %d\n",auxPrecio,precioAnterior);

                    menu_confirmacion(&confirmation);

                    if(confirmation == 's')
                    {
                        notebooks_setPrecio(auxNotebook,auxPrecio);
                        printf("\nSe ha modificado la Precio.\n");
                        break;
                    }
                    else if(confirmation == 'n')
                    {
                        printf("\nModificacion cancelada por usuario.\n");
                        break;
                    }
                }
                break;
                case 4:
                    printf("\nVolviendo al menu principal...\n");
                    break;
                }
                system("pause");
            }
        }
        while(option != 4);
    }
    else
    {
        printf("\nNo existe una Notebook con ese ID\n");
        return -1;
    }

    return 0;
}

int controller_removeNotebook(LinkedList* pLinkedListNotebooks,LinkedList* pLinkedListClientes)
{
    if(ll_isEmpty(pLinkedListNotebooks) != 0)
    {
        printf("\nSe deben cargar los datos antes de eliminar una Notebook en la lista.\n");
        return -1;
    }

    int validarEntero;
    int id;
    char confirmacion;
    char idChar[50];

    //Validar ingreso de datos
    system("cls");
    menu_printNotebooks(pLinkedListNotebooks,pLinkedListClientes);
    printf("\nIngrese el ID de la Notebook que desea eliminar: ");
    fflush(stdin);
    gets(idChar);
    validarEntero = validations_isValidID(idChar);

    while(validarEntero != 1)
    {
        printf("\nDato invalida. Ingrese el ID de la Notebook que desea eliminar: ");
        fflush(stdin);
        gets(idChar);
        validarEntero = validations_isValidID(idChar);
    }
    id = atoi(idChar);

    //Recorrer la lista, si existe la Notebook, la muestro y la borro
    int currentNodeIndex = 0;
    int linkedListSize = ll_len(pLinkedListNotebooks);
    Node* currentNode = pLinkedListNotebooks->pFirstNode;
    eNotebook* actualNote = NULL;
    int idActual;

    while (currentNodeIndex < linkedListSize)
    {
        actualNote = (eNotebook*)ll_get(pLinkedListNotebooks, currentNodeIndex);
        notebooks_getId(actualNote,&idActual);

        if (idActual == id)
        {
            menu_encabezadoNotebook();
            menu_printNotebook(pLinkedListClientes,actualNote);
            menu_confirmacion(&confirmacion);
            if(confirmacion == 's')
            {
                ll_remove(pLinkedListNotebooks,currentNodeIndex);
                printf("\nSe ha eliminado esta Notebook.\n");
                return 0;
            }
            else if (confirmacion == 'n')
            {
                printf("\nBaja cancelada por usuario.\n");
                return 0;
            }
        }

        currentNode = currentNode->pNextNode;
        currentNodeIndex++;
    }

    printf("\nNo se encontro una Notebook con ese ID.\n");
    return -1;
}

int controller_removeNotebookPop(LinkedList* pLinkedListNotebooks,LinkedList* pLinkedListClientes)
{

    if(ll_isEmpty(pLinkedListNotebooks) != 0)
    {
        printf("\nSe deben cargar los datos antes de eliminar una mascota a la lista.\n");
        return -1;
    }

    int validarEntero, id;
    char idChar[50];

    //Validar ingreso de datos
    system("cls");
    menu_printNotebooks(pLinkedListNotebooks,pLinkedListClientes);
    printf("\nIngrese el ID de la Notebook que desea eliminar\n");
    fflush(stdin);
    gets(idChar);
    validarEntero = validations_isValidID(idChar);
    while(validarEntero != 1)
    {
        printf("\nDato invalida. Ingrese el ID de la Notebook que desea eliminar\n");
        fflush(stdin);
        gets(idChar);
        validarEntero = validations_isValidID(idChar);
    }
    id = atoi(idChar);

    //Recorrer la lista, si existe la Notebook, la muestro y la borro
    int currentNodeIndex = 0;
    int linkedListSize = ll_len(pLinkedListNotebooks);
    Node* currentNode = pLinkedListNotebooks->pFirstNode;
    eNotebook* actualNotebook = NULL;
    int idActual;

    while (currentNodeIndex < linkedListSize)
    {
        actualNotebook = (eNotebook*)ll_get(pLinkedListNotebooks, currentNodeIndex);
        notebooks_getId(actualNotebook, &idActual);

        if (idActual == id)
        {
            actualNotebook = ll_pop(pLinkedListNotebooks,currentNodeIndex);
            menu_encabezadoNotebook();
            menu_printNotebook(pLinkedListClientes,actualNotebook);
            printf("\nSe ha eliminado esta Notebook.\n");
            return 0;
        }

        currentNode = currentNode->pNextNode;
        currentNodeIndex++;
    }

    printf("\nNo se encontro una Notebook con ese ID.\n");
    return -1;

}

int controller_ListNotebooks(LinkedList* pLinkedListNotebooks, LinkedList* pLinkedListClientes)
{
    if (ll_isEmpty(pLinkedListNotebooks) == 1)
    {
        printf("\nNo existen ninguna Notebook en el sistema.\n");
        return 0;
    }

    system("cls");
    menu_printNotebooks(pLinkedListNotebooks,pLinkedListClientes);

    return 1;
}

int controller_ListClientes(LinkedList* pLinkedListClientes)
{
    if (ll_isEmpty(pLinkedListClientes) == 1)
    {
        printf("\nNo existen ningun Cliente en el sistema.\n");
        return 0;
    }

    system("cls");
    menu_printClientes(pLinkedListClientes);

    return 1;
}

int controller_cloneList(LinkedList* pLinkedListNotebooks, LinkedList* pLinkedListClientes)
{
    if (ll_isEmpty(pLinkedListNotebooks) == 1 && ll_isEmpty(pLinkedListClientes) == 1)
    {
        printf("\nNo existen ninguna Notebook en el sistema. Intente cargarlos desde el menu para poder clonarlas.\n");
        return -1;
    }

    int error = -1;

    LinkedList* cloneList = ll_clone(pLinkedListNotebooks);

    if(cloneList != NULL)
    {
        system("cls");
        printf("                                         Lista Clonada \n");
        printf("----------------------------------------------------------------------------------------------\n");
        menu_printNotebooks(cloneList,pLinkedListClientes);
        ll_deleteLinkedList(cloneList);
        error = 0;
    }

    return error;
}

int controller_makeSubList(LinkedList* pLinkedListNotebooks, LinkedList* pLinkedListClientes)
{
    if (ll_isEmpty(pLinkedListNotebooks) == 1 && ll_isEmpty(pLinkedListClientes) == 1)
    {
        printf("\nNo existen Notebook en el sistema. Intente cargarlos desde el menu para poder realizar una sublista.\n");
        return -1;
    }

    int error = -1;
    LinkedList* subList = NULL;
    char desdeStr[100];
    char hastaStr[100];
    int validDesde;
    int validHasta;
    int desde;
    int hasta;

    printf("\nIngrese un indice entero desde donde quiere comenzar a copiar\n");
    fflush(stdin);
    gets(desdeStr);
    validDesde = validations_isValidNumber(desdeStr);
    while(validDesde != 1)
    {
        printf("\nDato invalido. Ingrese un indice entero desde donde quiere comenzar a copiar\n");
        fflush(stdin);
        gets(desdeStr);
        validDesde = validations_isValidNumber(desdeStr);
    }

    printf("\nIngrese un indice entero desde donde quiere finalizar el copiado\n");
    fflush(stdin);
    gets(hastaStr);
    validHasta = validations_isValidNumber(hastaStr);
    while(validHasta != 1)
    {
        printf("\nDato invalido. Ingrese un indice entero desde donde quiere finalizar el copiado\n");
        fflush(stdin);
        gets(hastaStr);
        validHasta = validations_isValidNumber(hastaStr);
    }

    desde = atoi(desdeStr);
    hasta = atoi(hastaStr);

    subList = ll_subList(pLinkedListNotebooks,desde,hasta);

    if(subList != NULL)
    {
        system("cls");
        printf("                                           Sub Lista\n");
        printf("----------------------------------------------------------------------------------------------\n");
        menu_printNotebooks(subList,pLinkedListClientes);
        ll_deleteLinkedList(subList);
        error = 0;
    }

    return error;
}

int controller_saveNotebooksAsText(char* path, LinkedList* pLinkedListNotebooks)
{
    if (ll_isEmpty(pLinkedListNotebooks) == 1)
    {
        printf("\nPrimero deben haber Notebooks cargadas.\n");
        return -1;
    }

    FILE *pFile;

    pFile = fopen(path, "w");

    if (pFile == NULL || pLinkedListNotebooks == NULL)
    {
        return -1;
    }

    int currentNodeIndex = 0;
    int linkedListSize = ll_len(pLinkedListNotebooks);

    int idActual;
    int precioActual;
    int idClienteActual;

    char nombreActual[100];
    char tipoActual[100];

    eNotebook* actualNotebook;
    Node* currentNode = pLinkedListNotebooks->pFirstNode;

    // Escribimos los headers del CSV
    fprintf(pFile, "Id,Nombre,Tipo,Precio,IdCliente\n");

    // Recorremos la Linked List con un índice (un número)
    while (currentNodeIndex < linkedListSize)
    {
        actualNotebook = (eNotebook*)ll_get(pLinkedListNotebooks, currentNodeIndex);

        notebooks_getId(actualNotebook,&idActual);
        notebooks_getModelo(actualNotebook, nombreActual);
        notebooks_getTipo(actualNotebook,tipoActual);
        notebooks_getPrecio(actualNotebook,&precioActual);
        notebooks_getIdCliente(actualNotebook,&idClienteActual);

        fprintf(pFile, "%d,%s,%s,%d,%d\n",
                idActual,
                nombreActual,
                tipoActual,
                precioActual,
                idClienteActual);

        currentNode = currentNode->pNextNode;
        currentNodeIndex++;
    }

    fclose(pFile);

    printf("\nLos cambios para la lista de Notebooks, han sido guardados correctamente.\n");

    return 0;
}

int controller_saveClientesAsText(char* path, LinkedList* pLinkedListClientes)
{
    if (ll_isEmpty(pLinkedListClientes) == 1)
    {
        printf("\nPrimero deben haber Clientes cargados.\n");
        return -1;
    }

    FILE *pFile;

    pFile = fopen(path, "w");

    if (pFile == NULL || pLinkedListClientes == NULL)
    {
        return -1;
    }

    int currentNodeIndex = 0;
    int linkedListSize = ll_len(pLinkedListClientes);
    int idActual;
    char nombreActual[100];
    char sexoActual[100];

    eCliente* actualCliente;
    Node* currentNode = pLinkedListClientes->pFirstNode;

    // Escribimos los headers del CSV
    fprintf(pFile, "Id,Nombre,Sexo\n");

    // Recorremos la Linked List con un índice (un número)
    while (currentNodeIndex < linkedListSize)
    {
        actualCliente = (eCliente*)ll_get(pLinkedListClientes, currentNodeIndex);
        cliente_getId(actualCliente,&idActual);
        cliente_getNombre(actualCliente,nombreActual);
        cliente_getSexo(actualCliente,sexoActual);

        fprintf(pFile, "%d,%s,%s\n",
                idActual,
                nombreActual,
                sexoActual);

        currentNode = currentNode->pNextNode;
        currentNodeIndex++;
    }

    fclose(pFile);

    printf("\nLos cambios para la lista de Clientes, han sido guardados correctamente.\n");

    return 0;
}

int controller_saveNotebooksAsBinary(char* path, LinkedList* pLinkedListNotebooks)
{
    if (ll_isEmpty(pLinkedListNotebooks) == 1)
    {
        printf("\nPrimero deben haber Notebooks cargadas.\n");
        return -1;
    }

    FILE* pFile= fopen(path, "wb");

    if (pFile == NULL || pLinkedListNotebooks == NULL)
    {
        return -1;
    }

    int currentNodeIndex = 0;
    int linkedListSize = ll_len(pLinkedListNotebooks);

    eNotebook* actualNotebook;
    Node* currentNode = pLinkedListNotebooks->pFirstNode;

    while (currentNodeIndex < linkedListSize)
    {
        actualNotebook = (eNotebook*)ll_get(pLinkedListNotebooks, currentNodeIndex);

        fwrite(actualNotebook, sizeof(eNotebook), 1, pFile);

        currentNode = currentNode->pNextNode;
        currentNodeIndex++;
    }

    fclose(pFile);

    return 0;
}

int controller_saveClientesAsBinary(char* path, LinkedList* pLinkedListClientes)
{
    if (ll_isEmpty(pLinkedListClientes) == 1)
    {
        printf("\nPrimero deben haber Clientes cargados.\n");
        return -1;
    }

    FILE* pFile= fopen(path, "wb");

    if (pFile == NULL || pLinkedListClientes == NULL)
    {
        return -1;
    }

    int currentNodeIndex = 0;
    int linkedListSize = ll_len(pLinkedListClientes);

    eCliente* actualCliente;
    Node* currentNode = pLinkedListClientes->pFirstNode;

    while (currentNodeIndex < linkedListSize)
    {
        actualCliente = (eCliente*)ll_get(pLinkedListClientes, currentNodeIndex);

        fwrite(actualCliente, sizeof(eCliente), 1, pFile);

        currentNode = currentNode->pNextNode;
        currentNodeIndex++;
    }

    fclose(pFile);

    return 0;
}

int controller_freeResources(LinkedList* this)
{
    if(!ll_deleteLinkedList(this))
    {
        return 0;
    }

    return -1;
}

int controller_sortNotebooks(LinkedList* pLinkedListNotebooks, LinkedList* pLinkedListClientes)
{
    if (ll_isEmpty(pLinkedListNotebooks) == 1)
    {
        printf("\nNo existen Noteboooks en el sistema. Intente cargarlas para poder listarlas.\n");
        return -1;
    }

    int optionSort = 0;
    int selectSort = 0;

    do
    {
        menu_DeOrdenamiento();
        selectSort = validations_getOption(
                         &optionSort,
                         "\nOpcion invalida, vuelva a intentarlo.\n",
                         1,
                         4);
        if(!selectSort)
        {
            switch(optionSort)
            {
            case 1:
                printf("Aguarde, esto podria tardar un momento. Ordenando por nombre ...");
                ll_sort(pLinkedListNotebooks, notebook_SortByName, 1);
                printf("\nNotebooks ordenadas por nombre.\n");
                system("pause");
                controller_ListNotebooks(pLinkedListNotebooks, pLinkedListClientes);
                break;
            case 2:
                printf("Aguarde, esto podria tardar un momento. Ordenando por ID ...");
                ll_sort(pLinkedListNotebooks, notebook_SortById,1);
                printf("\nNotebooks ordenadas por Id.\n");
                system("pause");
                controller_ListNotebooks(pLinkedListNotebooks,pLinkedListClientes);
                break;
            case 3:
                printf("Aguarde, esto podria tardar un momento. Ordenando por tipo ...");
                ll_sort(pLinkedListNotebooks, notebook_SortByTipo, 1);
                printf("\nNotebooks ordenadas por tipo.\n");
                system("pause");
                controller_ListNotebooks(pLinkedListNotebooks,pLinkedListClientes);
                break;
            case 4:
                printf("Volviendo al menu principal...\n");
                break;
            }
            system("pause");
        }
    }
    while(optionSort != 4);

    return 0;
}

int controller_filterNotebooks(LinkedList* pLinkedListNotebooks, LinkedList* pLinkedListClientes)
{
    if (ll_isEmpty(pLinkedListNotebooks) == 1)
    {
        printf("\nNo existen mascotas en el sistema. Intente cargarlas para poder filtrarlas.\n");
        return -1;
    }

    int optionSort = 0;
    int selectSort = 0;

    /*
    economica
    normal
    gamer
    */

    do
    {
        menu_DeFiltrado();
        selectSort = validations_getOption(
                         &optionSort,
                         "\nOpcion invalida, vuelva a intentarlo.\n",
                         1,
                         5);
        if(!selectSort)
        {
            switch(optionSort)
            {
            case 1:
            {
                LinkedList* economica = ll_filter(pLinkedListNotebooks,notebooks_filtrarEconomica);
                if(economica != NULL)
                {
                    system("cls");
                    printf("---------------------------------------------------------------------------------------------\n");
                    printf("                                             Economicas \n");
                    printf("---------------------------------------------------------------------------------------------\n");
                    menu_printNotebooks(economica,pLinkedListClientes);
                    ll_deleteLinkedList(economica);
                }
                else
                {
                    ll_deleteLinkedList(economica);
                }
            }
            break;
            case 2:
            {
                LinkedList* normal = ll_filter(pLinkedListNotebooks,notebooks_filtrarNormal);
                if(normal != NULL)
                {
                    system("cls");
                    printf("---------------------------------------------------------------------------------------------\n");
                    printf("                                             Normales \n");
                    printf("---------------------------------------------------------------------------------------------\n");
                    menu_printNotebooks(normal,pLinkedListClientes);
                    ll_deleteLinkedList(normal);
                }
                else
                {
                    ll_deleteLinkedList(normal);
                }
            }
            break;
            case 3:
            {
                LinkedList* gamer = ll_filter(pLinkedListNotebooks,notebooks_filtrarGamer);
                if(gamer != NULL)
                {
                    system("cls");
                    printf("---------------------------------------------------------------------------------------------\n");
                    printf("                                             Gamers \n");
                    printf("---------------------------------------------------------------------------------------------\n");
                    menu_printNotebooks(gamer,pLinkedListClientes);
                    ll_deleteLinkedList(gamer);
                }
                else
                {
                    ll_deleteLinkedList(gamer);
                }
            }
            break;
            case 4:
                printf("Volviendo al menu principal...\n");
                break;
            }
            system("pause");
        }
    }
    while(optionSort != 5);

    return 0;
}

int controller_containsList(LinkedList* pLinkedListNotebooks, LinkedList* pLinkedListClientes)
{
    if (ll_isEmpty(pLinkedListNotebooks) == 1)
    {
        printf("\nNo existen Notebooks en el sistema. Intente cargarlas desde el menu principal primero.\n");
        return -1;
    }
    //Generar una sublista de pLinkedListNotebooks y ver si esta contenida en pLinkedListNotebooks
    //Ver si pLinkedListClientes esta contenido en pLinkedListNotebooks

    int optionSort = 0;
    int selectSort = 0;

    do
    {
        menu_sublist();
        selectSort = validations_getOption(
                         &optionSort,
                         "\nOpcion invalida, vuelva a intentarlo.\n",
                         1,
                         3);
        if(!selectSort)
        {
            switch(optionSort)
            {
            case 1:
            {
                int contiene;
                LinkedList* listaContenida = ll_subList(pLinkedListNotebooks,10,15);
                system("cls");
                printf("_____________________________________________________________________________________________\n");
                printf("                                           Sub-lista 1 \n");
                menu_printNotebooks(listaContenida,pLinkedListClientes);
                printf("_____________________________________________________________________________________________\n");
                printf("\n\nEstara esta sublista contenida en la lista de Notebooks principal?\n");

                if(listaContenida != NULL)
                {
                    contiene = ll_containsAll(pLinkedListNotebooks,listaContenida);
                    if(contiene == 1)
                    {
                        printf("\nSi! La lista esta contenida.\n");
                        ll_deleteLinkedList(listaContenida);
                    }
                    else if(contiene == 0)
                    {
                        printf("\nNo, la lista no esta contenida...\n");
                        ll_deleteLinkedList(listaContenida);
                    }
                }
            }
            break;
            case 2:
            {
                int contiene;
                LinkedList* listaContenidaD = ll_subList(pLinkedListClientes,5,10);

                system("cls");
                printf("____________________________________________________\n");
                printf("                  Sub-lista 2 \n");
                menu_printClientes(listaContenidaD);
                printf("____________________________________________________\n");
                printf("\n\nEstara esta sublista contenida en la lista de Notebooks principal?\n");

                if(listaContenidaD != NULL)
                {
                    contiene = ll_containsAll(pLinkedListNotebooks,listaContenidaD);
                    if(contiene == 1)
                    {
                        printf("\nSi! La lista esta contenida.\n");
                        ll_deleteLinkedList(listaContenidaD);
                    }
                    else if(contiene == 0)
                    {
                        printf("\nNo, la lista no esta contenida...\n");
                        ll_deleteLinkedList(listaContenidaD);
                    }
                }

            }
            break;
            case 3:
                printf("Volviendo al menu principal...\n");
                break;
            }
            system("pause");
        }
    }
    while(optionSort != 3);

    return 0;
}

int controller_settingNotebook(LinkedList* pLinkedListNotebooks, LinkedList* pLinkedListClientes)
{
    if(ll_isEmpty(pLinkedListNotebooks) != 0)
    {
        printf("\nSe deben cargar los datos antes de agregar una Notebook a la lista.\n");
        return -1;
    }

    // preguntar un indice dónde guardarlo
    char indexAsChar[100];
    int index;
    int validIndex;
    int id;

    printf("\n Ingrese una posicion de la lista: ");
    fflush(stdin);
    gets(indexAsChar);
    validIndex = validations_isValidNumber(indexAsChar);
    while(validIndex != 1)
    {
        printf("\n Dato invalido. Ingrese una posicion de la lista: ");
        fflush(stdin);
        gets(indexAsChar);
        validIndex = validations_isValidNumber(indexAsChar);
    }

    index = atoi(indexAsChar);

    if(index >= 0 && index < ll_len(pLinkedListNotebooks))
    {
        // de esa mascota sacar el ID -> para ponerlo en la mascota nueva
        eNotebook* auxNote = ll_get(pLinkedListNotebooks,index);

        if(auxNote != NULL)
        {
            notebooks_getId(auxNote, &id);
        }
    }
    else
    {
        printf("\nEl indice se encuentra fuera de rango.\n");
        return -1;
    }

    eNotebook* newNotebook = NULL;

    char idAsChar[50];
    char marca[100];
    char tipo[50];
    char precio[50];
    char idCliente[50];

    // Ingresar y validar datos
    itoa(id,idAsChar,10);
    notebooks_enterMarca(marca);
    notebooks_enterTipo(tipo);
    notebooks_enterPrecio(precio);

    //imprimir Clientes
    system("cls");
    menu_printClientes(pLinkedListClientes);
    notebooks_enterIdCliente(idCliente);

    // cree una notebook nueva sin añadirla al LL
    newNotebook = note_newParams(idAsChar,marca,tipo,precio,idCliente);

    // guardar la notebook
    if(newNotebook != NULL)
    {
        ll_set(pLinkedListNotebooks,index,newNotebook);
        return 0;
    }

    return -1;
}

int controller_pushNotebook(LinkedList* pLinkedListNotebooks, LinkedList* pLinkedListClientes)
{
    if(ll_isEmpty(pLinkedListNotebooks) != 0)
    {
        printf("\nSe deben cargar los datos antes de agregar una Notebook a la lista.\n");
        return -1;
    }

    // preguntar un indice dónde guardarlo (validar!!!!)
    char indexAsChar[100];
    int index;
    int validIndex;


    printf("\n Ingrese una posicion de la lista: ");
    fflush(stdin);
    gets(indexAsChar);
    validIndex = validations_isValidNumber(indexAsChar);
    while(validIndex != 1)
    {
        printf("\n Dato invalido. Ingrese una posicion de la lista: ");
        fflush(stdin);
        gets(indexAsChar);
        validIndex = validations_isValidNumber(indexAsChar);
    }

    index = atoi(indexAsChar);

    if(index < 0 || index >= ll_len(pLinkedListNotebooks))
    {
        printf("\nIndice fuera del rango. \n");
        return -1;
    }

    eNotebook* newNotebook = NULL;
    int id;
    char idAsChar[50];
    char marca[100];
    char tipo[50];
    char precio[50];
    char idCliente[50];

    // Ingresar y validar datos
    notebooks_enterMarca(marca);
    notebooks_enterTipo(tipo);
    notebooks_enterPrecio(precio);
    system("cls");
    menu_printClientes(pLinkedListClientes);
    notebooks_enterIdCliente(idCliente);

    // Id autoincremental
    Node* currentNode = pLinkedListNotebooks->pFirstNode;

    while (currentNode->pNextNode != NULL)
    {
        currentNode = currentNode->pNextNode;
    }

    eNotebook* auxNotebook = (eNotebook*)currentNode->pElement;
    notebooks_getId(auxNotebook,&id);
    id += 1;
    itoa(id, idAsChar, 10);

    newNotebook = note_newParams(idAsChar,marca,tipo,precio,idCliente);

    if(newNotebook != NULL)
    {
        ll_push(pLinkedListNotebooks,index,newNotebook);
    }

    return 0;
}
