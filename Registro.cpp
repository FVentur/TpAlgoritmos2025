/*### 1. Registro de Vendedores y Sucursales (`registro.cpp`)

- Permitir cargar:
    - Código de vendedor (único)
    - Nombre del vendedor
    - Nombre de la sucursal
- Guardar todos los vendedores en el archivo `vendedores.dat`.

✅ **Tip**: Validar que no se repita el código de vendedor.*/
#include <iostream>
#include <cstring>
using namespace std;

const int MAX_VENDEDORES = 100;

struct Vendedor {
    int codigo_Vendedor;
    char nombre_Vendedor[26];
    char nombre_Sucursal[31];
};


void cargarDesdeArchivo(Vendedor vec[], int& len) {
    FILE* arch = fopen("Vendedores.dat", "rb"); //rb solo para lectura
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

bool existeCodigo(int codigo, Vendedor vec[], int len) {
    for (int i = 0; i < len; i++) {
        if (vec[i].codigo_Vendedor == codigo)
            return true;
    }
    return false;
}


Vendedor pedirDatos() {
    Vendedor v;
    string nombre, sucursal;

    cout << "Ingrese codigo del vendedor: ";
    cin >> v.codigo_Vendedor;
    cin.ignore();

    cout << "Ingrese nombre del vendedor: ";
    getline(cin, nombre);
    strcpy(v.nombre_Vendedor, nombre.c_str());

    cout << "Ingrese nombre de la sucursal: ";
    getline(cin, sucursal);
    strcpy(v.nombre_Sucursal, sucursal.c_str());

    return v;
}
void ordenar(Vendedor v[],int len){
	bool ordenado;
	for(int i=0;i<len-1;i++){
		ordenado=false;
		for(int j=0;j < len - i - 1;j++){
			Vendedor Aux;
			 if(v[j].codigo_Vendedor>v[j + 1].codigo_Vendedor){
				 Aux = v[j+1];
				 v[j+1]=v[j];
				 v[j]=Aux;
				 ordenado=true;
			 }
		}
		if (!ordenado) {
			break;
		}
	}

}

void guardarTodoEnArchivo(Vendedor vec[], int len) {
    FILE* arch = fopen("Vendedores.dat", "wb"); // "wb" sobreescribe
    if (!arch) {
        cout << "Error al abrir el archivo para guardar." << endl;
        return;
    }

    fwrite(vec, sizeof(Vendedor), len, arch);
    fclose(arch);
}

void mostrarArchivo() {
    FILE* arch = fopen("Vendedores.dat", "rb");
    if (!arch) {
        cout << "Archivo vacio o no encontrado." << endl;
        return;
    }

    Vendedor v;
    while (fread(&v, sizeof(Vendedor), 1, arch)) {
        cout << "Codigo: " << v.codigo_Vendedor << endl;
        cout << "Nombre: " << v.nombre_Vendedor << endl;
        cout << "Sucursal: " << v.nombre_Sucursal << endl;
        cout << "-----------------------------" << endl;
    }

    fclose(arch);
}

void cargarVendedores() {
    Vendedor lista[MAX_VENDEDORES];
    int len = 0;
    cargarDesdeArchivo(lista, len);
    char seguir;
    do {
        if (len >= MAX_VENDEDORES) {
            cout << "Se alcanzo el limite maximo de vendedores." << endl;
            break;
        }
        Vendedor nuevo = pedirDatos();
        if (existeCodigo(nuevo.codigo_Vendedor, lista, len)) {
            cout << "Error: ese codigo ya existe." << endl;
        } else {
            lista[len++] = nuevo;
            cout << "Vendedor registrado con exito." << endl;
        }
        cout << "¿Desea ingresar otro vendedor? (s/n): ";
        cin >> seguir;
        cin.ignore();
    } while (seguir == 's' || seguir == 'S');
    ordenar(lista, len);
    guardarTodoEnArchivo(lista, len);
}

/*int main() {
    cargarVendedores();
    cout << "\nVendedores registrados:\n";
    mostrarArchivo();
    return 0;
}*/
