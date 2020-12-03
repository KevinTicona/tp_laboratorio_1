#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"
#include "../inc/parser.h"
#include"../inc/notebooks.h"
#include "../inc/clientes.h"
#include "../inc/validaciones.h"


eNotebook* note_new()
{
    eNotebook* nuevo = (eNotebook*) malloc(sizeof(eNotebook));

    if(nuevo != NULL)
    {
        nuevo->id = 0;
        strcpy(nuevo->marca, "");
        strcpy(nuevo->tipo, "");
        nuevo->precio = 0;
        nuevo->idCliente = 0;
    }

    return nuevo;
}

eNotebook* note_newParams(char* id, char* marca, char* tipo, char* precio, char* idCliente
)
{
    int validIdResult = validations_isValidNumber(id);
    int validPrecioResult = validations_isValidNumber(precio);
    int validIdClienteResult = validations_isValidNumber(idCliente);

    int validId;
    int validPrecio;
    int validIdCliente;

    if(!validIdResult || !validPrecioResult || !validIdClienteResult)
    {
        if(!validIdResult)
        {
            printf("\nEl Id de la nueva Mascota es invalido. Valor recibido: %s\n", id);
        }
        else if(!validPrecioResult)
        {
            printf("\nLa edad de la nueva Mascota es invalida. Valor recibido: %s\n", precio);
        }
        else if(!validIdClienteResult)
        {
            printf("\nEl Id del duenio de la nueva Mascota es invalido. Valor recibido: %s\n", idCliente);
        }

        return NULL;
    }

    validId = atoi(id);
    validPrecio = atoi(precio);
    validIdCliente = atoi(idCliente);
        //printf("\nholasa\n");
    eNotebook* newNotebook = note_new();

    if(newNotebook != NULL)
    {
        if(!(!notebooks_setId(newNotebook,validId) &&
                !notebooks_setModelo(newNotebook,marca) &&
                !notebooks_setTipo(newNotebook,tipo) &&
                !notebooks_setPrecio(newNotebook,validPrecio) &&
                !notebooks_setIdCliente(newNotebook,validIdCliente)
            ))
        {
            printf("\nOcurrio un problema al inicializar las propiedades de la nueva Mascota. La mismo no sera creada.\n");
            newNotebook = NULL;
            free(newNotebook);
        }
    //printf("\nhola\n");
    }
    return newNotebook;
}

void notebooks_delete(eNotebook* this)
{
    free(this);
}

int notebooks_setId(eNotebook* this,int id)
{
    int error = -1;

    if(this != NULL && id > 0)
    {
        this->id = id;
        error = 0;
    }
    return error;
}

int notebooks_getId(eNotebook* this,int* id)
{
    int error = -1;

    if(this != NULL && id != NULL)
    {
        *id = this->id;
        error = 0;
    }
    return error;
}

int notebooks_setModelo(eNotebook* this,char* marca)
{
    int error = -1;

    if(this != NULL && marca != NULL && validations_isValidName(marca))
    {
        strcpy(this->marca, marca);
        error = 0;
    }
    return error;
}

int notebooks_getModelo(eNotebook* this,char* marca)
{
    int error = -1;

    if(this != NULL && marca != NULL)
    {
        strcpy(marca, this->marca);
        error = 0;
    }
    return error;
}

int notebooks_setTipo(eNotebook* this,char* tipo)
{
    int error = -1;

    if(this != NULL && tipo != NULL && validations_isValidType(tipo))
    {
        strcpy(this->tipo, tipo);
        error = 0;
    }
    return error;
}

int notebooks_getTipo(eNotebook* this,char* tipo)
{
    int error = -1;

    if(this != NULL && tipo != NULL)
    {
        strcpy(tipo, this->tipo);
        error = 0;
    }
    return error;
}

int notebooks_setIdCliente(eNotebook* this,int idCliente)
{
    int error = -1;
    char idStr[50];
    itoa(idCliente,idStr,10);

    if(this != NULL && validations_isValidNumber(idStr))
    {
        this->idCliente = idCliente;
        error = 0;
    }
    return error;
}

int notebooks_getIdCliente(eNotebook* this,int* idCliente)
{
    int error = -1;

    if(this != NULL && idCliente != NULL)
    {
        *idCliente = this->idCliente;
        error = 0;
    }
    return error;
}

int notebooks_setPrecio(eNotebook* this,int precio)
{
    int error = -1;
    char precioStr[50];
    itoa(precio,precioStr,10);

    if(this != NULL && validations_isValidNumber(precioStr))
    {
        this->precio = precio;
        error = 0;
    }
    return error;
}

int notebooks_getPrecio(eNotebook* this,int* precio)
{
    int error = -1;

    if(this != NULL && precio != NULL)
    {
        *precio = this->precio;
        error = 0;
    }
    return error;
}
//---------------------------------------------------------------

void notebooks_ValidMarca(char* validMarca)
{
    char marca[100];
    int marcaValida;

    printf("\nIngrese Marca: ");
    fflush(stdin);
    gets(marca);
    marcaValida = validations_isValidName(marca);
    while(marcaValida != 1)
    {
        printf("\nDato invalido. Ingrese Marca: ");
        fflush(stdin);
        gets(marca);
        marcaValida = validations_isValidName(marca);
    }
    validations_formatStr(marca);
    strcpy(validMarca,marca);
}

void notebooks_ValidTipo(char* validTipo)
{
    char tipo[100];
    int tipoValido;

    printf("  Tipos de Notebooks  \n");
    printf("-----------------------\n");
    printf("Economica\n");
    printf("Normal\n");
    printf("Gamer\n");
    printf("-----------------------\n");

    printf("\Escriba el tipo de notebook:");
    fflush(stdin);
    gets(tipo);
    tipoValido = validations_isValidType(tipo);
    while(tipoValido != 1)
    {
        printf("\nDato invalido. Escriba el tipo de notebook: ");
        fflush(stdin);
        gets(tipo);
        tipoValido = validations_isValidType(tipo);
    }
    strcpy(validTipo,tipo);
}

void notebooks_ValidPrecio(char* validPrecio)
{
    char precio[100];
    int precioValido;

    printf("\nIngrese Precio: ");
    fflush(stdin);
    gets(precio);
    precioValido = validations_isValidPrecio(precio);
    while(precioValido != 1)
    {
        printf("\nDato invalido. Ingrese Precio: ");
        fflush(stdin);
        gets(precio);
        precioValido = validations_isValidSex(precio);
    }
    strcpy(validPrecio,precio);
}

void notebooks_ValidIdCliente(char* validIdCliente)
{
    char idCliente[50];
    int idClienteValidado;

    printf("\n\nIngrese Id del Cliente: ");
    fflush(stdin);
    gets(idCliente);
    idClienteValidado = validations_isValidIdCliente(idCliente);
    while(idClienteValidado != 1)
    {
        printf("\nDato invalido. Ingrese el id del Cliente: ");
        fflush(stdin);
        gets(idCliente);
        idClienteValidado = validations_isValidIdCliente(idCliente);
    }
    strcpy(validIdCliente,idCliente);
}

eNotebook* notebooks_searchByID(LinkedList* this,int id)
{
    eNotebook* auxNotebook = NULL;
    int len = ll_len(this);
    int index = 0;
    Node* currentNode = this->pFirstNode;

    if(this != NULL)
    {
        while (index < len)
        {
            auxNotebook = (eNotebook*)ll_get(this,index);

            if(auxNotebook->id == id)
            {
                break;
            }
            currentNode = currentNode->pNextNode;
            index++;
        }
    }
    return auxNotebook;
}

//--------------------------------------------

int notebooks_filtrarEconomica(void* NoteTipo)
{
    int retorno = 0;
    eNotebook* auxNotebook = NULL;

    if(NoteTipo != NULL)
    {
        auxNotebook = (eNotebook*) NoteTipo;

        if(strcmp(auxNotebook->tipo,"Economica") == 0)
        {
            retorno = 1;
        }
    }
    return retorno;
}

int notebooks_filtrarNormal(void* NoteTipo)
{
    int retorno = 0;
    eNotebook* auxNotebook = NULL;

    if(NoteTipo != NULL)
    {
        auxNotebook = (eNotebook*) NoteTipo;

        if(strcmp(auxNotebook->tipo,"Normal") == 0)
        {
            retorno = 1;
        }
    }
    return retorno;
}

int notebooks_filtrarGamer(void* NoteTipo)
{
    int retorno = 0;
    eNotebook* auxNotebook = NULL;

    if(NoteTipo != NULL)
    {
        auxNotebook = (eNotebook*) NoteTipo;

        if(strcmp(auxNotebook->tipo,"Gamer") == 0)
        {
            retorno = 1;
        }
    }
    return retorno;
}


void menu_printCliente(eCliente* unCliente)
{
    int auxId;
    char nombre[100];
    char sexo[50];

    cliente_getId(unCliente,&auxId);
    cliente_getNombre(unCliente, nombre);
    cliente_getSexo(unCliente, sexo);

    printf("\n%4d  %20s           %2s\n",
           auxId,
           nombre,
           sexo);
}

int menu_printClientes(LinkedList* this)
{
    int currentNodeIndex = 0;
    int linkedListSize = ll_len(this);
    eCliente* currentDueno;
    Node* currentNode = this->pFirstNode;

    printf("             Listado de Clientes                \n");
    printf("  id           Nombre                    Sexo   \n");
    printf("------------------------------------------------\n");
    while (currentNodeIndex < linkedListSize)
    {
        currentDueno = (eCliente*)ll_get(this, currentNodeIndex);

        menu_printCliente(currentDueno);

        currentNode = currentNode->pNextNode;
        currentNodeIndex++;
    }

    return 0;
}

void menu_printNotebook(LinkedList* this, eNotebook* actualNotebook)
{
    eCliente* auxCliente = cliente_searchByID(this,actualNotebook->idCliente);
    int idActual;
    int precioActual;
    char marcaActual[100];
    char tipoActual[100];
    char nombreCliente[100];

    notebooks_getId(actualNotebook,&idActual);
    notebooks_getModelo(actualNotebook,marcaActual);
    notebooks_getTipo(actualNotebook,tipoActual);
    notebooks_getPrecio(actualNotebook,&precioActual);
    cliente_getNombre(auxCliente,nombreCliente);

    printf("\n%4d  %15s   %15s            %10d        %20s\n",
           idActual,
           marcaActual,
           tipoActual,
           precioActual,
           nombreCliente);
}

int menu_printNotebooks(LinkedList* pLinkedListNotebooks,LinkedList* pClientes)
{
    int actualNodeIndex = 0;
    int linkedListSize = ll_len(pLinkedListNotebooks);

    eNotebook* actualNotebook;
    Node* actualNode = pLinkedListNotebooks->pFirstNode;

    // Recorremos la Linked List con un índice (un número)
    // Aunque también podríamos recorrer la lista hasta llegar al final verificando si el pNextNode del Nodo actual no sea NULL

    printf("                                  Listado de Notebooks                              \n");
    printf("  Id           Marca               Tipo               Precio                 Cliente\n");
    printf("------------------------------------------------------------------------------------\n");

    while (actualNodeIndex < linkedListSize)
    {
        actualNotebook = (eNotebook*)ll_get(pLinkedListNotebooks, actualNodeIndex);

        menu_printNotebook(pClientes,actualNotebook);

        actualNode = actualNode->pNextNode;
        actualNodeIndex++;
    }

    return 0;
}


void menu_encabezadoNotebook()
{
    system("cls");
    printf("                                  Listado de Notebooks                              \n");
    printf("  Id           Marca               Tipo               Precio                 Cliente\n");
    printf("------------------------------------------------------------------------------------\n");
}

void menu_modificaciones()
{
    printf("\n\n");
    printf("1. Modificar Marca.\n");
    printf("2. Modificar Tipo.\n");
    printf("3. Modificar Precio.\n");
    printf("4. Volver atras.\n");
    printf("\n\n");
}

void menu_DeOrdenamiento()
{
    system("cls");
    printf("                            Tipos de Ordenamientos                    \n");
    printf("------------------------------------------------------------------------------------\n");
    printf("1. Ordenar Notebooks por Nombre.\n");
    printf("2. Ordenar Notebooks por Id.\n");
    printf("3. Ordenar Notebooks por Tipo.\n");
    printf("4. Volver al menu principal.\n");
}
void menu_DeFiltrado()
{
    system("cls");
    printf("                            Tipos de Filtrado                    \n");
    printf("------------------------------------------------------------------------------------\n");
    printf("1. Filtrar Economica.\n");
    printf("2. Filtrar Normal.\n");
    printf("3. Filtrar Gamer.\n");
    printf("5. Volver al menu principal.\n");
}

void menu_sublist()
{
    system("cls");
    printf("                            SubList                    \n");
    printf("------------------------------------------------------------------------------------\n");
    printf("1. Revisar si la lista de Notebooks esta contenida en la lista de Notebooks principal.\n");
    printf("2. Revisar si la lista de Clientes esta contenida en la lista de Notebooks.\n");
    printf("3. Volver al menu principal.\n");
}
void menu_confirmacion(char* pConfirm)
{
    char confirmacion[50];
    printf("\nConfirmar cambios? s - si; n - no\n");
    fflush(stdin);
    gets(confirmacion);
    strlwr(confirmacion);

    while(strcmp(confirmacion,"s") != 0 && strcmp(confirmacion,"si") != 0
            && strcmp(confirmacion,"n") != 0 && strcmp(confirmacion,"no") != 0)
    {
        printf("Opcion invalida. s - si; n - no\n");
        fflush(stdin);
        gets(confirmacion);
        strlwr(confirmacion);
    }
    strcpy(pConfirm, confirmacion);
}

int notebook_SortByName(void* notebookA, void* notebookB)
{
    int retorno = 0;
    eNotebook* noteA;
    eNotebook* noteB;

    if(notebookA != NULL && notebookB != NULL)
    {
        noteA = notebookA;
        noteB = notebookB;

        retorno = strcmp(noteA->marca, noteB->marca);
    }

    return retorno;
}

int notebook_SortByTipo(void* notebookA, void* notebookB)
{
    int retorno = 0;
    eNotebook* tipoA;
    eNotebook* tipoB;

    if(notebookA != NULL && notebookB != NULL)
    {
        tipoA = notebookA;
        tipoB = notebookB;

        retorno = strcmp(tipoA->tipo, tipoB->tipo);
    }

    return retorno;
}

int notebook_SortById(void* notebookA, void* notebookB)
{
    int retorno = 0;
    int idA;
    int idB;

    if(notebookA != NULL && notebookB != NULL)
    {
        if(
            !notebooks_getId((eNotebook*)notebookA, &idA) &&
            !notebooks_getId((eNotebook*)notebookB, &idB)
        )
        {
            if(idA > idB)
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

void notebooks_enterMarca(char* marcaValida)
{
    char marca[100];
    int marcaValidada;

    printf("\nIngrese la marca: ");
    fflush(stdin);
    gets(marca);
    marcaValidada = validations_isValidName(marca);
    while(marcaValidada != 1)
    {
        printf("\nDato invalido. Ingrese la marca: ");
        fflush(stdin);
        gets(marca);
        marcaValidada = validations_isValidName(marca);
    }
    validations_formatStr(marca);
    strcpy(marcaValida,marca);
}

void notebooks_enterTipo(char* tipoValidado)
{
    char tipo[100];
    int tipoValido;

    printf("\nIngrese tipo: ");
    fflush(stdin);
    gets(tipo);
    tipoValido = validations_isValidType(tipo);
    while(tipoValido != 1)
    {
        printf("\nDato invalido. Ingrese tipo: ");
        fflush(stdin);
        gets(tipo);
        tipoValido = validations_isValidType(tipo);
    }
    strcpy(tipoValidado,tipo);
}

void notebooks_enterPrecio(char* precioValidado)
{
    char precio[50];
    int precioValido;

    printf("\nIngrese el precio: ");
    fflush(stdin);
    gets(precio);
    precioValido = validations_isValidPrecio(precio);
    while(precioValido != 1)
    {
        printf("\nDato invalido. Ingrese el precio: ");
        fflush(stdin);
        gets(precio);
        precioValido = validations_isValidPrecio(precio);
    }
    strcpy(precioValidado,precio);
}

void notebooks_enterIdCliente(char* idClienteValidado)
{
    char idCliente[50];
    int idClienteValido;

    printf("\n\nIngrese el Id del Cliente: ");
    fflush(stdin);
    gets(idCliente);
    idClienteValido = validations_isValidIdCliente(idCliente);
    while(idClienteValido != 1)
    {
        printf("\nDato invalido. Ingrese el Id del Cliente: ");
        fflush(stdin);
        gets(idCliente);
        idClienteValido = validations_isValidIdCliente(idCliente);
    }
    strcpy(idClienteValidado,idCliente);
}

void menu_main()
{
    system("cls");
    printf("                                 **** Notebooks ****                   \n");
    printf("__________________________________________________________________________________\n");
    printf("1. Cargar los datos de las notebooks desde el archivo data.csv (modo texto).\n");
    printf("2. Cargar los datos de las notebooks desde el archivo data.bin (modo binario).\n");
    printf("3. Alta de notebook.\n");
    printf("4. Modificar datos de notebook.\n");
    printf("5. Baja de notebook.\n");
    printf("6. Baja de notebook con pop.\n");
    printf("7. Listar notebooks.\n");
    printf("8. Listar Clientes.\n");
    printf("9. Ordenar notebooks.\n");
    printf("10. Filtrar notebooks por tipo.\n");
    printf("11. Clonar notebooks.\n");
    printf("12. Revisar si una notebook o una lista esta contenida en la lista de notebooks.\n");
    printf("13. Generar sublista de notebooks.\n");
    printf("14. Setear una notebook nueva en un indice de la lista de notebooks.\n");
    printf("15. Hacer un push de una notebook nueva en un indice de la lista de notebooks.\n");
    printf("16. Guardar los datos de las notebooks en el archivo data.csv (modo texto).\n");
    printf("17. Guardar los datos de las notebooks en el archivo data.bin (modo binario)..\n");
    printf("18. Salir.\n");
}
