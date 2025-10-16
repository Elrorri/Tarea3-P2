#include "../include/conjuntoGeneros.h"

struct rep_conjuntogeneros{
  int cantMax;
  int ids[1000000]; 
  int cardinal;
};

TConjuntoGeneros crearTConjuntoGeneros(int cantMax){
  TConjuntoGeneros nuevo = new rep_conjuntogeneros;
  nuevo->cantMax = cantMax;
  nuevo->cardinal = 0;
  for (int i = 0; i < cantMax; i++){
    nuevo->ids[i] = 0;
  }
  return nuevo;    
}

bool esVacioTConjuntoGeneros(TConjuntoGeneros c){
  if (c->cardinal == 0){
    return true;
  }
  else return false;
}

void insertarTConjuntoGeneros(TConjuntoGeneros &c, int id){
  if (c->cantMax > id && c->ids[id] == 0){
    c->ids[id]=1;
    c->cardinal++;
  }
  else return;
}

void borrarDeTConjuntoGeneros(TConjuntoGeneros &c, int id){
  if (c->cardinal != 0 && c->ids[id] == 1){
    c->ids[id]=0;
    c->cardinal--;
  }
  else return;
}

bool perteneceTConjuntoGeneros(TConjuntoGeneros c, int id){
  if (c == NULL) return false;
  if (id < 0 || id >= c->cantMax) return false;
  return c->ids[id] == 1;
}

int cardinalTConjuntoGeneros(TConjuntoGeneros c){
  int cardinal = c->cardinal;
  return cardinal;
}

int cantMaxTConjuntoGeneros(TConjuntoGeneros c){
  int cantMax = c->cantMax;
  return cantMax;
}

void imprimirTConjuntoGeneros(TConjuntoGeneros c){
  int cont=0;
  for (int i=0;i<c->cantMax;i++){
    if (c->ids[i] == 1){
      if (cont==0){
      printf("%d",i);
      cont++;}
      else printf(" %d",i);
    }
  }
  printf("\n");
}

void liberarTConjuntoGeneros(TConjuntoGeneros &c){
  delete c;
  c = NULL; 
}

void InicializarCG (TConjuntoGeneros q){
  q->cardinal=0;
  for (int i=0;i<q->cantMax;i++){
    q->ids[i]=0;
  }
}

TConjuntoGeneros unionTConjuntoGeneros(TConjuntoGeneros c1, TConjuntoGeneros c2){
  TConjuntoGeneros un = new rep_conjuntogeneros;
  if (c1->cantMax>=c2->cantMax ){
    un->cantMax=c1->cantMax;
  }else{
    un->cantMax=c2->cantMax;
  }
  InicializarCG(un);
  for (int i=0;i<un->cantMax;i++){
    if (c1->ids[i]==1||c2->ids[i]==1){
      un->ids[i]=1;
      un->cardinal++;
    }
  } 
  return un;
}

TConjuntoGeneros interseccionTConjuntoGeneros(TConjuntoGeneros c1, TConjuntoGeneros c2){
  TConjuntoGeneros in = new rep_conjuntogeneros;
  if (c1->cantMax>=c2->cantMax ){
    in->cantMax=c1->cantMax;
  }else{
    in->cantMax=c2->cantMax;
  }

  InicializarCG(in);
  for (int i=0;i<in->cantMax;i++){
    if (c1->ids[i]==1&&c2->ids[i]==1){
      in->ids[i]=1;
      in->cardinal++;
    }
  }
  return in;
}

TConjuntoGeneros diferenciaTConjuntoGeneros(TConjuntoGeneros c1, TConjuntoGeneros c2){
  TConjuntoGeneros dif = new rep_conjuntogeneros;
  if (c1->cantMax>=c2->cantMax ){
    dif->cantMax=c1->cantMax;
  }else{
    dif->cantMax=c2->cantMax;
  }
  InicializarCG(dif);
  for (int i=0;i<dif->cantMax;i++){
    if (c1->ids[i]==1 && c2->ids[i]==0){
      dif->ids[i]=1;
      dif->cardinal++;
    }
  }
  return dif;
}
