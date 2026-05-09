#ifndef STRUCTS_H
#define STRUCTS_H

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
};

struct NodoBTree4 {
    Operativo* ocupantes[3];
    NodoBTree4* hijos[4];
    int cantidad_actual;
    bool hoja;
};

#endif