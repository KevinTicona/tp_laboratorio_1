#ifndef NOTEBOOKS_H_INCLUDED
#define NOTEBOOKS_H_INCLUDED
#include "../inc/clientes.h"
typedef struct
{
    int id;
    char marca[100];
    char tipo[50];
    int precio;
    int idCliente;
}eNotebook;


eNotebook* note_new();

eNotebook* note_newParams(char* id, char* marca, char* tipo, char* precio, char* idCliente);
void notebooks_delete(eNotebook* this);
int notebooks_setId(eNotebook* this,int id);
int notebooks_getId(eNotebook* this,int* id);
int notebooks_setModelo(eNotebook* this,char* marca);
int notebooks_getModelo(eNotebook* this,char* marca);
int notebooks_setTipo(eNotebook* this,char* tipo);
int notebooks_getTipo(eNotebook* this,char* tipo);
int notebooks_setIdCliente(eNotebook* this,int idCliente);
int notebooks_getIdCliente(eNotebook* this,int* idCliente);
int notebooks_setPrecio(eNotebook* this,int precio);
int notebooks_getPrecio(eNotebook* this,int* precio);
void notebooks_ValidMarca(char* validMarca);
void notebooks_ValidTipo(char* validTipo);
void notebooks_ValidPrecio(char* validPrecio);
void notebooks_ValidIdCliente(char* validIdCliente);
eNotebook* notebooks_searchByID(LinkedList* this,int id);
int notebooks_filtrarEconomica(void* NoteTipo);
int notebooks_filtrarNormal(void* NoteTipo);
int notebooks_filtrarGamer(void* NoteTipo);
void menu_printCliente(eCliente* unCliente);
int menu_printClientes(LinkedList* this);
void menu_printNotebook(LinkedList* this, eNotebook* actualNotebook);
int menu_printNotebooks(LinkedList* pLinkedListNotebooks,LinkedList* pClientes);
void menu_encabezadoNotebook();
void menu_modificaciones();
void menu_DeOrdenamiento();
void menu_DeFiltrado();
void menu_sublist();
void menu_confirmacion(char* pConfirm);
int notebook_SortByName(void* notebookA, void* notebookB);
int notebook_SortByTipo(void* notebookA, void* notebookB);
int notebook_SortById(void* notebookA, void* notebookB);
void notebooks_enterMarca(char* marcaValida);
void notebooks_enterTipo(char* tipoValidado);
void notebooks_enterPrecio(char* precioValidado);
void notebooks_enterIdCliente(char* idClienteValidado);
void menu_main();

#endif // NOTEBOOKS_H_INCLUDED
