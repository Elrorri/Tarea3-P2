
#include "../include/agGeneros.h"
#include <assert.h>


struct rep_agGeneros {
  int id;
  char nombreGenero;
  TAGGeneros SigHermano;
  TAGGeneros SigHijo;
};

TAGGeneros crearTAGGeneros(){
  return NULL;
}

void insertarGeneroTAGGeneros(TAGGeneros &arbolGeneros, int idGeneroPadre, int idGenero, const char nombreGenero[MAX_NOMBRE] ){
}

void imprimirTAGGeneros(TAGGeneros arbolGeneros){
  if (arbolGeneros!=NULL){
    printf("%d - %s",arbolGeneros->id,arbolGeneros->nombreGenero);
    if (arbolGeneros->SigHijo!=NULL){
      printf("\n");
      imprimirTAGGeneros(arbolGeneros->SigHijo);
    }
    imprimirTAGGeneros(arbolGeneros->SigHermano);
  }
}
void liberarTAGGeneros(TAGGeneros &arbolGeneros){
  delete arbolGeneros;
  arbolGeneros = NULL;
}

bool existeGeneroTAGGeneros(TAGGeneros arbolGeneros, int idGenero){
  return false;
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
