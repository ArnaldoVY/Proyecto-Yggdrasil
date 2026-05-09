#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "structs.h"
#include <iostream>
#include <string>

using namespace std;

// Declaraciones de constantes
extern const ClasePersonaje Juggernaut;
extern const ClasePersonaje Ejecutor;
extern const ClasePersonaje Espectro;

// Declaraciones de funciones
void presentacion();
void clearscreen();

// Arbol B-4
void insertarOperativo(NodoBTree4*& Neon, NodoBTree4*& OMEGA, int ID, int BandoNO, int HP);
void eliminarOperativo(NodoBTree4*& Neon, NodoBTree4*& OMEGA);
bool eliminarDelArbolB(NodoBTree4*& raiz, int ID);
void mostrarOperativos(NodoBTree4*& Neon, NodoBTree4*& OMEGA);
void auditoriaVisual(NodoBTree4*& Neon, NodoBTree4*& OMEGA);
void buscar(NodoBTree4*& Neon, NodoBTree4*& OMEGA, int ID);

#endif