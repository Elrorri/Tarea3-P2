#include "../include/agGeneros.h"
#include <assert.h>
#include <string.h>

struct rep_agGeneros {
  int id;
  char nombreGenero[MAX_NOMBRE];
  TAGGeneros SigHermano;
  TAGGeneros SigHijo;
};

TAGGeneros crearTAGGeneros(){
  return NULL;
}

static bool insertarAux(TAGGeneros nodo, int idGeneroPadre, int idGenero, const char nombreGenero[MAX_NOMBRE] ){
    if (nodo == NULL) {
        return false;
    }

    if (nodo->id == idGeneroPadre) {
        TAGGeneros nuevo = new rep_agGeneros;
        nuevo->id = idGenero;
        strncpy(nuevo->nombreGenero, nombreGenero, MAX_NOMBRE);
        nuevo->nombreGenero[MAX_NOMBRE-1] = '\0';
        nuevo->SigHijo = NULL;
        nuevo->SigHermano = NULL;
        
        if (nodo->SigHijo == NULL) {
            nodo->SigHijo = nuevo;
        } else {
            TAGGeneros aux = nodo->SigHijo;
            while (aux->SigHermano != NULL) {
                aux = aux->SigHermano;
            }
            aux->SigHermano = nuevo;
        }
        return true;
        
    } else {
        if (insertarAux(nodo->SigHijo, idGeneroPadre, idGenero, nombreGenero)) {
            return true; 
        }
        
        return insertarAux(nodo->SigHermano, idGeneroPadre, idGenero, nombreGenero);
    }
}

void insertarGeneroTAGGeneros(TAGGeneros &arbolGeneros, int idGeneroPadre, int idGenero, const char nombreGenero[MAX_NOMBRE] ){
    if (arbolGeneros == NULL) {
        if (idGeneroPadre == -1) { 
             TAGGeneros nuevo = new rep_agGeneros;
             nuevo->id = idGenero;
             strncpy(nuevo->nombreGenero, nombreGenero, MAX_NOMBRE);
             nuevo->nombreGenero[MAX_NOMBRE-1] = '\0';
             nuevo->SigHijo = NULL;
             nuevo->SigHermano = NULL;
             arbolGeneros = nuevo;
             return;
        }
        return;
    }
    
    insertarAux(arbolGeneros, idGeneroPadre, idGenero, nombreGenero);
}

static void imprimirAux(TAGGeneros arbolGeneros, int nivel){
    if (arbolGeneros != NULL){
        
        for (int i = 0; i < nivel; i++) {
            printf(" "); 
        }

        if (nivel == 0) {
            printf("%d - %s\n", arbolGeneros->id, arbolGeneros->nombreGenero);
        } else if (nivel == 1) {
            printf("%d- %s\n", arbolGeneros->id, arbolGeneros->nombreGenero);
        } else {
            printf("%d %s\n", arbolGeneros->id, arbolGeneros->nombreGenero);
        }

        if (arbolGeneros->SigHijo != NULL) {
            imprimirAux(arbolGeneros->SigHijo, nivel + 1);
        }

        imprimirAux(arbolGeneros->SigHermano, nivel);
    }
}

void imprimirTAGGeneros(TAGGeneros arbolGeneros) {
    imprimirAux(arbolGeneros, 0);
}

static void liberarAux(TAGGeneros nodo) {
  if (nodo == NULL) return;
  liberarAux(nodo->SigHijo);
  liberarAux(nodo->SigHermano);
  delete nodo;
}

void liberarTAGGeneros(TAGGeneros &arbolGeneros){
  liberarAux(arbolGeneros);
  arbolGeneros = NULL;
}

bool existeGeneroTAGGeneros(TAGGeneros arbolGeneros, int idGenero){
  return NULL;
}

char* nombreGeneroTAGGeneros(TAGGeneros arbolGeneros, int idGenero){
    return NULL;
}


nat alturaTAGGeneros(TAGGeneros arbolGeneros){
    return 0;
}

nat cantidadTAGGeneros(TAGGeneros arbolGeneros){
    return 0;
}

TAGGeneros obtenerSubarbolTAGGeneros(TAGGeneros arbolGeneros, int idGenero) {
  return NULL;
}

TConjuntoGeneros obtenerConjuntoGeneros(TAGGeneros arbolGeneros, int idGenero) {
  return NULL;
}

int obtenerMaxTAGGeneros(TAGGeneros arbolGeneros) {
  return 0;
}

void removerGeneroTAGGeneros(TAGGeneros &arbolGeneros, int idGenero){
}