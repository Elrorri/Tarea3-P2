#include "../include/agGeneros.h"
#include "../include/conjuntoGeneros.h"
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

TAGGeneros buscarNodo(TAGGeneros arbol, int idBuscado) {
    if (arbol == NULL) return NULL;
    
    if (arbol->id == idBuscado) {
        return arbol;
    }
    
    TAGGeneros encontrado = buscarNodo(arbol->SigHijo, idBuscado);
    if (encontrado != NULL) return encontrado;
    
    return buscarNodo(arbol->SigHermano, idBuscado);
}

void insertarGeneroTAGGeneros(TAGGeneros &arbolGeneros, int idGeneroPadre, int idGenero, const char nombreGenero[MAX_NOMBRE]) {
    if (arbolGeneros == NULL) {
        TAGGeneros nuevo = new rep_agGeneros;
        nuevo->id = idGenero;
        strncpy(nuevo->nombreGenero, nombreGenero, MAX_NOMBRE);
        nuevo->SigHijo = NULL;
        nuevo->SigHermano = NULL;
        arbolGeneros = nuevo;
    } else {
        TAGGeneros padre = buscarNodo(arbolGeneros, idGeneroPadre);
        
        if (padre != NULL) {
            TAGGeneros nuevoGenero = new rep_agGeneros;
            nuevoGenero->id = idGenero;
            strncpy(nuevoGenero->nombreGenero, nombreGenero, MAX_NOMBRE);
            nuevoGenero->SigHijo = NULL;
            nuevoGenero->SigHermano = NULL;

            if (padre->SigHijo == NULL) {
                padre->SigHijo = nuevoGenero;
            } else {
                nuevoGenero->SigHermano = padre->SigHijo;
                padre->SigHijo = nuevoGenero;
            }
        } else {
            return;
        }
    }
}

void imprimirTAGGenerosConNivel(TAGGeneros arbolGeneros, int nivel) {
    if (arbolGeneros == NULL) return;
    
    for (int i = 0; i < nivel; i++) {
        printf("    ");
    }
    
    printf("%d - %s\n", arbolGeneros->id, arbolGeneros->nombreGenero);
    
    imprimirTAGGenerosConNivel(arbolGeneros->SigHijo, nivel + 1);
    imprimirTAGGenerosConNivel(arbolGeneros->SigHermano, nivel);
}

void imprimirTAGGeneros(TAGGeneros arbolGeneros) {
    printf("Árbol de géneros:\n");
    imprimirTAGGenerosConNivel(arbolGeneros, 0);
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
  if (buscarNodo(arbolGeneros, idGenero) == NULL){
    return false;}
  else  {
    return true;}

}

char* nombreGeneroTAGGeneros(TAGGeneros arbolGeneros, int idGenero){
  buscarNodo(arbolGeneros, idGenero);
    return arbolGeneros->nombreGenero;
}

nat alturaTAGGeneros(TAGGeneros arbolGeneros){
    if (arbolGeneros == NULL) return 0;
    
    nat alturaMaxima = 0;
    TAGGeneros hijoActual = arbolGeneros->SigHijo;
    
    // Recorrer todos los hijos y encontrar la máxima altura
    while (hijoActual != NULL) {
        nat alturaHijo = alturaTAGGeneros(hijoActual);
        if (alturaHijo > alturaMaxima) {
            alturaMaxima = alturaHijo;
        }
        hijoActual = hijoActual->SigHermano;
    }
    
    return 1 + alturaMaxima;
}

nat cantidadTAGGeneros(TAGGeneros arbolGeneros){
  if (arbolGeneros == NULL) return 0;
  nat cantHijo = cantidadTAGGeneros(arbolGeneros->SigHijo);
  nat cantHermano = cantidadTAGGeneros(arbolGeneros->SigHermano);
  return 1 + cantHijo + cantHermano;
}
TAGGeneros obtenerSubarbolTAGGeneros(TAGGeneros arbolGeneros, int idGenero) {
    return buscarNodo(arbolGeneros, idGenero);
}

TConjuntoGeneros llenarConjuntoGenerosAux(TAGGeneros arbolGeneros, TConjuntoGeneros &conjunto) {
    if (arbolGeneros == NULL) return conjunto;
    insertarTConjuntoGeneros(conjunto, arbolGeneros->id);
    llenarConjuntoGenerosAux(arbolGeneros->SigHijo, conjunto);
    llenarConjuntoGenerosAux(arbolGeneros->SigHermano, conjunto);
    return conjunto;
}

TConjuntoGeneros obtenerConjuntoGeneros(TAGGeneros arbolGeneros, int idGenero) {
  arbolGeneros=buscarNodo(arbolGeneros, idGenero);
  if (arbolGeneros != NULL){
    TConjuntoGeneros conjunto = crearTConjuntoGeneros(obtenerMaxTAGGeneros(arbolGeneros) + 1);
    return llenarConjuntoGenerosAux(arbolGeneros, conjunto);
  }
  return NULL;
}

int obtenerMinTAGGeneros(TAGGeneros arbolGeneros) {
  return arbolGeneros->id;
}

int obtenerMaxTAGGeneros(TAGGeneros arbolGeneros) {
    if (arbolGeneros == NULL) return 0;
    
    int maxActual = arbolGeneros->id;
    
    // Buscar máximo en los hijos
    TAGGeneros hijo = arbolGeneros->SigHijo;
    while (hijo != NULL) {
        int maxHijo = obtenerMaxTAGGeneros(hijo);
        if (maxHijo > maxActual) {
            maxActual = maxHijo;
        }
        hijo = hijo->SigHermano;
    }
    
    // Buscar máximo en los hermanos
    TAGGeneros hermano = arbolGeneros->SigHermano;
    while (hermano != NULL) {
        int maxHermano = obtenerMaxTAGGeneros(hermano);
        if (maxHermano > maxActual) {
            maxActual = maxHermano;
        }
        hermano = hermano->SigHermano;
    }
    
    return maxActual;
}

void removerGeneroTAGGeneros(TAGGeneros &arbolGeneros, int idGenero){
    if (arbolGeneros == NULL) return;
    
    // Caso 1: El nodo a eliminar es la raíz
    if (arbolGeneros->id == idGenero) {
        TAGGeneros temp = arbolGeneros;
        arbolGeneros = arbolGeneros->SigHermano; // La nueva raíz será el hermano
        liberarAux(temp->SigHijo); // Liberar todos los hijos
        delete temp;
        return;
    }
    
    // Buscar el nodo en los hijos y hermanos
    TAGGeneros actual = arbolGeneros;
    
    // Buscar en los hermanos de la raíz
    while (actual->SigHermano != NULL) {
        if (actual->SigHermano->id == idGenero) {
            TAGGeneros nodoAEliminar = actual->SigHermano;
            actual->SigHermano = nodoAEliminar->SigHermano; // Saltar el nodo
            liberarAux(nodoAEliminar->SigHijo); // Liberar todos los hijos del nodo eliminado
            delete nodoAEliminar;
            return;
        }
        actual = actual->SigHermano;
    }
    
    // Buscar recursivamente en los hijos
    actual = arbolGeneros;
    while (actual != NULL) {
        if (actual->SigHijo != NULL) {
            // Si el hijo es el que queremos eliminar
            if (actual->SigHijo->id == idGenero) {
                TAGGeneros nodoAEliminar = actual->SigHijo;
                actual->SigHijo = nodoAEliminar->SigHermano; // El primer hijo ahora es el hermano
                liberarAux(nodoAEliminar->SigHijo); // Liberar hijos del nodo eliminado
                delete nodoAEliminar;
                return;
            } else {
                // Buscar recursivamente en el subárbol del hijo
                removerGeneroTAGGeneros(actual->SigHijo, idGenero);
            }
        }
        actual = actual->SigHermano;
    }
}