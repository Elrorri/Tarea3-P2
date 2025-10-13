
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
  // Reserva de libro <titulo libro> por <nombre socio> <apellido socio>.
  printf ("Reserva de libro %s por %s %s.\n", tituloTLibro(reserva->libro),nombreTSocio(reserva->socio),apellidoTSocio(reserva->socio));
}

void liberarTReserva(TReserva &reserva){
  liberarTLibro(reserva->libro);
  liberarTSocio(reserva->socio);
  delete reserva;
  reserva = NULL;
}

TSocio socioTReserva(TReserva reserva){
  return NULL;
}

TLibro libroTReserva(TReserva reserva){
  return NULL;
}

TReserva copiarTReserva(TReserva reserva){
  return NULL;
}

void liberarTReservaSoloEstructura(TReserva &reserva) {
}
