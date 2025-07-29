/*2. Registro de Ventas Diarias (`ventas.cpp`)

 - Permitir cargar hasta **1000 ventas por día**.
 - Debe cargar la fecha en formato `AAAAMMDD`.
 - Cada venta debe registrar:
 - Código de vendedor
 - Código de producto
 - Monto de la venta
 - Guardar todas las ventas en `ventas_diarias.dat`.

 ✅ **Tip**: Validar que el vendedor exista al momento de registrar la venta.*/

#include <iostream>
#include <cstdio>
using namespace std;

const int MAX_VENTAS = 1000;
const int MAX_VENDEDORES = 100;

struct Vendedor {
	int codigo_Vendedor;
	char nombre_Vendedor[26];
	char nombre_Sucursal[31];
};
struct Venta {
	int fecha;
	int codigo_Vendedor;
	int codigo_Producto;
	float monto;
};
void cargarVendedores(Vendedor vec[],int& len) {
	FILE *arch = fopen("Vendedores.dat", "rb");
	if (!arch) {
		len = 0;
		return;
	}
	len = 0;
	while (fread(&vec[len], sizeof(Vendedor), 1, arch) && len < MAX_VENDEDORES) {
		len++;
	}
	fclose(arch);
}
void guardarTodoEnArchivo(Venta ventas[], int lenVentas) {
	FILE *arch = fopen("ventas_diarias.dat", "ab");
	if (!arch) {
		cout << "Error al abrir el archivo de ventas para guardar." << endl;
		return;
	}
	fwrite(ventas, sizeof(Venta), lenVentas, arch);
	fclose(arch);
	cout << "\nVentas registradas con exito." << endl;
}
bool vendedorExiste(int codigo, Vendedor vec[], int len) {
	for (int i = 0; i < len; i++) {
		if (vec[i].codigo_Vendedor == codigo)
			return true;
	}
	return false;
}
void cargarVentas() {
	Venta ventas[MAX_VENTAS];
	int lenVentas = 0;
	Vendedor vendedores[MAX_VENDEDORES];
	int lenVendedores = 0;
	cargarVendedores(vendedores, lenVendedores);
	if (lenVendedores == 0) {
		cout << "No hay vendedores registrados. No se puede cargar ventas."
				<< endl;
		return;
	}
	char seguir;
	do {
		if (lenVentas >= MAX_VENTAS) {
			cout << "Se alcanzo el limite maximo de ventas diarias." << endl;
			break;
		}
		Venta nueva;
		cout << "Ingrese fecha de la venta (AAAAMMDD): ";
		cin >> nueva.fecha;
		cout << "Ingrese codigo del vendedor: ";
		cin >> nueva.codigo_Vendedor;
		if (!vendedorExiste(nueva.codigo_Vendedor, vendedores, lenVendedores)) {
			cout << "Error: el codigo de vendedor no existe." << endl;
			continue;
		}
		cout << "Ingrese codigo del producto: ";
		cin >> nueva.codigo_Producto;
		cout << "Ingrese monto de la venta: ";
		cin >> nueva.monto;
		ventas[lenVentas++] = nueva;
		cout << "¿Desea ingresar otra venta? (s/n): ";
		cin >> seguir;
		cin.ignore();
	} while (seguir == 's' || seguir == 'S');
	guardarTodoEnArchivo(ventas, lenVentas);
}
void mostrarVentas() {
	FILE *arch = fopen("ventas_diarias.dat", "rb");
	if (!arch) {
		cout << "Archivo de ventas vacio o no encontrado." << endl;
		return;
	}
	Venta v;
	cout << "\nVentas registradas:\n";
	while (fread(&v, sizeof(Venta), 1, arch)) {
		cout << "Fecha: " << v.fecha << endl;
		cout << "Vendedor: " << v.codigo_Vendedor << endl;
		cout << "Producto: " << v.codigo_Producto << endl;
		cout << "Monto: $" << v.monto << endl;
		cout << "-----------------------------" << endl;
	}
	fclose(arch);
}
/*int main() {
	cargarVentas();
	mostrarVentas();
	return 0;
}*/
