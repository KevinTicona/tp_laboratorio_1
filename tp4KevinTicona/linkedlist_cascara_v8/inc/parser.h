#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

int parser_notebooksFromText(FILE* pFile, LinkedList* pLinkedListNotebooks);

int parser_clientesFromText(FILE* pFile, LinkedList* pLinkedListClientes);

int parser_notebooksFromBinary(FILE* pFile, LinkedList* pLinkedListNotebooks);

int parser_clientesFromBinary(FILE* pFile, LinkedList* pLinkedListClientes);
#endif // PARSER_H_INCLUDED
