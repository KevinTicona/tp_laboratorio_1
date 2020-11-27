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
        printf("\nSe deben cargar los datos antes de agregar una Notebook a la lista.\n");
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
        printf("\nSe deben cargar los datos antes de editar una Notebook de la lista.\n");
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


