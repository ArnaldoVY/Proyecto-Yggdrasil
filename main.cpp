#include "funciones.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

int main() {
    presentacion();
    cout << "\nPresione ENTER para continuar...";
    cin.get();
    clearscreen();
    Operativo* Neon = nullptr;
    Operativo* OMEGA = nullptr;
    int opcion;

    do {
        clearscreen();
        cout << "\n=============================================" << endl;
        cout << "   YGGDRASIL - CENTRO DE MANDO  " << endl;
        cout << "=============================================" << endl;
        cout << "1. Gestion del Arbol B-4 (Insertar Operativo)" << endl;
        cout << "2. Extirpacion Manual (Eliminar por ID)" << endl;
        cout << "3. Mostrar Operativos por Equipo" << endl;
        cout << "4. Buscar Operativo por ID" << endl;
        cout << "5. Auditoria Visual (Imprimir Estructura)" << endl;
        cout << "6. Desconectar del Nucleo (Salir)" << endl;

        cout << "=============================================" << endl;
        cout << "Seleccione un comando: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int ID, BandoNO, HP;
                cout << "\n[Función Insertar Operativo] " << endl;
                cout << "Ingrese ID del Operativo: ";
                cin >> ID;
                cout << "Ingrese Bando del Operativo (1 para Neon, 2 para OMEGA): " << endl;
                cin >> BandoNO;

                HP = 100;

                insertarOperativo(Neon, OMEGA, ID, BandoNO, HP);
                break;
            }
            case 2:
                eliminarOperativo(Neon, OMEGA);
                break;
            case 3:
                mostrarOperativos(Neon, OMEGA);
                break;
            case 4: {
                int ID;
                cout << "\nIngrese el ID del operativo a buscar: ";
                cin >> ID;
                buscar(Neon, OMEGA, ID);
                break;
            }
            case 5:
                auditoriaVisual(Neon, OMEGA);
                break;
            case 6:
                cout << "\nDesconectando del Nucleo de Yggdrasil. Fin de la transmision." << endl;
                break;
            default:
                cout << "\n[ERROR] Comando no reconocido. Intente de nuevo." << endl;
        }

        if (opcion != 6) {
            cout << "\nPresione ENTER para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }

    } while (opcion != 6);

    return 0;
}