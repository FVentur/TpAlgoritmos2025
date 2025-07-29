/*### 3. Análisis de Ventas (`analisis.cpp`)

 Desde el archivo `ventas_diarias.dat`, y el `vendedores.dat` el sistema debe:

 - Determinar **el vendedor que más dinero generó** (mostrar su nombre y monto total).
 - Determinar **la sucursal que más dinero generó** (sumando las ventas de todos los vendedores de esa sucursal).
 - Mostrar **un ranking de los productos más vendidos** (por cantidad de veces que se vendió cada código de producto).

 ✅ **Tip**:

 - Agrupar ventas por vendedor y sucursal usando **corte de control** o acumulación.
 - Para ranking de productos, contar ocurrencias y luego ordenar.*/
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
struct mayorVenta {
	int codigo_Vendedor;
	float totalRecaudado;
};
void cargarVendedoress(Vendedor vec[],int& len){
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
void cargarVentas(Venta vec[], int &len) {
	FILE *archVentas = fopen("ventas_diarias.dat", "rb");
	if (!archVentas) {
		len = 0;
		return;
	}
	len = 0;
	while (fread(&vec[len], sizeof(Venta), 1, archVentas) && len < MAX_VENTAS) {
		len++;
	}
	fclose(archVentas);
}
void ordenarPorCodigoVendedor(Venta ventas[], int &lenVentas) {
	bool ordenado;
	for (int i = 0; i < lenVentas - 1; i++) {
		ordenado = false;
		for (int j = 0; j < lenVentas - i - 1; j++) {
			Venta Aux;
			if (ventas[j].codigo_Vendedor > ventas[j + 1].codigo_Vendedor) {
				Aux = ventas[j + 1];
				ventas[j + 1] = ventas[j];
				ventas[j] = Aux;
				ordenado = true;
			}
		}
		if (!ordenado) {
			break;
		}
	}

}
mayorVenta vendedorQueMasRecaudo(Venta ventas[], int &lenVentas) {
	mayorVenta MayorVen;
	int i = 0;
	while (i < lenVentas) {
		MayorVen.codigo_Vendedor = ventas[i].codigo_Vendedor;
		MayorVen.totalRecaudado = 0;
		int contador = 0;
		while (i < lenVentas
				&& MayorVen.codigo_Vendedor == ventas[i].codigo_Vendedor) {
			MayorVen.totalRecaudado += ventas[i].monto;
			contador++;
			i++;
		}

	}
	return MayorVen;
}
int buscarVendedor(Vendedor vendedor[], int lenVendedores,
		mayorVenta MayorVen) {
	int izquierda = 0;
	int derecha = lenVendedores - 1;
	while (izquierda <= derecha) {
		int medio = (izquierda + derecha) / 2;
		if (vendedor[medio].codigo_Vendedor == MayorVen.codigo_Vendedor) {
			return medio;
		} else if (vendedor[medio].codigo_Vendedor < MayorVen.codigo_Vendedor) {
			izquierda = medio + 1;
		} else {
			derecha = medio - 1;
		}
	}
	return -1;
}
void mostrarVendedor(Vendedor vendedor[], int pos,mayorVenta MayorVen){
	cout << "\n===== Vendedor que mas dinero genero fue =====\n";
    cout << "Nombre: " << vendedor[pos].nombre_Vendedor << endl;
    cout << "Total recaudado: " << MayorVen.totalRecaudado << endl;
    cout << "\n-----------------------------" << endl;
}
void vendedorQueMasVendio(Venta ventas[], int &lenVentas, Vendedor vendedor[], int &lenVendedores) {
	ordenarPorCodigoVendedor(ventas, lenVentas);
	mayorVenta MayorVen = vendedorQueMasRecaudo(ventas, lenVentas);
	int pos=buscarVendedor(vendedor, lenVendedores, MayorVen);
	mostrarVendedor(vendedor,pos,MayorVen);
}
void sucursalQueMasVendio(){


}
/*rankingProductos() {

}*/
int main() {
	Venta ventas[MAX_VENTAS];
	int lenVentas = 0;
	Vendedor vendedores[MAX_VENDEDORES];
	int lenVendedores = 0;
	cargarVentas(ventas, lenVentas);
	cargarVendedoress(vendedores, lenVendedores);
	int opcion;
	do {
		cout << "\n===== MENU DE ANALISIS DE VENTAS =====" << endl;
		cout << "1. Vendedor que mas dinero genero" << endl;
		cout << "2. Sucursal que mas dinero genero" << endl;
		cout << "3. Ranking de productos mas vendidos" << endl;
		cout << "0. Salir" << endl;
		cout << "Seleccione una opcion: ";
		cin >> opcion;
		switch (opcion) {
		case 1:
			vendedorQueMasVendio(ventas, lenVentas, vendedores, lenVendedores);
			break;
		/*case 2:
			sucursalQueMasVendio();
			break;
		case 3:
			rankingProductos();
			break;*/
		case 0:
			cout << "Saliendo del menu de analisis..." << endl;
			break;
		default:
			cout << "Opcion invalida. Intentelo de nuevo." << endl;
			break;
		}
	} while (opcion != 0);
	return 0;
}
