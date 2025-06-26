#include <stdio.h>
#include <string.h>
#include "funciones.h"

int main()
{
    int opcion;
    int datosInicializados = 0;

    do
    {
        printf("\n\n--- Sistema de Gestion de Repuestos Automotrices ---\n");
        printf("1. Inicializar/Reiniciar Datos\n");
        printf("2. Ver Catalogo de Productos\n");
        printf("3. Registrar Venta\n");
        printf("4. Ver Registro de Clientes\n");
        printf("5. Ver Historial de Ventas\n");
        printf("6. Ver Estadisticas de Ventas\n");
        printf("7. Salir\n");
        printf("Seleccione una opcion: ");

        if (scanf("%d", &opcion) != 1)
        {
            printf("Entrada no valida. Por favor, ingrese un numero.\n");
            while (getchar() != '\n')
                ;
            opcion = -1;
        }

        switch (opcion)
        {
        case 1:
            inicializarDatos();
            datosInicializados = 1;
            printf("\nDatos inicializados con exito.\n");
            pausar();
            break;
        case 2:
            if (datosInicializados)
            {
                mostrarProductos();
            }
            else
            {
                printf("\nPrimero debe inicializar los datos.\n");
            }
            pausar();
            break;
        case 3:
            if (datosInicializados)
            {
                registrarVenta();
            }
            else
            {
                printf("\nPrimero debe inicializar los datos.\n");
            }
            pausar();
            break;
        case 4:
            if (datosInicializados)
            {
                mostrarClientes();
            }
            else
            {
                printf("\nPrimero debe inicializar los datos.\n");
            }
            pausar();
            break;
        case 5:
            if (datosInicializados)
            {
                mostrarVentas();
            }
            else
            {
                printf("\nPrimero debe inicializar los datos.\n");
            }
            pausar();
            break;
        case 6:
            if (datosInicializados)
            {
                mostrarEstadisticas();
            }
            else
            {
                printf("\nPrimero debe inicializar los datos.\n");
            }
            pausar();
            break;
        case 7:
            printf("Saliendo del sistema...\n");
            break;
        default:
            printf("Opcion no valida. Por favor, intente de nuevo.\n");
            pausar();
        }
    } while (opcion != 7);

    return 0;
}
