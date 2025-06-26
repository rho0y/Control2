#include "funciones.h"
#include <stdio.h>
#include <string.h>

Cliente clientesGlobal[100];
int totalClientesGlobal = 0;

void guardarProductos(Producto productos[], int cantidad)
{
    FILE *f = fopen("productos.data", "wb");
    if (f == NULL)
    {
        printf("Error al abrir productos.data\n");
        return;
    }
    fwrite(productos, sizeof(Producto), cantidad, f);
    fclose(f);
}

void guardarClientes(Cliente clientes[], int cantidad)
{
    FILE *f = fopen("clientes.data", "wb");
    if (f == NULL)
    {
        printf("Error al abrir clientes.data\n");
        return;
    }
    fwrite(clientes, sizeof(Cliente), cantidad, f);
    fclose(f);
}

void guardarVentas(Venta ventas[], int cantidad)
{
    FILE *f = fopen("ventas.data", "wb");
    if (f == NULL)
    {
        printf("Error al abrir ventas.data\n");
        return;
    }
    fwrite(ventas, sizeof(Venta), cantidad, f);
    fclose(f);
}

void guardarProductosVendidos(ProductoVendido productos[], int cantidad)
{
    FILE *f = fopen("productosVendidos.data", "wb");
    if (f == NULL)
    {
        printf("Error al abrir productosVendidos.data\n");
        return;
    }
    fwrite(productos, sizeof(ProductoVendido), cantidad, f);
    fclose(f);
}

void mostrarProductos()
{
    FILE *f = fopen("productos.data", "rb");
    if (f == NULL)
    {
        printf("No se pudo abrir productos.data. Inicializaste los datos?\n");
        return;
    }

    Producto p;
    printf("\n+---------------------------------------------+\n");
    printf("|           CATALOGO DE PRODUCTOS            |\n");
    printf("+-----+-------------------------+-------+-----+\n");
    printf("| %-3s | %-23s | %-5s | %-3s |\n", "ID", "Producto", "Precio", "Stock");
    printf("+-----+-------------------------+-------+-----+\n");

    int id = 1;
    while (fread(&p, sizeof(Producto), 1, f) == 1)
    {
        printf("| %-3d | %-23s | $%-5.2f | %-3d |\n", id++, p.nombre, p.precio, p.stock);
    }

    printf("+-----+-------------------------+-------+-----+\n");
    fclose(f);
}

void mostrarClientes()
{
    FILE *f = fopen("clientes.data", "rb");
    if (f == NULL)
    {
        printf("No se pudo abrir clientes.data. Inicializaste los datos?\n");
        return;
    }

    Cliente c;
    printf("\n+-------------------------------------------------------+\n");
    printf("|                 REGISTRO DE CLIENTES                 |\n");
    printf("+----------------+--------------------+--------+--------+\n");
    printf("| %-14s | %-18s | %-6s | %-6s |\n", "Cedula", "Nombre", "Compras", "Total");
    printf("+----------------+--------------------+--------+--------+\n");

    while (fread(&c, sizeof(Cliente), 1, f) == 1)
    {
        printf("| %-14s | %-18s | %-6d | $%-6.2f |\n", c.cedula, c.nombre, c.compras, c.total);
    }

    printf("+----------------+--------------------+--------+--------+\n");
    fclose(f);
}

void mostrarVentas()
{
    FILE *f = fopen("ventas.data", "rb");
    if (f == NULL)
    {
        printf("No se pudo abrir ventas.data. Inicializaste los datos?\n");
        return;
    }

    Venta v;
    printf("\n+---------------------------------------------------------------+\n");
    printf("|                    REGISTRO DE VENTAS                       |\n");
    printf("+--------------------+-------------------------+----+---------+\n");
    printf("| %-18s | %-23s | %-2s | %-7s |\n", "Cliente", "Producto", "Cant", "Total");
    printf("+--------------------+-------------------------+----+---------+\n");

    while (fread(&v, sizeof(Venta), 1, f) == 1)
    {
        printf("| %-18s | %-23s | %-2d | $%-6.2f |\n", v.nombreCliente, v.nombreProducto, v.cantidad, v.total);
    }

    printf("+--------------------+-------------------------+----+---------+\n");
    fclose(f);
}

void mostrarEstadisticas()
{
    FILE *f = fopen("productosVendidos.data", "rb");
    if (f == NULL)
    {
        printf("No se pudo abrir productosVendidos.data. Inicializaste los datos?\n");
        return;
    }

    ProductoVendido pv;
    printf("\n+------------------------------------------------+\n");
    printf("|          ESTADISTICAS DE PRODUCTOS           |\n");
    printf("+-------------------------+--------+------------+\n");
    printf("| %-23s | %-6s | %-10s |\n", "Producto", "Vendidos", "Total ($)");
    printf("+-------------------------+--------+------------+\n");

    while (fread(&pv, sizeof(ProductoVendido), 1, f) == 1)
    {
        printf("| %-23s | %-6d | $%-9.2f |\n", pv.nombreProducto, pv.cantidad, pv.total);
    }

    printf("+-------------------------+--------+------------+\n");
    fclose(f);
}

void inicializarProductos(Producto productos[])
{
    strcpy(productos[0].nombre, "Radiador");
    productos[0].precio = 200.0;
    productos[0].stock = 20;

    strcpy(productos[1].nombre, "Manzana para la rueda");
    productos[1].precio = 30.0;
    productos[1].stock = 50;

    strcpy(productos[2].nombre, "Escape");
    productos[2].precio = 100.0;
    productos[2].stock = 15;

    strcpy(productos[3].nombre, "Filtro de Aceite");
    productos[3].precio = 35.0;
    productos[3].stock = 100;

    strcpy(productos[4].nombre, "Bujias de encendido");
    productos[4].precio = 45.0;
    productos[4].stock = 80;
}

void inicializarDatos()
{
    Producto productos[5];
    inicializarProductos(productos);
    guardarProductos(productos, 5);

    Cliente clientes[1];
    guardarClientes(clientes, 0);

    Venta ventas[1];
    guardarVentas(ventas, 0);

    ProductoVendido productosVendidos[1];
    guardarProductosVendidos(productosVendidos, 0);

    totalClientesGlobal = 0;
}

int esCedulaValida(const char *cedula)
{
    int len = strlen(cedula);
    if (len < 5 || len > 15)
        return 0;
    for (int i = 0; i < len; i++)
    {
        if (cedula[i] < '0' || cedula[i] > '9')
            return 0;
    }
    return 1;
}

int esNombreValido(const char *nombre)
{
    int len = strlen(nombre);
    if (len < 2 || len > 50)
        return 0;
    for (int i = 0; i < len; i++)
    {
        if (!((nombre[i] >= 'A' && nombre[i] <= 'Z') ||
              (nombre[i] >= 'a' && nombre[i] <= 'z') ||
              nombre[i] == ' '))
            return 0;
    }
    return 1;
}

int buscarCliente(const char *cedula)
{
    FILE *f = fopen("clientes.data", "rb");
    if (f == NULL)
        return -1;

    Cliente c;
    int indice = 0;
    while (fread(&c, sizeof(Cliente), 1, f) == 1)
    {
        if (strcmp(c.cedula, cedula) == 0)
        {
            fclose(f);
            return indice;
        }
        indice++;
    }
    fclose(f);
    return -1;
}

void registrarVenta()
{
    char cedula[20], nombre[50];
    int producto, cantidad;

    printf("\nIngrese la cedula del cliente: ");
    scanf("%s", cedula);

    if (!esCedulaValida(cedula))
    {
        printf("Cedula invalida.\n");
        return;
    }

    int indiceCliente = buscarCliente(cedula);
    Cliente cliente;

    if (indiceCliente == -1)
    {
        printf("Cliente nuevo. Ingrese el nombre: ");
        while (getchar() != '\n')
            ;
        fgets(nombre, sizeof(nombre), stdin);
        nombre[strcspn(nombre, "\n")] = 0;

        if (!esNombreValido(nombre))
        {
            printf("Nombre invalido.\n");
            return;
        }

        strcpy(cliente.cedula, cedula);
        strcpy(cliente.nombre, nombre);
        cliente.compras = 0;
        cliente.total = 0;
    }
    else
    {
        FILE *fclientes = fopen("clientes.data", "rb");
        fseek(fclientes, indiceCliente * sizeof(Cliente), SEEK_SET);
        fread(&cliente, sizeof(Cliente), 1, fclientes);
        fclose(fclientes);
        strcpy(nombre, cliente.nombre);
    }

    mostrarProductos();

    int numProductos;
    while (1)
    {
        printf("\n¿Cuantos productos diferentes desea comprar? (maximo 5): ");
        if (scanf("%d", &numProductos) == 1 && numProductos >= 1 && numProductos <= 5)
        {
            break;
        }
        printf("Numero invalido. Ingrese un valor entre 1 y 5.\n");
        while (getchar() != '\n')
            ;
    }

    float totalGeneral = 0;
    Producto productos[5];
    int cantidades[5];
    int indices[5];

    // Cargar todos los productos desde el archivo
    FILE *fproductos = fopen("productos.data", "rb+");
    if (fproductos == NULL)
    {
        printf("Error al abrir productos.data\n");
        return;
    }

    for (int i = 0; i < 5; i++)
    {
        fread(&productos[i], sizeof(Producto), 1, fproductos);
    }

    // Solicitar índice y cantidad para cada producto
    for (int i = 0; i < numProductos; i++)
    {
        printf("\n--- Producto %d ---\n", i + 1);
        
        while (1)
        {
            printf("Seleccione el numero del producto (1-5): ");
            if (scanf("%d", &producto) == 1 && producto >= 1 && producto <= 5)
            {
                indices[i] = producto - 1;
                break;
            }
            printf("Opcion invalida. Vuelva a intentarlo.\n");
            while (getchar() != '\n')
                ;
        }

        while (1)
        {
            printf("Ingrese la cantidad para %s: ", productos[indices[i]].nombre);
            if (scanf("%d", &cantidad) == 1 && cantidad > 0)
            {
                if (productos[indices[i]].stock >= cantidad)
                {
                    cantidades[i] = cantidad;
                    break;
                }
                else
                {
                    printf("Stock insuficiente. Solo hay %d unidades disponibles. Vuelva a intentarlo.\n", productos[indices[i]].stock);
                }
            }
            else
            {
                printf("Cantidad invalida. Vuelva a intentarlo.\n");
                while (getchar() != '\n')
                    ;
            }
        }

        // Actualizar stock temporalmente para evitar conflictos
        productos[indices[i]].stock -= cantidades[i];
        totalGeneral += productos[indices[i]].precio * cantidades[i];
    }

    // Escribir todos los productos actualizados al archivo
    fseek(fproductos, 0, SEEK_SET);
    for (int i = 0; i < 5; i++)
    {
        fwrite(&productos[i], sizeof(Producto), 1, fproductos);
    }
    fclose(fproductos);

    float total = totalGeneral;

    cliente.compras++;
    cliente.total += total;

    FILE *fclientes = fopen("clientes.data", "rb");
    if (fclientes == NULL)
    {
        Cliente clientesArray[1];
        clientesArray[0] = cliente;
        guardarClientes(clientesArray, 1);
    }
    else
    {
        Cliente clientesArray[100];
        int numClientes = 0;

        while (fread(&clientesArray[numClientes], sizeof(Cliente), 1, fclientes) == 1)
        {
            numClientes++;
        }
        fclose(fclientes);

        if (indiceCliente == -1)
        {
            clientesArray[numClientes] = cliente;
            numClientes++;
        }
        else
        {
            clientesArray[indiceCliente] = cliente;
        }

        guardarClientes(clientesArray, numClientes);
    }

    // Registrar cada venta individual
    for (int i = 0; i < numProductos; i++)
    {
        Venta nuevaVenta;
        strcpy(nuevaVenta.nombreProducto, productos[indices[i]].nombre);
        strcpy(nuevaVenta.cedulaCliente, cedula);
        strcpy(nuevaVenta.nombreCliente, nombre);
        nuevaVenta.cantidad = cantidades[i];
        nuevaVenta.total = productos[indices[i]].precio * cantidades[i];

        FILE *fventas = fopen("ventas.data", "rb");
        if (fventas == NULL)
        {
            Venta ventasArray[1];
            ventasArray[0] = nuevaVenta;
            guardarVentas(ventasArray, 1);
        }
        else
        {
            Venta ventasArray[100];
            int numVentas = 0;

            while (fread(&ventasArray[numVentas], sizeof(Venta), 1, fventas) == 1)
            {
                numVentas++;
            }
            fclose(fventas);

            ventasArray[numVentas] = nuevaVenta;
            numVentas++;

            guardarVentas(ventasArray, numVentas);
        }

        // Actualizar productos vendidos
        FILE *fpv = fopen("productosVendidos.data", "rb");
        if (fpv == NULL)
        {
            ProductoVendido pvArray[1];
            strcpy(pvArray[0].nombreProducto, productos[indices[i]].nombre);
            pvArray[0].cantidad = cantidades[i];
            pvArray[0].total = productos[indices[i]].precio * cantidades[i];
            guardarProductosVendidos(pvArray, 1);
        }
        else
        {
            ProductoVendido pvArray[100];
            int numPV = 0;
            int encontrado = 0;

            while (fread(&pvArray[numPV], sizeof(ProductoVendido), 1, fpv) == 1)
            {
                if (strcmp(pvArray[numPV].nombreProducto, productos[indices[i]].nombre) == 0)
                {
                    pvArray[numPV].cantidad += cantidades[i];
                    pvArray[numPV].total += productos[indices[i]].precio * cantidades[i];
                    encontrado = 1;
                }
                numPV++;
            }
            fclose(fpv);

            if (!encontrado)
            {
                strcpy(pvArray[numPV].nombreProducto, productos[indices[i]].nombre);
                pvArray[numPV].cantidad = cantidades[i];
                pvArray[numPV].total = productos[indices[i]].precio * cantidades[i];
                numPV++;
            }

            guardarProductosVendidos(pvArray, numPV);
        }
    }

    printf("\nVenta registrada con exito!\n");
    printf("Cliente: %s\n", nombre);
    printf("Productos comprados:\n");
    for (int i = 0; i < numProductos; i++)
    {
        printf("- %s: %d unidades ($%.2f)\n", productos[indices[i]].nombre, cantidades[i], productos[indices[i]].precio * cantidades[i]);
    }
    printf("Total general: $%.2f\n", total);
}

void pausar()
{
    printf("\nPresione Enter para continuar...");
    while (getchar() != '\n')
        ;
    getchar();
}
