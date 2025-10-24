#include "../include/prestamo.h"

struct rep_prestamo {
  TSocio socio;
  TLibro libro;
  TFecha fechaRetiro;
  TFecha fechaDevolucion;
};

TPrestamo crearTPrestamo(TSocio socio, TLibro libro, TFecha fechaRetiro){
  TPrestamo nuevoPrestamo = new rep_prestamo;
  nuevoPrestamo->socio=socio;
  nuevoPrestamo->libro=libro;
  nuevoPrestamo->fechaRetiro=fechaRetiro;
  nuevoPrestamo->fechaDevolucion=NULL;
  return nuevoPrestamo;
}
 
void imprimirTPrestamo(TPrestamo prestamo){
  printf("Préstamo de libro %s a %s %s.\n", tituloTLibro(prestamo->libro),nombreTSocio(prestamo->socio),apellidoTSocio(prestamo->socio));
  imprimirTFecha(prestamo->fechaRetiro);
  if (prestamo->fechaDevolucion != NULL){
    imprimirTFecha(prestamo->fechaDevolucion);
  } else {
    printf("No retornado\n");
  }
}

void liberarTPrestamosSoloEstructura(TPrestamo &prestamo){
  liberarTFecha(prestamo->fechaDevolucion);
  liberarTFecha(prestamo->fechaRetiro);
  delete prestamo;
  prestamo = NULL;
}

void liberarTPrestamo(TPrestamo &prestamo) {
  if (prestamo != NULL) {
    // NO liberar libro ni socio aquí: son compartidos y tienen sus propios liberadores
    if (prestamo->fechaRetiro != NULL) {
      liberarTFecha(prestamo->fechaRetiro);
      prestamo->fechaRetiro = NULL;
    }
    if (prestamo->fechaDevolucion != NULL) {
      liberarTFecha(prestamo->fechaDevolucion);
      prestamo->fechaDevolucion = NULL;
    }
    delete prestamo;
    prestamo = NULL;
  }
}


TSocio socioTPrestamo(TPrestamo prestamo){
  TSocio socio = (prestamo->socio);
  return socio;
}
 
TFecha fechaRetiroTPrestamo(TPrestamo prestamo){
  TFecha retiro = prestamo->fechaRetiro;
  return retiro;
}

TFecha fechaDevolucionTPrestamo(TPrestamo prestamo){
  TFecha devolucion = prestamo->fechaDevolucion;
  return devolucion;
}

TLibro libroTPrestamo(TPrestamo prestamo){
  TLibro libro = (prestamo->libro);
  return libro;
}

bool fueRetornadoTPrestamo(TPrestamo prestamo){
  if(prestamo->fechaDevolucion != NULL){
    return true;
  }
  return false;
}

void actualizarFechaDevolucionTPrestamo(TPrestamo prestamo, TFecha fechaDevolucion){
  prestamo->fechaDevolucion=fechaDevolucion;
}

TPrestamo copiarTPrestamo(TPrestamo prestamo){
  TPrestamo copia;
  TSocio copiaSocio=copiarTSocio(prestamo->socio);
  TLibro copiaLibro=copiarTLibro(prestamo->libro);
  TFecha copiaFecha=copiarTFecha(prestamo->fechaRetiro);
  copia=crearTPrestamo(copiaSocio,copiaLibro,copiaFecha);
  if (fueRetornadoTPrestamo(prestamo)) {
    TFecha copiaFechaDevolucion = copiarTFecha(prestamo->fechaDevolucion);
    actualizarFechaDevolucionTPrestamo(copia, copiaFechaDevolucion);
  }
  return copia;
}