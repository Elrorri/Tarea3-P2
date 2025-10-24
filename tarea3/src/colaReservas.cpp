#include "../include/colaReservas.h"

struct cola{
  TReserva reserva;
  cola* sig;
};

struct rep_colaReservas {
  cola* primero;
  cola* ultimo;
};

TColaReservas crearTColaReservas(){
  TColaReservas nuevaCola = new rep_colaReservas;
  nuevaCola->primero = NULL;
  nuevaCola->ultimo = NULL;
  return nuevaCola;
}

void encolarTColaReservas(TColaReservas &colaReservas, TReserva reserva){
  cola* nuevaCola = new cola;
  nuevaCola->reserva = reserva;
  nuevaCola->sig = NULL;
  
  if (colaReservas->primero == NULL){
    colaReservas->primero = nuevaCola;
    colaReservas->ultimo = nuevaCola;
  } else {
    colaReservas->ultimo->sig = nuevaCola;
    colaReservas->ultimo = nuevaCola;
  }
}

void desencolarTColaReservas(TColaReservas &colaReservas) {
  if (colaReservas->primero == NULL) return;
  
  cola* temp = colaReservas->primero;
  colaReservas->primero = colaReservas->primero->sig;
  
  if (colaReservas->primero == NULL){
    colaReservas->ultimo = NULL;
  }
  
  liberarTReserva(temp->reserva);
  delete temp;
}

TReserva frenteTColaReservas(TColaReservas colaReservas) {
  if (colaReservas->primero == NULL) return NULL;
  return colaReservas->primero->reserva;
}

nat cantidadTColaReservas(TColaReservas colaReservas){
  nat cont = 0;
  cola* actual = colaReservas->primero;
  while (actual != NULL) {
    cont++;
    actual = actual->sig;
  }
  return cont;
}

void imprimirTColaReservas(TColaReservas colaReservas){
  printf("Cola de Reservas:\n");
  cola* actual = colaReservas->primero;
  while (actual != NULL) {
    imprimirTReserva(actual->reserva);
    actual = actual->sig;
  }
}

void liberarTColaReservas(TColaReservas &colaReservas){
  while (colaReservas->primero != NULL) {
    desencolarTColaReservas(colaReservas);
  }
  delete colaReservas;
  colaReservas = NULL;
}

void liberarTColaReservasSoloEstructura(TColaReservas &colaReservas){
  cola* aBorrar;
  cola* avanzar;
  avanzar=colaReservas->primero;
  while(avanzar!=NULL){
    aBorrar=avanzar;
    avanzar=avanzar->sig;
    liberarTReservaSoloEstructura(aBorrar->reserva);
    delete aBorrar;
  }
  delete colaReservas;
  colaReservas = NULL;
}

TReserva extraerFrenteTColaReservas(TColaReservas &colaReservas) {
  if (colaReservas->primero == NULL) return NULL;
  TReserva extraida = colaReservas->primero->reserva;
  desencolarTColaReservas(colaReservas);
  return extraida;
}