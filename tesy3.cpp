// 1. Zona para las librerías 
#include<iostream>
#include<string.h>
#include<conio.h>
#include<locale.h>

using namespace std;

// 2. Definir estructuras

struct Cliente {
    string cedula;
    string nombre;
    string telefono;
    string email;
    Cliente* sgt;
    Cliente* ant;
};

struct Habitacion {
    int numero;
    string descripcion;
    float precioBase;
    bool vistaAlMar;
    int camas;  // Solo para habitaciones múltiples
    Habitacion* sgt;
    Habitacion* ant;
};

struct Reservacion {
    string descripcionHabitacion;
    string fechaInicio;
    string fechaSalida;
    Cliente cliente;
    string temporada;
    float precioTotal;
    Reservacion* sgt;
    Reservacion* ant;
};

// 3. Declarar funciones
int menu();
void fun_operaciones(int op, Habitacion *&pcabHabit, Habitacion *&pfinHabit, Cliente *&pcabCli, Cliente *&pfinCli, Reservacion *&pcabRes, Reservacion *&pfinRes);
void fun_ingresarHabitacion(Habitacion *&pcab, Habitacion *&pfin);
void fun_modificarHabitacion(Habitacion *&pcab);
void fun_eliminarHabitacion(Habitacion *&pcab, Habitacion *&pfin);
void fun_visualizarHabitaciones(Habitacion *pcab);
void fun_reservarHabitacion(Habitacion *pcab, Reservacion *&pcabRes, Reservacion *&pfinRes, Cliente *pcabCli);
float calcularPrecioTotal(Habitacion *hab, string temporada, int dias);

// 4. Zona del programa principal
int main() {
    setlocale(LC_CTYPE, "Spanish");

    Habitacion *pcabHabit = NULL;  
    Habitacion *pfinHabit = NULL;  
    Cliente *pcabCli = NULL;
    Cliente *pfinCli = NULL;  
    Reservacion *pcabRes = NULL;  
    Reservacion *pfinRes = NULL;

    int op;
    do {
        op = menu();            
        fun_operaciones(op, pcabHabit, pfinHabit, pcabCli, pfinCli, pcabRes, pfinRes);
        cout << "\nSi desea repetir el proceso Si(1), No(0)";
        cin >> op;     
    } while (op == 1);    
    getch();
    return 0;
}

// 5. Implementación de funciones

int menu() {
    int op;
    do {
        cout << "***** GESTIÓN DE HOTEL *****" << endl; 
        cout << "1: Ingresar Habitación" << endl;
        cout << "2: Modificar Habitación" << endl;
        cout << "3: Eliminar Habitación" << endl;
        cout << "4: Visualizar Habitaciones" << endl;
        cout << "5: Reservar Habitación" << endl;
        cout << "Elija una operación" << endl;
        cin >> op;
    } while (op < 1 || op > 5);
    return op;
}

void fun_operaciones(int op, Habitacion *&pcabHabit, Habitacion *&pfinHabit, Cliente *&pcabCli, Cliente *&pfinCli, Reservacion *&pcabRes, Reservacion *&pfinRes) {
    switch (op) {
        case 1:
            fun_ingresarHabitacion(pcabHabit, pfinHabit);
            break;
        case 2:
            fun_modificarHabitacion(pcabHabit);
            break;
        case 3:
            fun_eliminarHabitacion(pcabHabit, pfinHabit);
            break;
        case 4:
            fun_visualizarHabitaciones(pcabHabit);
            break;
        case 5:
            fun_reservarHabitacion(pcabHabit, pcabRes, pfinRes, pcabCli);
            break;
        default:
            cout << "Opción no válida " << endl;
    }
}

// Función para ingresar habitación
void fun_ingresarHabitacion(Habitacion *&pcab, Habitacion *&pfin) {
    Habitacion *nueva = new Habitacion();
    int multiple;
    cout << "Ingrese el número de habitación: ";
    cin >> nueva->numero;
    cin.ignore();
    
    cout << "Ingrese la descripción de la habitación: ";
    getline(cin, nueva->descripcion);
    
    cout << "Ingrese el precio base: ";
    cin >> nueva->precioBase;
    
    cout << "¿Tiene vista al mar? (1: Sí, 0: No): ";
    cin >> nueva->vistaAlMar;
    
    cout << "¿Es una habitación múltiple? (1: Sí, 0: No): ";
    cin >> multiple;
    
    if (multiple == 1) {
        cout << "Ingrese la cantidad de camas: ";
        cin >> nueva->camas;
    } else {
        nueva->camas = 1;  // Si no es múltiple, solo 1 cama.
    }
    
    nueva->sgt = NULL;
    nueva->ant = pfin;

    if (pcab == NULL) {
        pcab = nueva;
        pfin = nueva;
    } else {
        pfin->sgt = nueva;
        pfin = nueva;
    }
}

// Función para modificar una habitación
void fun_modificarHabitacion(Habitacion *&pcab) {
    int numero;
    cout << "Ingrese el número de la habitación a modificar: ";
    cin >> numero;

    Habitacion *actual = pcab;
    while (actual != NULL) {
        if (actual->numero == numero) {
            cout << "Ingrese la nueva descripción: ";
            cin.ignore();
            getline(cin, actual->descripcion);

            cout << "Ingrese el nuevo precio base: ";
            cin >> actual->precioBase;

            cout << "¿Tiene vista al mar? (1: Sí, 0: No): ";
            cin >> actual->vistaAlMar;

            cout << "¿Es una habitación múltiple? (1: Sí, 0: No): ";
            int multiple;
            cin >> multiple;
            if (multiple == 1) {
                cout << "Ingrese la cantidad de camas: ";
                cin >> actual->camas;
            } else {
                actual->camas = 1;  // Si no es múltiple, solo 1 cama.
            }
            cout << "Habitación modificada exitosamente." << endl;
            return;
        }
        actual = actual->sgt;
    }
    cout << "Habitación no encontrada." << endl;
}

// Función para eliminar una habitación
void fun_eliminarHabitacion(Habitacion *&pcab, Habitacion *&pfin) {
    int numero;
    cout << "Ingrese el número de la habitación a eliminar: ";
    cin >> numero;

    Habitacion *actual = pcab;
    Habitacion *anterior = NULL;

    while (actual != NULL) {
        if (actual->numero == numero) {
            if (anterior == NULL) {  // Es la primera habitación
                pcab = actual->sgt;
                if (pcab != NULL) {
                    pcab->ant = NULL;
                } else {
                    pfin = NULL;  // Lista vacía
                }
            } else {
                anterior->sgt = actual->sgt;
                if (actual->sgt != NULL) {
                    actual->sgt->ant = anterior;
                } else {
                    pfin = anterior;
                }
            }
            delete actual;
            cout << "Habitación eliminada exitosamente." << endl;
            return;
        }
        anterior = actual;
        actual = actual->sgt;
    }
    cout << "Habitación no encontrada." << endl;
}

// Función para visualizar habitaciones
void fun_visualizarHabitaciones(Habitacion *pcab) {
    Habitacion *actual = pcab;
    while (actual != NULL) {
        cout << "\nNúmero: " << actual->numero;
        cout << "\nDescripción: " << actual->descripcion;
        cout << "\nPrecio base: " << actual->precioBase;
        cout << "\nVista al mar: " << (actual->vistaAlMar ? "Sí" : "No");
        cout << "\nCamas: " << actual->camas << endl;
        actual = actual->sgt;
    }
}

// Función para calcular el precio total
float calcularPrecioTotal(Habitacion *hab, string temporada, int dias) {
    float tasaTemporada;
    
    if (temporada == "alta") {
        tasaTemporada = 0.15;
    } else if (temporada == "media") {
        tasaTemporada = 0.10;
    } else {
        tasaTemporada = 0.0;
    }

    float precio = hab->precioBase * dias;
    float tasa = precio * tasaTemporada;
    float iva = precio * 0.15;
    
    return precio + tasa + iva;
}

// Función para realizar una reservación
void fun_reservarHabitacion(Habitacion *pcab, Reservacion *&pcabRes, Reservacion *&pfinRes, Cliente *pcabCli) {
    int numeroHabitacion, dias;
    string temporada;
    
    cout << "Ingrese el número de la habitación que desea reservar: ";
    cin >> numeroHabitacion;

    Habitacion *habitacionSeleccionada = pcab;
    while (habitacionSeleccionada != NULL) {
        if (habitacionSeleccionada->numero == numeroHabitacion) {
            break;
        }
        habitacionSeleccionada = habitacionSeleccionada->sgt;
    }

    if (habitacionSeleccionada == NULL) {
        cout << "Habitación no encontrada." << endl;
        return;
    }

    Reservacion *nuevaRes = new Reservacion();
    
    nuevaRes->descripcionHabitacion = habitacionSeleccionada->descripcion;
    
    cout << "Ingrese la fecha de inicio (DD/MM/YYYY): ";
    cin.ignore();
    getline(cin, nuevaRes->fechaInicio);
    
    cout << "Ingrese la fecha de salida (DD/MM/YYYY): ";
    getline(cin, nuevaRes->fechaSalida);

    cout << "Ingrese el nombre del cliente: ";
    getline(cin, nuevaRes->cliente.nombre);
    
    cout << "Ingrese la cédula/RUC del cliente: ";
    getline(cin, nuevaRes->cliente.cedula);
    
    cout << "Ingrese el teléfono del cliente: ";
    getline(cin, nuevaRes->cliente.telefono);
    
    cout << "Ingrese el email del cliente: ";
    getline(cin, nuevaRes->cliente.email);

    cout << "Ingrese el tipo de temporada (alta, media, baja): ";
    getline(cin, temporada);

    cout << "Ingrese la cantidad de días de estadía: ";
    cin >> dias;
    
    nuevaRes->precioTotal = calcularPrecioTotal(habitacionSeleccionada, temporada, dias);
    
    nuevaRes->sgt = NULL;
    nuevaRes->ant = pfinRes;

    if (pcabRes == NULL) {
        pcabRes = nuevaRes;
        pfinRes = nuevaRes;
    } else {
        pfinRes->sgt = nuevaRes;
        pfinRes = nuevaRes;
    }

    cout << "Reservación realizada exitosamente. Precio total: $" << nuevaRes->precioTotal << endl;
}
