#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int main()
{
    char seguir = 's';
    int opcion = 0;
    float a = 0;
    float b = 0;
    float rSuma = 0;
    float rResta = 0;
    float rDivision = 0;
    float rMultiplicacion = 0;
    int rFact1 = 0;
    int rFact2 = 0;
    int flag = 0;

    while(seguir == 's')
    {
        system("cls");
        printf("1- Ingresar 1er operando (A=%.2f)\n",a);
        printf("2- Ingresar 2do operando (B=%.2f)\n",b);
        printf("3- Calcular todas las operaciones");
        printf("a- Calcular la suma (%.2f+%.2f)\n",a,b);
        printf("b- Calcular la resta (%.2f-%.2f)\n",a,b);
        printf("c- Calcular la division (%.2f/%.2f)\n",a,b);
        printf("d- Calcular la multiplicacion (%.2f*%.2f)\n",a,b);
        printf("e- Calcular el factorial (%d) y (%d)\n",(int)a,(int)b);
        printf("4- Informar Resultados \n");
        printf("5- Salir");
        printf("\n Eliga una de las Opciones: ");
        fflush(stdin);
        scanf("%d",&opcion);
        system("cls");
        switch(opcion)
        {
        case 1:
            printf("\nIngrese el primer operando: ");
            scanf("%f",&a);
            break;
        case 2:
            printf("\nIngrese el segundo operando: ");
            scanf("%f",&b);
            break;
        case 3:
            rSuma = sumar(a,b);
            rResta = resta(a,b);
            rDivision = division(a,b);
            rMultiplicacion = multiplicacion(a,b);
            rFact1 = (int)factorial(a);
            rFact2 = (int)factorial(b);
            printf("\n Las funciones se realizaron.\n");
            flag = 1;
            break;
        case 4:
            if(flag == 1)
            {
                printf("El resultado de la Suma es %.2f\n",rSuma);
                printf("El resultado de la Resta es %.2f\n",rResta);
                if(!b)
                {
                    printf("No se puede dividir por 0, vuelva ingrese el operador B \n");
                }
                else
                {
                    printf("El resultado de la Division es %.2f\n",rDivision);
                }
                printf("El resultado de la Multiplicacion es %.2f\n",rMultiplicacion);
                printf("El resultado del Factorial A es: %d y el Factorial B es: %d\n",rFact1,rFact2);
            }
            else
            {
                printf("\n Debes calcular las funciones antes de mostrar \n");

            }
            break;
        case 5:
            seguir = 'n';
            break;
        default:
            printf("\n Comando desconocido \n");
            break;
        }
        system("pause");
    }
    return 0;

}
