#include <iostream>
#include <string>

using namespace std;
//Presentacion y limpieza de pantalla
    void presentacion() {
        cout << "¡Bienvenido a Yggdrasil, el juego de estrategia y defensa!" << endl;
        cout << "En este mundo, cada unidad tiene su propia pila de escudos y un arsenal de armas." << endl;
        cout << "¡Preparate para defender tu base y atacar a tus enemigos!" << endl;
    }

    void clearscreen() {

        cout << string(100, '\n');
    }


//Parte 1 Gestion del arbol B-4


struct Operativo {
    int ID_Clave;
    int Bando;
    int HP_Base;
    Operativo*prox;
    
};


struct NodoBTree4 {
    Operativo* ocupantes[3];
    NodoBTree4* hijos[4];
    int cantidad_actual;
    bool hoja;
}; 
void insertarOperativo(Operativo *&Neon,Operativo *&OMEGA,int ID, int BandoNO, int HP) {
    Operativo* newOperativo = new Operativo;
   
    newOperativo->Bando=BandoNO;
    newOperativo->ID_Clave=ID;
    newOperativo->HP_Base=HP;
    Operativo* aux = nullptr;
    if(newOperativo->Bando==1){
       if(Neon==nullptr) Neon=newOperativo;
    
        else{
            aux=Neon;
            newOperativo->prox=aux;
            Neon=newOperativo;
        }
        cout<<"Bienvenido al equipo Neon"<<endl;
        
    }
    else if(newOperativo->Bando==2){
        if(OMEGA==nullptr) OMEGA=newOperativo;
    
        else{
            aux=OMEGA;
            newOperativo->prox=aux;
            OMEGA=newOperativo;
        }
        cout<<"Bienvenido al equipo OMEGA"<<endl;
    }
    cout<<"Operativo insertado con exito"<<endl;

}


//Personajes y perfiles de equipamiento
struct Arma {
    string nombre;
    int dano;
};

struct ClasePersonaje {
    string nombre;
    int HP_Base;
    Arma arma_base;
    int escudos_iniciales;
    string tipo_escudo;
    bool control_mental;
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
        cout << "3. Inteligencia (Buscar Ruta de Acceso)" << endl;
        cout << "4. Auditoria Visual (Imprimir Arbol)" << endl;
        cout << "5. Desconectar (Salir)" << endl;
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
               /* eliminarOperativo();*/
                break;
            case 3:
                /*buscarInteligencia();*/
                break;
            case 4:
                /*auditoriaVisual();*/
                break;
            case 5:
                cout << "\nDesconectando del Nucleo de Yggdrasil. Fin de la transmision." << endl;
                break;
            default:
                cout << "\n[ERROR] Comando no reconocido. Intente de nuevo." << endl;
        }

    } while (opcion != 5);

    return 0;
}