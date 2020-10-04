#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "arrayEmployees.h"
#define TAM 1000
#define ASC 1 // ascendiente
#define DESC 0 // desenciente


int main()
{
    eEmployee lista[TAM];

    int id = 0;
    char seguir = 's';
    int flag = 0;
    int aux;
    int aux2;

    if(initEmployees(lista,TAM)==0)
    {
        printf("Personas inicializadas con exito!!!\n");
    }
    else
    {
        printf("No se pudo inicializar las personas !!!\n");
    }

    while(seguir == 's')
    {
        switch(menuEmployee())
        {
        case 1:

            if(addEmployee(lista,TAM,id)==0)
            {
                id++;
                printf("Alta exitosa!!\n\n");
                flag = 1;
            }
            else
            {
                printf("Problemas para realizar el alta!!\n\n");
            }
            printEmployees(lista,TAM);

            break;
        case 2:
            if(!flag)
            {

                printf("No hay Empleados registrados\n");
                break;
            }
            if(modificarEmplyee(lista,TAM) == 0)
            {
                printf("\nModificacion Exitosa.\n");
            }
            else
            {
                printf("Algo salio Mal.\n");
            }
            break;
        case 3:
            if(!flag)
            {
                printf("No hay Empleados registrados\n");
                break;
            }
            if(removeEmployee(lista,TAM)== 0 )
            {
                printf("Todo salio bien.\n");
            }
            else if (removeEmployee(lista,TAM)==1)
            {
                printf("la baja fue cancelada por el usuario.\n");
            }
            else
            {
                printf("Error. Intente de nuevo\n");
            }
            break;
        case 4:
            if(!flag)
            {
                printf("No hay Empleados registrados\n");
                break;
            }
            printf("----Informes----\n");
            printf("1- Listado de los empleados alfabeticamanete por Apellido y sector.\n");
            printf("2- Total y promedio de los Salarios, y cuantos empleados supera el salario promedio.\n");
            scanf("%d",&aux);

            switch(aux)
            {
            case 1:
                    printf("-Tipo de orden-\n");
                    printf("1-Creciente.\n");
                    printf("2-Decreciente.\n");
                    printf("Opcion: ");
                    scanf("%d",&aux2);
                    if(aux2 == 1){
                        sortEmployees(lista,TAM,ASC,DESC);
                    }else if(aux2 == 2){
                        sortEmployees(lista,TAM,DESC,ASC);
                    }else{
                        printf("Dato invalido.\n");
                    }
                    system("cls");
                    printEmployees(lista,TAM);
                break;
            case 2:
                    printEmployees(lista,TAM);
                    totalPromedioSuperan(lista,TAM);
                break;
            default:
                    printf("Dato Invalido.\n");
                break;
            }
            break;

        case 5:
            seguir = 'n';
            break;
        default:
            break;
        }
        system("pause");
    }

    return 0;
}
