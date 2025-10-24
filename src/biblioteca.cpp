#include "../include/biblioteca.h"
#include <assert.h>

struct rep_biblioteca {
  TABBLibros Libros;
  TLSESocios Socios;
  TLDEPrestamos Prestamos;
  TAGGeneros Generos;
  TColaReservas Reservas;
};

TBiblioteca crearTBiblioteca(){
  TBiblioteca nueva = new rep_biblioteca;
  nueva->Libros=crearTABBLibrosVacio;
  nueva->Socios=crearTLSESociosVacia;
  nueva->Prestamos=crearTLDEPrestamosVacia;
  nueva->Generos=crearTAGGeneros;
  nueva->Reservas=crearTColaReservas;
  return nueva;
}

void agregarLibroTBiblioteca(TBiblioteca biblioteca, TLibro libro){
  insertarLibroTABBLibros(biblioteca->Libros,libro);
}

void agregarSocioTBiblioteca(TBiblioteca biblioteca, TSocio socio){
  insertarTLSESocios(biblioteca->Socios,socio);
}

void prestarLibroTBiblioteca(TBiblioteca biblioteca, int ciSocio, int isbnLibro, TFecha fechaPrestamo){
  TSocio Socio = obtenerSocioTLSESocios(biblioteca->Socios,ciSocio);
  TLibro Libro = obtenerLibroTABBLibros(biblioteca->Libros,isbnLibro);
  TPrestamo Prestamo = crearTPrestamo(Socio,Libro,fechaPrestamo);
  insertarTLDEPrestamos(biblioteca->Prestamos,Prestamo);
}


bool disponibleLibroTBiblioteca(TBiblioteca biblioteca, int isbnLibro){
  bool existe = existeLibroTABBLibros(biblioteca->Libros,isbnLibro);
  if (existe){
    int noRet=1;
    TLDEPrestamos noDisponibles = filtrarPrestamosTLDEPrestamos(biblioteca->Prestamos,noRet);
    nat cantidadDeNoRetornados = cantidadTLDEPrestamos(noDisponibles);
    for (nat i=1;i<=cantidadDeNoRetornados;i++){
      TPrestamo actual = obtenerNesimoTLDEPrestamos(noDisponibles,i);
      TLibro libro = libroTPrestamo(actual);
      int isbnLActual = isbnTLibro(libro);
      if (isbnLActual == isbnLibro) return false;
    }
    return true;
  } 
  else return false;
}

void reservarLibroTBiblioteca(TBiblioteca biblioteca, int ciSocio, int isbnLibro){
  TSocio Socio = obtenerSocioTLSESocios(biblioteca->Socios,ciSocio);
  TLibro Libro = obtenerLibroTABBLibros(biblioteca->Libros,isbnLibro);
  TReserva reserva = crearTReserva(Socio,Libro);
  encolarTColaReservas(biblioteca->Reservas,reserva);
}

void devolverLibroTBiblioteca(TBiblioteca biblioteca, int ciSocio, int isbnLibro, TFecha fechaPrestamo, TFecha fechaDevolucion){
  int noRet=1;
  TLDEPrestamos noDisponibles = filtrarPrestamosTLDEPrestamos(biblioteca->Prestamos,noRet);
  nat cantidadDeNoRetornados = cantidadTLDEPrestamos(noDisponibles);
  for (nat i=1;i<=cantidadDeNoRetornados;i++){
    TPrestamo actual = obtenerNesimoTLDEPrestamos(noDisponibles,i);
    TLibro libroPrestamo = libroTPrestamo(actual);
    TSocio socioPrestamo = socioTPrestamo(actual);
    int ciPrestamo = ciTSocio(socioPrestamo);
    int isbnLActual = isbnTLibro(libroPrestamo);
    if ((isbnLActual == isbnLibro) && (ciSocio == ciPrestamo)) {
      actualizarFechaDevolucionTPrestamo(actual,fechaDevolucion);
      return;
    }
  }
}

void imprimirSociosTBiblioteca(TBiblioteca biblioteca){
  imprimirTLSESocios(biblioteca->Socios);
}

void imprimirLibrosTBiblioteca(TBiblioteca biblioteca){
  imprimirTABBLibros(biblioteca->Libros);
}

void imprimirReservasTBiblioteca(TBiblioteca biblioteca){
  imprimirTColaReservas(biblioteca->Reservas);
}

void imprimirPrestamosTBiblioteca(TBiblioteca biblioteca){
  imprimirTLDEPrestamos(biblioteca->Prestamos);
}

void agregarGeneroABiblioteca(TBiblioteca biblioteca, int idGeneroPadre, int idGenero, const char nombreGenero[MAX_NOMBRE]) {
  insertarGeneroTAGGeneros(biblioteca->Generos,idGeneroPadre,idGenero,nombreGenero);
}

TABBLibros obtenerLibrosDeGenero(TBiblioteca biblioteca, int idGenero) {
  TABBLibros filtrados = filtradoPorGeneroTABBLibros(biblioteca->Libros,idGenero);
  return filtrados;
}

void liberarTBiblioteca(TBiblioteca &biblioteca) {
  liberarTABBLibros(biblioteca->Libros);
  liberarTColaReservas(biblioteca->Reservas);
  liberarTLDEPrestamos(biblioteca->Prestamos);
  liberarTLSESocios(biblioteca->Socios);
  liberarTAGGeneros(biblioteca->Generos);
  delete biblioteca;
  biblioteca = NULL;
}
