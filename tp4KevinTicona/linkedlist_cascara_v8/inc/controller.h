#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED
#include "../inc/LinkedList.h"

int controller_loadNotebooksFromText(char* path, LinkedList* pLinkedListNotebooks);
int controller_loadClientesFromText(char* path, LinkedList* pLinkedListClientes);
int controller_loadNotebooksFromBinary(char* path, LinkedList* pLinkedListNotebooks);
int controller_loadClientesFromBinary(char* path, LinkedList* pLinkedListClientes);
int controller_addNotebook(LinkedList* pLinkedListNotebooks, LinkedList* pLinkedListClientes);
int controller_editeNotebook(LinkedList* pLinkedListNotebooks, LinkedList* pLinkedListClientes);
int controller_removeNotebook(LinkedList* pLinkedListNotebooks,LinkedList* pLinkedListClientes);
int controller_removeNotebookPop(LinkedList* pLinkedListNotebooks,LinkedList* pLinkedListClientes);
int controller_ListNotebooks(LinkedList* pLinkedListNotebooks, LinkedList* pLinkedListClientes);
int controller_ListClientes(LinkedList* pLinkedListClientes);
int controller_cloneList(LinkedList* pLinkedListNotebooks, LinkedList* pLinkedListClientes);
int controller_makeSubList(LinkedList* pLinkedListNotebooks, LinkedList* pLinkedListClientes);
int controller_saveNotebooksAsText(char* path, LinkedList* pLinkedListNotebooks);
int controller_saveClientesAsText(char* path, LinkedList* pLinkedListClientes);
int controller_saveNotebooksAsBinary(char* path, LinkedList* pLinkedListNotebooks);
int controller_saveClientesAsBinary(char* path, LinkedList* pLinkedListClientes);
int controller_freeResources(LinkedList* this);
int controller_sortNotebooks(LinkedList* pLinkedListNotebooks, LinkedList* pLinkedListClientes);
int controller_filterNotebooks(LinkedList* pLinkedListNotebooks, LinkedList* pLinkedListClientes);
int controller_containsList(LinkedList* pLinkedListNotebooks, LinkedList* pLinkedListClientes);
int controller_settingNotebook(LinkedList* pLinkedListNotebooks, LinkedList* pLinkedListClientes);
int controller_pushNotebook(LinkedList* pLinkedListNotebooks, LinkedList* pLinkedListClientes);
#endif // CONTROLLER_H_INCLUDED

