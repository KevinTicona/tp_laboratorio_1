#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
typedef struct
{
    int id;
    char nombre[128];
    int horasTrabajadas;
    int sueldo;
}Employee;

Employee* employee_new();
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr);

void employee_delete();

int employee_setId(Employee* this,int id);
int employee_getId(Employee* this,int* id);

int employee_setNombre(Employee* this,char* nombre);
int employee_getNombre(Employee* this,char* nombre);

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);

int employee_setSueldo(Employee* this,int sueldo);
int employee_getSueldo(Employee* this,int* sueldo);

int validations_isValidNumber(char* str);

int employee_SortByName(void* empleadoA, void* empleadoB);
int employee_SortById(void* empleadoA, void* empleadoB);
int employee_SortByWorkHours(void* empleadoA, void* empleadoB);
int employee_SortBySalary(void* empleadoA, void* empleadoB);

void imprimir_UnEmpleado(Employee* unEmployee);
void imprimir_Emcabezado();
void imprimir_MenuDeModificaciones();
int imprimir_Empleados(LinkedList* pArrayListEmployee);
void imprimir_MenuDeOrdenamiento();
void imprimir_Menu();

int employee_setIdStr(Employee* this,char* id);
int employee_setSueldoStr(Employee* this,char* sueldo);
int employee_setHorasTrabajadasStr(Employee* this,char* horasTrabajadas);
int employee_getIdStr(Employee* this,char* id);
int employee_getSueldoStr(Employee* this,char* sueldo);
int employee_getHorasTrabajadasStr(Employee* this,char* horasTrabajadas);

int getopcion(int* pResult, char* errorMsj, int min, int max);

#endif // employee_H_INCLUDED
