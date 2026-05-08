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
void insertarOrdenadoAscendente(Operativo*& head, Operativo* newOp);
bool existeOperativoEnLista(Operativo* head, int ID);
bool existeOperativo(Operativo* Neon, Operativo* OMEGA, int ID);
bool eliminarOperativoPorID(Operativo*& head, int ID);
void eliminarOperativo(Operativo*& Neon, Operativo*& OMEGA);
void insertarOperativo(Operativo*& Neon, Operativo*& OMEGA, int ID, int BandoNO, int HP);
void mostrarOperativos(Operativo*& Neon, Operativo*& OMEGA);
void auditoriaVisual(Operativo*& Neon, Operativo*& OMEGA);
void buscar(Operativo*& Neon, Operativo*& OMEGA, int ID);

#endif