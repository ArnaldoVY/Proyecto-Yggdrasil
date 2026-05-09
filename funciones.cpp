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

// ==========================================
// MÉTODOS AUXILIARES DEL ÁRBOL B-4
// ==========================================

NodoBTree4* crearNodo(bool hoja) {
    NodoBTree4* nodo = new NodoBTree4;
    nodo->hoja = hoja;
    nodo->cantidad_actual = 0;
    for (int i = 0; i < 4; i++) {
        nodo->hijos[i] = nullptr;
    }
    for (int i = 0; i < 3; i++) {
        nodo->ocupantes[i] = nullptr;
    }
    return nodo;
}

NodoBTree4* buscarArbolB(NodoBTree4* nodo, int ID, bool mostrarRuta = false) {
    if (nodo == nullptr) {
        return nullptr;
    }

    if (mostrarRuta) {
        cout << " -> [";
        for (int j = 0; j < nodo->cantidad_actual; j++) {
            cout << nodo->ocupantes[j]->ID_Clave;
            if (j < nodo->cantidad_actual - 1) cout << ", ";
        }
        cout << "]";
    }

    int i = 0;
    while (i < nodo->cantidad_actual && ID > nodo->ocupantes[i]->ID_Clave) {
        i++;
    }
    if (i < nodo->cantidad_actual && ID == nodo->ocupantes[i]->ID_Clave) {
        return nodo;
    }
    if (nodo->hoja) {
        return nullptr;
    }
    return buscarArbolB(nodo->hijos[i], ID, mostrarRuta);
}

bool existeOperativo(NodoBTree4* Neon, NodoBTree4* OMEGA, int ID) {
    if (buscarArbolB(Neon, ID) != nullptr) return true;
    if (buscarArbolB(OMEGA, ID) != nullptr) return true;
    return false;
}

void dividirHijo(NodoBTree4* padre, int i, NodoBTree4* hijo) {
    NodoBTree4* nuevo = crearNodo(hijo->hoja);
    nuevo->cantidad_actual = 1;
    nuevo->ocupantes[0] = hijo->ocupantes[2]; 
    
    if (!hijo->hoja) {
        nuevo->hijos[0] = hijo->hijos[2];
        nuevo->hijos[1] = hijo->hijos[3];
    }
    
    hijo->cantidad_actual = 1; 
    
    for (int j = padre->cantidad_actual; j >= i + 1; j--) {
        padre->hijos[j + 1] = padre->hijos[j];
    }
    padre->hijos[i + 1] = nuevo;
    
    for (int j = padre->cantidad_actual - 1; j >= i; j--) {
        padre->ocupantes[j + 1] = padre->ocupantes[j];
    }
    padre->ocupantes[i] = hijo->ocupantes[1]; 
    padre->cantidad_actual++;
}

void insertarNoLleno(NodoBTree4* nodo, Operativo* op) {
    int i = nodo->cantidad_actual - 1;
    if (nodo->hoja) {
        while (i >= 0 && nodo->ocupantes[i]->ID_Clave > op->ID_Clave) {
            nodo->ocupantes[i + 1] = nodo->ocupantes[i];
            i--;
        }
        nodo->ocupantes[i + 1] = op;
        nodo->cantidad_actual++;
    } else {
        while (i >= 0 && nodo->ocupantes[i]->ID_Clave > op->ID_Clave) {
            i--;
        }
        i++;
        if (nodo->hijos[i]->cantidad_actual == 3) {
            dividirHijo(nodo, i, nodo->hijos[i]);
            if (nodo->ocupantes[i]->ID_Clave < op->ID_Clave) {
                i++;
            }
        }
        insertarNoLleno(nodo->hijos[i], op);
    }
}

void insertarArbolB(NodoBTree4*& raiz, Operativo* op) {
    if (raiz == nullptr) {
        raiz = crearNodo(true);
        raiz->ocupantes[0] = op;
        raiz->cantidad_actual = 1;
    } else {
        if (raiz->cantidad_actual == 3) {
            NodoBTree4* nuevaRaiz = crearNodo(false);
            nuevaRaiz->hijos[0] = raiz;
            dividirHijo(nuevaRaiz, 0, raiz);
            int i = 0;
            if (nuevaRaiz->ocupantes[0]->ID_Clave < op->ID_Clave) {
                i++;
            }
            insertarNoLleno(nuevaRaiz->hijos[i], op);
            raiz = nuevaRaiz;
        } else {
            insertarNoLleno(raiz, op);
        }
    }
}

// ---- ELIMINACIÓN ----
int buscarClaveIdx(NodoBTree4* nodo, int ID) {
    int idx = 0;
    while (idx < nodo->cantidad_actual && nodo->ocupantes[idx]->ID_Clave < ID)
        ++idx;
    return idx;
}

Operativo* obtenerPredecesor(NodoBTree4* nodo, int idx) {
    NodoBTree4* actual = nodo->hijos[idx];
    while (!actual->hoja)
        actual = actual->hijos[actual->cantidad_actual];
    return actual->ocupantes[actual->cantidad_actual - 1];
}

Operativo* obtenerSucesor(NodoBTree4* nodo, int idx) {
    NodoBTree4* actual = nodo->hijos[idx + 1];
    while (!actual->hoja)
        actual = actual->hijos[0];
    return actual->ocupantes[0];
}

void prestarDeAnterior(NodoBTree4* nodo, int idx) {
    NodoBTree4* hijo = nodo->hijos[idx];
    NodoBTree4* hermano = nodo->hijos[idx - 1]; 

    for (int i = hijo->cantidad_actual - 1; i >= 0; --i)
        hijo->ocupantes[i + 1] = hijo->ocupantes[i];

    if (!hijo->hoja) {
        for (int i = hijo->cantidad_actual; i >= 0; --i)
            hijo->hijos[i + 1] = hijo->hijos[i];
    }

    hijo->ocupantes[0] = nodo->ocupantes[idx - 1];

    if (!hijo->hoja)
        hijo->hijos[0] = hermano->hijos[hermano->cantidad_actual];

    nodo->ocupantes[idx - 1] = hermano->ocupantes[hermano->cantidad_actual - 1];

    hijo->cantidad_actual += 1;
    hermano->cantidad_actual -= 1;
}

void prestarDeSiguiente(NodoBTree4* nodo, int idx) {
    NodoBTree4* hijo = nodo->hijos[idx];
    NodoBTree4* hermano = nodo->hijos[idx + 1]; 

    hijo->ocupantes[(hijo->cantidad_actual)] = nodo->ocupantes[idx];

    if (!hijo->hoja)
        hijo->hijos[(hijo->cantidad_actual) + 1] = hermano->hijos[0];

    nodo->ocupantes[idx] = hermano->ocupantes[0];

    for (int i = 1; i < hermano->cantidad_actual; ++i)
        hermano->ocupantes[i - 1] = hermano->ocupantes[i];

    if (!hermano->hoja) {
        for (int i = 1; i <= hermano->cantidad_actual; ++i)
            hermano->hijos[i - 1] = hermano->hijos[i];
    }

    hijo->cantidad_actual += 1;
    hermano->cantidad_actual -= 1;
}

void fusionar(NodoBTree4* nodo, int idx) {
    NodoBTree4* hijo = nodo->hijos[idx];
    NodoBTree4* hermano = nodo->hijos[idx + 1];

    hijo->ocupantes[hijo->cantidad_actual] = nodo->ocupantes[idx]; 

    for (int i = 0; i < hermano->cantidad_actual; ++i)
        hijo->ocupantes[i + hijo->cantidad_actual + 1] = hermano->ocupantes[i]; 

    if (!hijo->hoja) {
        for (int i = 0; i <= hermano->cantidad_actual; ++i)
            hijo->hijos[i + hijo->cantidad_actual + 1] = hermano->hijos[i]; 
    }

    for (int i = idx + 1; i < nodo->cantidad_actual; ++i)
        nodo->ocupantes[i - 1] = nodo->ocupantes[i];

    for (int i = idx + 2; i <= nodo->cantidad_actual; ++i)
        nodo->hijos[i - 1] = nodo->hijos[i];

    hijo->cantidad_actual += hermano->cantidad_actual + 1; 
    nodo->cantidad_actual--;

    delete hermano;
}

void llenar(NodoBTree4* nodo, int idx) {
    if (idx != 0 && nodo->hijos[idx - 1]->cantidad_actual >= 2)
        prestarDeAnterior(nodo, idx);
    else if (idx != nodo->cantidad_actual && nodo->hijos[idx + 1]->cantidad_actual >= 2)
        prestarDeSiguiente(nodo, idx);
    else {
        if (idx != nodo->cantidad_actual)
            fusionar(nodo, idx);
        else
            fusionar(nodo, idx - 1);
    }
}

Operativo* borrarClave(NodoBTree4* nodo, int ID) {
    int idx = buscarClaveIdx(nodo, ID);

    if (idx < nodo->cantidad_actual && nodo->ocupantes[idx]->ID_Clave == ID) {
        if (nodo->hoja) {
            Operativo* op = nodo->ocupantes[idx];
            for (int i = idx + 1; i < nodo->cantidad_actual; ++i)
                nodo->ocupantes[i - 1] = nodo->ocupantes[i];
            nodo->cantidad_actual--;
            return op; 
        } else {
            if (nodo->hijos[idx]->cantidad_actual >= 2) {
                Operativo* pred = obtenerPredecesor(nodo, idx);
                Operativo* extraido = borrarClave(nodo->hijos[idx], pred->ID_Clave);
                Operativo* temp = nodo->ocupantes[idx];
                nodo->ocupantes[idx] = extraido;
                return temp; 
            } 
            else if (nodo->hijos[idx + 1]->cantidad_actual >= 2) {
                Operativo* suc = obtenerSucesor(nodo, idx);
                Operativo* extraido = borrarClave(nodo->hijos[idx + 1], suc->ID_Clave);
                Operativo* temp = nodo->ocupantes[idx];
                nodo->ocupantes[idx] = extraido;
                return temp;
            } 
            else {
                fusionar(nodo, idx);
                return borrarClave(nodo->hijos[idx], ID);
            }
        }
    } else {
        if (nodo->hoja) {
            return nullptr; 
        }
        
        bool flag = ((idx == nodo->cantidad_actual) ? true : false);

        if (nodo->hijos[idx]->cantidad_actual < 2) {
            llenar(nodo, idx);
        }

        if (flag && idx > nodo->cantidad_actual) {
            return borrarClave(nodo->hijos[idx - 1], ID);
        } else {
            return borrarClave(nodo->hijos[idx], ID);
        }
    }
}

bool eliminarDelArbolB(NodoBTree4*& raiz, int ID) {
    if (raiz == nullptr) return false;

    Operativo* op = borrarClave(raiz, ID);
    
    if (op != nullptr) {
        delete op; 
        
        if (raiz->cantidad_actual == 0) {
            NodoBTree4* viejaRaiz = raiz;
            if (raiz->hoja) {
                raiz = nullptr;
            } else {
                raiz = raiz->hijos[0];
            }
            delete viejaRaiz; 
        }
        return true;
    }
    return false;
}

void mostrarInOrden(NodoBTree4* nodo) {
    if (nodo != nullptr) {
        int i;
        for (i = 0; i < nodo->cantidad_actual; i++) {
            if (!nodo->hoja) {
                mostrarInOrden(nodo->hijos[i]);
            }
            cout << "  [*] ID: " << nodo->ocupantes[i]->ID_Clave 
                 << " | HP: " << nodo->ocupantes[i]->vida.actual << "/" << nodo->ocupantes[i]->vida.maximo
                 << " | Escudo: " << nodo->ocupantes[i]->escudo.actual << "/" << nodo->ocupantes[i]->escudo.maximo
                 << " | Arma: " << nodo->ocupantes[i]->arma.nombre << " (Dano: " << nodo->ocupantes[i]->arma.dano << ")" << endl;
        }
        if (!nodo->hoja) {
            mostrarInOrden(nodo->hijos[i]);
        }
    }
}

void imprimirEstructuraArbol(NodoBTree4* nodo, string prefijo, bool esUltimo, bool esRaiz, int nivel = 0) {
    if (nodo != nullptr) {
        if (esRaiz) {
            cout << "[";
            for (int i = 0; i < nodo->cantidad_actual; i++) {
                cout << nodo->ocupantes[i]->ID_Clave;
                if (i < nodo->cantidad_actual - 1) cout << ", ";
            }
            cout << "] (nivel 0)" << endl;
        } else {
            cout << prefijo << (esUltimo ? "+-- " : "|-- ");
            cout << "[";
            for (int i = 0; i < nodo->cantidad_actual; i++) {
                cout << nodo->ocupantes[i]->ID_Clave;
                if (i < nodo->cantidad_actual - 1) cout << ", ";
            }
            cout << "] (nivel " << nivel << ")" << endl;
        }

        if (!nodo->hoja) {
            string nuevoPrefijo = prefijo;
            if (!esRaiz) {
                nuevoPrefijo += (esUltimo ? "    " : "|   ");
            }
            
            for (int i = 0; i <= nodo->cantidad_actual; i++) {
                bool ultimoHijo = (i == nodo->cantidad_actual);
                imprimirEstructuraArbol(nodo->hijos[i], nuevoPrefijo, ultimoHijo, false, nivel + 1);
            }
        }
    }
}

// ==========================================
// MÉTODOS DEL PROGRAMA PRINCIPAL
// ==========================================

void insertarOperativo(NodoBTree4*& Neon, NodoBTree4*& OMEGA, int ID, int BandoNO, int HP) {
    if (existeOperativo(Neon, OMEGA, ID)) {
        cout << "Error: Ya existe un operativo con ID " << ID << ". No se puede insertar duplicado." << endl;
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

    if (newOperativo->Bando == 1) {
        insertarArbolB(Neon, newOperativo);
        cout << "Bienvenido al equipo Neon. Insertado en Arbol B-4." << endl;
    } else {
        insertarArbolB(OMEGA, newOperativo);
        cout << "Bienvenido al equipo OMEGA. Insertado en Arbol B-4." << endl;
    }
    cout << "Operativo insertado con exito" << endl;
}

void eliminarOperativo(NodoBTree4*& Neon, NodoBTree4*& OMEGA) {
    int equipo;
    int ID;
    cout << "\n[Eliminar Operativo por ID - Arbol B-4]" << endl;
    cout << "Seleccione un equipo: 1. Neon, 2. OMEGA" << endl;
    cin >> equipo;
    cout << "Ingrese el ID del operativo a eliminar: ";
    cin >> ID;

    bool eliminado = false;
    if (equipo == 1) {
        eliminado = eliminarDelArbolB(Neon, ID);
    } else if (equipo == 2) {
        eliminado = eliminarDelArbolB(OMEGA, ID);
    } else {
        cout << "Equipo no valido. Operacion cancelada." << endl;
        return;
    }

    if (eliminado) {
        cout << "Operativo con ID " << ID << " eliminado exitosamente y Arbol rebalanceado." << endl;
    } else {
        cout << "No se encontro ningun operativo con ID " << ID << " en el equipo seleccionado." << endl;
    }
}

void mostrarOperativos(NodoBTree4*& Neon, NodoBTree4*& OMEGA) {
    int opc;
    cout << "Seleccione un equipo para mostrar sus operativos:" << endl;
    cout << "1. Equipo Neon" << endl;
    cout << "2. Equipo OMEGA" << endl;
    cin >> opc;

    if (opc == 1) {
        cout << "\n=============================================" << endl;
        cout << "   LISTADO EQUIPO NEON (Orden Ascendente)" << endl;
        cout << "=============================================" << endl;
        if (Neon == nullptr) cout << "  (sin operativos)" << endl;
        else mostrarInOrden(Neon);
        cout << "=============================================" << endl;
    } else if (opc == 2) {
        cout << "\n=============================================" << endl;
        cout << "   LISTADO EQUIPO OMEGA (Orden Ascendente)" << endl;
        cout << "=============================================" << endl;
        if (OMEGA == nullptr) cout << "  (sin operativos)" << endl;
        else mostrarInOrden(OMEGA);
        cout << "=============================================" << endl;
    } else {
        cout << "Opcion no valida. Regresando al menu principal." << endl;
    }
}

void auditoriaVisual(NodoBTree4*& Neon, NodoBTree4*& OMEGA) {
    cout << "\n[Yggdrasil - Auditoria Visual B-Tree 4]" << endl;
    cout << "Raiz: Yggdrasil" << endl;

    cout << "\n  Estructura Arbol B-4: Equipo Neon" << endl;
    if (Neon == nullptr) {
        cout << "    (sin operativos)" << endl;
    } else {
        imprimirEstructuraArbol(Neon, "    ", true, true);
    }

    cout << "\n  Estructura Arbol B-4: Equipo OMEGA" << endl;
    if (OMEGA == nullptr) {
        cout << "    (sin operativos)" << endl;
    } else {
        imprimirEstructuraArbol(OMEGA, "    ", true, true);
    }
}

void buscar(NodoBTree4*& Neon, NodoBTree4*& OMEGA, int ID) {
    cout << "\n[Analisis de Ruta - Inteligencia Yggdrasil]" << endl;
    
    cout << "Buscando ID " << ID << " en equipo Neon..." << endl;
    cout << "Ruta:";
    NodoBTree4* encontrado = buscarArbolB(Neon, ID, true);
    
    if (encontrado != nullptr) {
        cout << "\n[RESULTADO] Operativo localizado en el equipo Neon." << endl;
        return;
    }
    
    cout << "\n\nBuscando ID " << ID << " en equipo OMEGA..." << endl;
    cout << "Ruta:";
    encontrado = buscarArbolB(OMEGA, ID, true);
    
    if (encontrado != nullptr) {
        cout << "\n[RESULTADO] Operativo localizado en el equipo OMEGA." << endl;
        return;
    }
    
    cout << "\n\n[RESULTADO] Operativo con ID " << ID << " no detectado en ningun sector del sistema." << endl;
}