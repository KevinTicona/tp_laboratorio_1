#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

typedef struct
{
    int id;
    char nombre[100];
    char sexo[1];
}eCliente;


eCliente* cliente_new();

eCliente* cliente_newParams(char* id, char* nombre, char* sexo);

void cliente_delete(eCliente* this);

int cliente_setId(eCliente* this,int id);

int cliente_getId(eCliente* this,int* id);

int cliente_setNombre(eCliente* this,char* nombre);

int cliente_getNombre(eCliente* this,char* nombre);

int cliente_setSexo(eCliente* this,char* sexo);

int cliente_getSexo(eCliente* this,char* sexo);

eCliente* cliente_searchByID(LinkedList* this,int id);

#endif // CLIENTES_H_INCLUDED
