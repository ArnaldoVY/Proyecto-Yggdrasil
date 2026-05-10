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
    "Escudo Fisico",
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
    cout << "Bienvenido a Yggdrasil, el juego de estrategia y defensa!" << endl;
    cout << "En este mundo, cada unidad tiene su propia pila de escudos y un arsenal de armas." << endl;
    cout << "Este proyecto usa listas enlazadas, pilas y colas." << endl;
    cout << "Integrantes del grupo:" << endl;
    cout << "- Ortega Vazquez, Saul A. (31191797)" << endl;
    cout << "- Palma Mata, Daniela L. (30459494)" << endl;
    cout << "- Velasquez Yanez, Arnaldo A. (30513998)" << endl;
}

void clearscreen() {
    system("cls");
}

void pushEscudo(NodoEscudo*& pila, Escudo nuevoEscudo) {
    NodoEscudo* nuevo = new NodoEscudo;
    nuevo->escudo = nuevoEscudo;
    nuevo->prox = pila;
    pila = nuevo;
}

void popEscudo(NodoEscudo*& pila) {
    if (pila != nullptr) {
        NodoEscudo* temp = pila;
        pila = pila->prox;
        delete temp;
    }
}

void agregarArma(NodoArma*& lista, Arma nuevaArma) {
    NodoArma* nuevo = new NodoArma;
    nuevo->arma = nuevaArma;
    nuevo->prox = nullptr;

    if (lista == nullptr) {
        lista = nuevo;
    } else {
        NodoArma* aux = lista;
        while (aux->prox != nullptr) {
            aux = aux->prox;
        }
        aux->prox = nuevo;
    }
}

void liberarPilaEscudos(NodoEscudo*& pila) {
    while (pila != nullptr) {
        popEscudo(pila);
    }
}

void liberarListaArmas(NodoArma*& lista) {
    while (lista != nullptr) {
        NodoArma* temp = lista;
        lista = lista->prox;
        delete temp;
    }
}

void liberarOperativos(Operativo*& head) {
    while (head != nullptr) {
        Operativo* temp = head;
        head = head->prox;
        liberarPilaEscudos(temp->pilaEscudos);
        liberarListaArmas(temp->listaArmas);
        delete temp;
    }
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
            liberarPilaEscudos(current->pilaEscudos);
            liberarListaArmas(current->listaArmas);
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

void insertarOperativo(Operativo*& Neon, Operativo*& OMEGA, int BandoNO) {
    int ID;
    cout << "Ingrese ID del Operativo: ";
    cin >> ID;

    if (existeOperativo(Neon, OMEGA, ID)) {
        cout << "Error: Ya existe un operativo con ID " << ID << ". No se puede insertar duplicado." << endl;
        return;
    }

    int opcClase;
    cout << "Seleccione la Clase del Operativo:" << endl;
    cout << "1. Juggernaut" << endl;
    cout << "2. Ejecutor" << endl;
    cout << "3. Espectro" << endl;
    cout << "Opcion: ";
    cin >> opcClase;

    ClasePersonaje claseSel;
    if (opcClase == 1) claseSel = Juggernaut;
    else if (opcClase == 2) claseSel = Ejecutor;
    else claseSel = Espectro;

    Operativo* newOperativo = new Operativo;
    newOperativo->Bando = BandoNO;
    newOperativo->ID_Clave = ID;
    newOperativo->vida.actual = claseSel.HP_Base;
    newOperativo->vida.maximo = claseSel.HP_Base;

    newOperativo->pilaEscudos = nullptr;
    newOperativo->listaArmas = nullptr;

    for (int i = 0; i < claseSel.escudos_iniciales; i++) {
        Escudo e = {claseSel.tipo_escudo, 50, 50};
        pushEscudo(newOperativo->pilaEscudos, e);
    }

    agregarArma(newOperativo->listaArmas, claseSel.arma_base);

    newOperativo->prox = nullptr;

    if (newOperativo->Bando == 1) {
        insertarOrdenadoAscendente(Neon, newOperativo);
        cout << "Bienvenido al equipo Neon (" << claseSel.nombre << ")" << endl;
    } else {
        insertarOrdenadoAscendente(OMEGA, newOperativo);
        cout << "Bienvenido al equipo OMEGA (" << claseSel.nombre << ")" << endl;
    }
    cout << "Operativo insertado con exito" << endl;
    
    int opc;
    cout << "Desea ingresar otro operativo?" << endl;
    cout << "1. Si" << endl;
    cout << "2. No" << endl;
    cin >> opc;
    if (opc == 1) {
        insertarOperativo(Neon, OMEGA, BandoNO);
    } else {
        cout << "Regresando al menu principal." << endl;
        clearscreen() ;
    }

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
        cout << endl;
    } else if (opc == 2) {
        cout << "\n[Equipo OMEGA]" << endl;
        aux = OMEGA;
        while (aux != nullptr) {
            cout << "ID: " << aux->ID_Clave << " -> ";
            aux = aux->prox;
        }
        cout << endl;
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
            int numEscudos = 0;
            NodoEscudo* tempE = aux->pilaEscudos;
            while(tempE != nullptr) { numEscudos++; tempE = tempE->prox; }
            
            cout << "    - Operativo ID " << aux->ID_Clave
                 << " [HP " << aux->vida.actual << "/" << aux->vida.maximo
                 << ", Escudos(Pila): " << numEscudos << "]" << endl;
            aux = aux->prox;
        }
        cout << endl;
    }

    cout << "  Lista: Equipo OMEGA" << endl;
    if (OMEGA == nullptr) {
        cout << "    (sin operativos)" << endl;
    } else {
        Operativo* aux = OMEGA;
        while (aux != nullptr) {
            int numEscudos = 0;
            NodoEscudo* tempE = aux->pilaEscudos;
            while(tempE != nullptr) { numEscudos++; tempE = tempE->prox; }

            cout << "    - Operativo ID " << aux->ID_Clave
                 << " [HP " << aux->vida.actual << "/" << aux->vida.maximo
                 << ", Escudos(Pila): " << numEscudos << "]" << endl;
            aux = aux->prox;
        }
        cout << endl;
    }
}

void buscar(Operativo*& Neon, Operativo*& OMEGA, int ID) {
    Operativo* aux = nullptr;
    bool encontrado = false;

    // Buscar en el equipo Neon
    aux = Neon;
    while (aux != nullptr) {
        if (aux->ID_Clave == ID) {
            int numEscudos = 0;
            NodoEscudo* tempE = aux->pilaEscudos;
            while(tempE != nullptr) { numEscudos++; tempE = tempE->prox; }
            cout << "Operativo encontrado en el equipo Neon: ID " << aux->ID_Clave 
                 << " [HP " << aux->vida.actual << "/" << aux->vida.maximo 
                 << ", Escudos: " << numEscudos << "]" << endl;
            encontrado = true;
            break;
        }
        aux = aux->prox;
    }

    // Si no se encontro en Neon, buscar en OMEGA
    if (!encontrado) {
        aux = OMEGA;
        while (aux != nullptr) {
            if (aux->ID_Clave == ID) {
                int numEscudos = 0;
                NodoEscudo* tempE = aux->pilaEscudos;
                while(tempE != nullptr) { numEscudos++; tempE = tempE->prox; }
                cout << "Operativo encontrado en el equipo OMEGA: ID " << aux->ID_Clave 
                     << " [HP " << aux->vida.actual << "/" << aux->vida.maximo 
                     << ", Escudos: " << numEscudos << "]" << endl;
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
