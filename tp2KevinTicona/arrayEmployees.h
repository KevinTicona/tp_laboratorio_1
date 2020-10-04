#ifndef ARRAYEMPLOYEES_H_INCLUDED
#define ARRAYEMPLOYEES_H_INCLUDED
typedef struct
{
 int id;
 char name[51];
 char lastName[51];
 float salary;
 int sector;
 int isEmpty;// 1 estaVacia  si vale 0 guardaDatos

}eEmployee;
#endif // ARRAYEMPLOYEES_H_INCLUDED


int initEmployees(eEmployee list[], int len);
int addEmployee(eEmployee list[], int len, int id);
int removeEmployee(eEmployee list[], int len);
int printEmployees(eEmployee list[], int length);
void printEmployee(eEmployee Emplo);
int findEmployeeById(eEmployee list[], int len, int id);
int findFree(eEmployee list[], int len);
int sortEmployees(eEmployee list[], int len, int criterioS, int criterioA);
int menuEmployee();
int validarNumero(char num[]);
int validarCadena(char cadena[]);
void orderName(char name[]);
int modificarEmplyee(eEmployee list[], int len);
void totalPromedioSuperan(eEmployee list[], int len);
