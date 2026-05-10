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
        cout << "1. Gestion de Operativos (Insertar)" << endl;
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
                clearscreen();
                int BandoNO;
                cout << "\n[Funcion Insertar Operativo] " << endl;
                cout << "Ingrese Bando del Operativo (1 para Neon, 2 para OMEGA): " << endl;
                cin >> BandoNO;

                insertarOperativo(Neon, OMEGA, BandoNO);
                break;
            }
            case 2: {
                clearscreen();
                eliminarOperativo(Neon, OMEGA);
                break;
            }
            case 3: {
                clearscreen();
                mostrarOperativos(Neon, OMEGA);
                break;
            }
            case 4: {
                clearscreen();
                int ID;
                cout << "Ingrese el ID del operativo a buscar: ";
                cin >> ID;
                buscar(Neon, OMEGA, ID);
                break;
            }
            case 5: {
                clearscreen();
                auditoriaVisual(Neon, OMEGA);
                break;
            }
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

    liberarOperativos(Neon);
    liberarOperativos(OMEGA);

    return 0;
}

