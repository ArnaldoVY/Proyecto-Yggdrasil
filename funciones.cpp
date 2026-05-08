#include "funciones.h"
#include <iostream>
#include <string>
#include <cstdlib> // Para system()

using namespace std;

// Definiciones de constantes
const ClasePersonaje Juggernaut = {
    "Juggernaut",
    150,
    {"Arma Base", 15},
    3,
    "Escudo Físico",
    false
};

const ClasePersonaje Ejecutor = {
    "Ejecutor",
    100,
    {"Arma Base", 30},
    1,
    "Escudo Anti-Plasma",
    false
};

const ClasePersonaje Espectro = {
    "Espectro",
    60,
    {"Arma Base", 10},
    0,
    "",
    true
};

// Implementaciones de funciones
void presentacion() {
    cout << "¡Bienvenido a Yggdrasil, el juego de estrategia y defensa!" << endl;
    cout << "En este mundo, cada unidad tiene su propia pila de escudos y un arsenal de armas." << endl;
    cout << "¡Preparate para defender tu base y atacar a tus enemigos!" << endl;
}

void clearscreen() {
    system("cls");
}

void insertarOrdenadoAscendente(Operativo*& head, Operativo* newOp) {
    if (head == nullptr || newOp->ID_Clave < head->ID_Clave) {
        newOp->prox = head;
        head = newOp;
        return;
    }
    Operativo* current = head;
    while (current->prox != nullptr && current->prox->ID_Clave < newOp->ID_Clave) {
        current = current->prox;
    }
    newOp->prox = current->prox;
    current->prox = newOp;
}

bool existeOperativoEnLista(Operativo* head, int ID) {
    Operativo* current = head;
    while (current != nullptr) {
        if (current->ID_Clave == ID) {
            return true;
        }
        current = current->prox;
    }
    return false;
}

bool existeOperativo(Operativo* Neon, Operativo* OMEGA, int ID) {
    return existeOperativoEnLista(Neon, ID) || existeOperativoEnLista(OMEGA, ID);
}

bool eliminarOperativoPorID(Operativo*& head, int ID) {
    Operativo* current = head;
    Operativo* prev = nullptr;

    while (current != nullptr) {
        if (current->ID_Clave == ID) {
            if (prev == nullptr) {
                head = current->prox;
            } else {
                prev->prox = current->prox;
            }
            delete current;
            return true;
        }
        prev = current;
        current = current->prox;
    }

    return false;
}

void eliminarOperativo(Operativo*& Neon, Operativo*& OMEGA) {
    int equipo;
    int ID;
    cout << "\n[Eliminar Operativo por ID]" << endl;
    cout << "Seleccione un equipo: 1. Neon, 2. OMEGA" << endl;
    cin >> equipo;
    cout << "Ingrese el ID del operativo a eliminar: ";
    cin >> ID;

    bool eliminado = false;
    if (equipo == 1) {
        eliminado = eliminarOperativoPorID(Neon, ID);
    } else if (equipo == 2) {
        eliminado = eliminarOperativoPorID(OMEGA, ID);
    } else {
        cout << "Equipo no valido. Operacion cancelada." << endl;
        return;
    }

    if (eliminado) {
        cout << "Operativo con ID " << ID << " eliminado exitosamente." << endl;
    } else {
        cout << "No se encontro ningun operativo con ID " << ID << " en el equipo seleccionado." << endl;
    }
}

void insertarOperativo(Operativo*& Neon, Operativo*& OMEGA, int ID, int BandoNO, int HP) {
    if (existeOperativo(Neon, OMEGA, ID)) {
        cout << "Error: Ya existe un operativo con ID " << ID << ". No se puede insertar duplicate." << endl;
        return;
    }

    Operativo* newOperativo = new Operativo;
    newOperativo->Bando = BandoNO;
    newOperativo->ID_Clave = ID;
    newOperativo->vida.actual = HP;
    newOperativo->vida.maximo = HP;
    newOperativo->escudo.tipo = "Escudo Base";
    newOperativo->escudo.actual = 50;
    newOperativo->escudo.maximo = 50;
    newOperativo->arma = {"Arma Base", 10};
    newOperativo->prox = nullptr;

    if (newOperativo->Bando == 1) {
        insertarOrdenadoAscendente(Neon, newOperativo);
        cout << "Bienvenido al equipo Neon" << endl;
    } else {
        insertarOrdenadoAscendente(OMEGA, newOperativo);
        cout << "Bienvenido al equipo OMEGA" << endl;
    }
    cout << "Operativo insertado con exito" << endl;
}

void mostrarOperativos(Operativo*& Neon, Operativo*& OMEGA) {
    Operativo* aux = nullptr;
    int opc;
    cout << "Seleccione un equipo para mostrar sus operativos:" << endl;
    cout << "1. Equipo Neon" << endl;
    cout << "2. Equipo OMEGA" << endl;
    cin >> opc;

    if (opc == 1) {
        cout << "\n[Equipo Neon]" << endl;
        aux = Neon;
        while (aux != nullptr) {
            cout << "ID: " << aux->ID_Clave << " -> ";
            aux = aux->prox;
        }
    } else if (opc == 2) {
        cout << "\n[Equipo OMEGA]" << endl;
        aux = OMEGA;
        while (aux != nullptr) {
            cout << "ID: " << aux->ID_Clave << " -> ";
            aux = aux->prox;
        }
    } else {
        cout << "Opcion no valida. Regresando al menu principal." << endl;
    }
}

void auditoriaVisual(Operativo*& Neon, Operativo*& OMEGA) {
    cout << "\n[Yggdrasil - Auditoria Visual]" << endl;
    cout << "Raiz: Yggdrasil" << endl;

    cout << "  Lista: Equipo Neon" << endl;
    if (Neon == nullptr) {
        cout << "    (sin operativos)" << endl;
    } else {
        Operativo* aux = Neon;
        while (aux != nullptr) {
            cout << "    - Operativo ID " << aux->ID_Clave
                 << " [HP " << aux->vida.actual << "/" << aux->vida.maximo
                 << ", Escudo " << aux->escudo.actual << "/" << aux->escudo.maximo << "]" << endl;
            aux = aux->prox;
        }
    }

    cout << "  Lista: Equipo OMEGA" << endl;
    if (OMEGA == nullptr) {
        cout << "    (sin operativos)" << endl;
    } else {
        Operativo* aux = OMEGA;
        while (aux != nullptr) {
            cout << "    - Operativo ID " << aux->ID_Clave
                 << " [HP " << aux->vida.actual << "/" << aux->vida.maximo
                 << ", Escudo " << aux->escudo.actual << "/" << aux->escudo.maximo << "]" << endl;
            aux = aux->prox;
        }
    }
}

void buscar(Operativo*& Neon, Operativo*& OMEGA, int ID) {
    Operativo* aux = nullptr;
    bool encontrado = false;

    // Buscar en el equipo Neon
    aux = Neon;
    while (aux != nullptr) {
        if (aux->ID_Clave == ID) {
            cout << "Operativo encontrado en el equipo Neon: ID " << aux->ID_Clave << endl;
            encontrado = true;
            break;
        }
        aux = aux->prox;
    }

    // Si no se encontró en Neon, buscar en OMEGA
    if (!encontrado) {
        aux = OMEGA;
        while (aux != nullptr) {
            if (aux->ID_Clave == ID) {
                cout << "Operativo encontrado en el equipo OMEGA: ID " << aux->ID_Clave << endl;
                encontrado = true;
                break;
            }
            aux = aux->prox;
        }
    }

    if (!encontrado) {
        cout << "Operativo con ID " << ID << " no encontrado en ninguno de los equipos." << endl;
    }
}