#include <iostream>
#include <string>

using namespace std;



//Parte 1 Gestion del arbol B-4
//Personajes y perfiles de equipamiento
struct Arma {
    string nombre;
    int dano;
};

struct Escudo {
    string tipo;
    int actual;
    int maximo;
};

struct Vida {
    int actual;
    int maximo;
};

struct ClasePersonaje {
    string nombre;
    int HP_Base;
    Arma arma_base;
    int escudos_iniciales;
    string tipo_escudo;
    bool control_mental;
};

struct Operativo {
    int ID_Clave;
    int Bando;
    Vida vida;
    Escudo escudo;
    Arma arma;
    Operativo* prox;
};

struct NodoBTree4 {
    Operativo* ocupantes[3];
    NodoBTree4* hijos[4];
    int cantidad_actual;
    bool hoja;
}; 

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

//Presentacion y limpieza de pantalla
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

void insertarOperativo(Operativo *&Neon,Operativo *&OMEGA,int ID, int BandoNO, int HP) {
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

    if(newOperativo->Bando == 1){
        insertarOrdenadoAscendente(Neon, newOperativo);
        cout << "Bienvenido al equipo Neon" << endl;
    }
    else {
        insertarOrdenadoAscendente(OMEGA, newOperativo);
        cout << "Bienvenido al equipo OMEGA" << endl;
    }
    cout << "Operativo insertado con exito" << endl;
}



void mostrarOperativos(Operativo* &Neon, Operativo* &OMEGA) {
    Operativo* aux = nullptr;
    int opc;
    cout << "Seleccione un equipo para mostrar sus operativos:" << endl;
    cout << "1. Equipo Neon" << endl;
    cout << "2. Equipo OMEGA" << endl;
    cin >> opc;

    if (opc == 1) {
        cout << "\n[Equipo Neon]" << endl;
        aux = Neon;
        while(aux!= nullptr){
            cout << "ID: " << aux->ID_Clave << " -> " ;
            aux = aux->prox;
        }   
    }
    else if (opc == 2) {
        cout << "\n[Equipo OMEGA]" << endl;
        aux = OMEGA;
        while(aux!= nullptr){
            cout << "ID: " << aux->ID_Clave << " -> " ;
            aux = aux->prox;
        }   
    }
    else cout << "Opcion no valida. Regresando al menu principal." << endl;

    
}

void buscar(Operativo* &Neon, Operativo* &OMEGA, int ID) {
    Operativo* aux = nullptr;
    bool encontrado = false;

    // Buscar en el equipo Neon
    aux = Neon;
    while (aux != nullptr) {
        if (aux->ID_Clave == ID) {
            cout << "Operativo encontrado en el equipo Neon: ID " << aux->ID_Clave<< endl;
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





//Ataques y defensas



int main (){
    presentacion();
    cout << "\nPresione ENTER para continuar...";
    cin.get();
    clearscreen();
    Operativo* Neon = nullptr;
    Operativo* OMEGA = nullptr;
    int opcion;

    do {
        cout << "\n=============================================" << endl;
        cout << "   YGGDRASIL - CENTRO DE MANDO  " << endl;
        cout << "=============================================" << endl;
        cout << "1. Gestion del Arbol B-4 (Insertar Operativo)" << endl;
        cout << "2. Extirpacion Manual (Eliminar por ID)" << endl;
        // cout << "3. Inteligencia (Buscar Ruta de Acceso)" << endl;
        // cout << "4. Auditoria Visual (Imprimir Arbol)" << endl;
        cout << "3. Mostrar Operativos por Equipo" << endl;
        cout << "4. Buscar Operativo por ID" << endl;
        cout << "5. Desconectar del Nucleo (Salir)" << endl;

        cout << "=============================================" << endl;
        cout << "Seleccione un comando: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                
                int ID, BandoNO, HP;
                cout << "\n[Función Insertar Operativo] " << endl;
                cout<< "Ingrese ID del Operativo: ";
                cin>> ID;
                cout<< "Ingrese Bando del Operativo (1 para Neon, 2 para OMEGA): "<<endl;
                cin>> BandoNO;

                HP=100;

                insertarOperativo(Neon, OMEGA, ID, BandoNO, HP);
                break;

            }
                
            case 2:
                eliminarOperativo(Neon, OMEGA);
                break;
            case 3:
                /*buscarInteligencia();*/
                break;
            case 4:
                /*auditoriaVisual();*/
                break;
            case 5:
                mostrarOperativos(Neon, OMEGA);
                break;
            case 6:
                int ID;
                cout << "\nIngrese el ID del operativo a buscar: ";
                cin >> ID;
                buscar(Neon, OMEGA, ID);
                break;
            case 7:
                cout << "\nDesconectando del Nucleo de Yggdrasil. Fin de la transmision." << endl;
                break;
            default:
                cout << "\n[ERROR] Comando no reconocido. Intente de nuevo." << endl;
        }

    } while (opcion != 7);

    return 0;
}