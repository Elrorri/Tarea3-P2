
#include "../include/reserva.h"

struct rep_reserva {
  TSocio socio;
  TLibro libro;
};

TReserva crearTReserva(TSocio socio, TLibro libro){
  TReserva nueva = new rep_reserva;
  nueva->libro=libro;
  nueva->socio=socio;
  return nueva; }

void imprimirTReserva(TReserva reserva){
  printf ("Reserva de libro %s por %s %s.\n", tituloTLibro(reserva->libro),nombreTSocio(reserva->socio),apellidoTSocio(reserva->socio));
}

void liberarTReserva(TReserva &reserva){
  liberarTLibro(reserva->libro);
  liberarTSocio(reserva->socio);
  delete reserva;
  reserva = NULL;
}

TSocio socioTReserva(TReserva reserva){
  TSocio devolver = reserva->socio;
  return devolver;
}

TLibro libroTReserva(TReserva reserva){
  TLibro devolver = reserva->libro;
  return devolver;
}

TReserva copiarTReserva(TReserva reserva){
  TReserva copia = new rep_reserva;
  TSocio CSocio = copiarTSocio(reserva->socio);
  TLibro CLibro = copiarTLibro(reserva->libro);
  copia->libro=CLibro;
  copia->socio=CSocio;
  return copia;
}

void liberarTReservaSoloEstructura(TReserva &reserva) {
  delete reserva;
  reserva = NULL;
}
