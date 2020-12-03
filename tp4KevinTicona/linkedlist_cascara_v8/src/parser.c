#include <stdio.h>
#include <stdlib.h>
#include "../inc/LinkedList.h"
#include "../inc/parser.h"
#include"../inc/notebooks.h"
#include "../inc/clientes.h"


int parser_notebooksFromText(FILE* pFile, LinkedList* pLinkedListNotebooks)
{
    int amountOfDataRead;
    char id[50];
    char marca[50];
    char tipo[50];
    char precio[50];
    char idCliente[50];

    if (pFile == NULL || pLinkedListNotebooks == NULL)
    {
        return -1;
    }

    // Forzamos lectura de la primer linea del archivo ya que esta contiene los encabezados
    fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^\n]\n",id,marca,tipo,precio,idCliente);

    do
    {
        amountOfDataRead = fscanf(
                                  pFile,
                                  "%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
                                  id,
                                  marca,
                                  tipo,
                                  precio,
                                  idCliente
                              );

        if (amountOfDataRead == 5)
        {
            eNotebook* newNotebook = note_newParams(id,marca,tipo,precio,idCliente);

            if (newNotebook != NULL)
            {
                ll_add(pLinkedListNotebooks, newNotebook);
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

int parser_clientesFromText(FILE* pFile, LinkedList* pLinkedListClientes)
{
    int amountOfDataRead;
    char id[50];
    char nombre[50];
    char sexo[50];

    if (pFile == NULL || pLinkedListClientes == NULL)
    {
        return -1;
    }

    fscanf(pFile,"%[^,],%[^,],%[^\n]\n",id,nombre,sexo);

    do
    {
        amountOfDataRead = fscanf(pFile,"%[^,],%[^,],%[^\n]\n",id,nombre,sexo);

        if (amountOfDataRead == 3)
        {
            eCliente* newCliente = cliente_newParams(id,nombre,sexo);

            if (newCliente != NULL)
            {
                ll_add(pLinkedListClientes, newCliente);
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

int parser_notebooksFromBinary(FILE* pFile, LinkedList* pLinkedListNotebooks)
{
    if (pFile == NULL || pLinkedListNotebooks == NULL)
    {
        return -1;
    }

    eNotebook* noteTemporal;

    while (!feof(pFile))
    {
        noteTemporal = (eNotebook*)malloc(sizeof(eNotebook));

        if (fread(noteTemporal, sizeof(eNotebook), 1, pFile) == 1)
        {
            ll_add(pLinkedListNotebooks, noteTemporal);
        }
    }

    return 0;
}

int parser_clientesFromBinary(FILE* pFile, LinkedList* pLinkedListClientes)
{
    if (pFile == NULL || pLinkedListClientes == NULL)
    {
        return -1;
    }

    eCliente* clienteTemporal;

    while (!feof(pFile))
    {
        clienteTemporal = (eCliente*)malloc(sizeof(eCliente));

        if (fread(clienteTemporal, sizeof(eCliente), 1, pFile) == 1)
        {
            ll_add(pLinkedListClientes, clienteTemporal);
        }
    }

    return 0;
}
