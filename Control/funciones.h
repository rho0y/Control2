typedef struct
{
    char nombre[50];
    float precio;
    int stock;
} Producto;

typedef struct
{
    char cedula[20];
    char nombre[50];
    int compras;
    float total;
} Cliente;

typedef struct
{
    char nombreProducto[50];
    char cedulaCliente[20];
    char nombreCliente[50];
    int cantidad;
    float total;
} Venta;

typedef struct
{
    char nombreProducto[50];
    int cantidad;
    float total;
} ProductoVendido;

void guardarProductos(Producto productos[], int cantidad);
void guardarClientes(Cliente clientes[], int cantidad);
void guardarVentas(Venta ventas[], int cantidad);
void guardarProductosVendidos(ProductoVendido productos[], int cantidad);

void mostrarProductos();
void mostrarClientes();
void mostrarVentas();
void mostrarEstadisticas();

void inicializarProductos(Producto productos[]);
void inicializarDatos();

int esCedulaValida(const char *cedula);
int esNombreValido(const char *nombre);
int buscarCliente(const char *cedula);

void registrarVenta();
void pausar();
