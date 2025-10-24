#include "../include/biblioteca.h"
#include <assert.h>
#include <stddef.h>

extern TABBLibros filtradoPorConjuntoDeGenerosTABBLibros(TABBLibros abbLibros, TConjuntoGeneros conjuntoGeneros);
extern void liberarConjuntoGeneros(TConjuntoGeneros &conjuntoGeneros);

struct rep_biblioteca {
  TABBLibros Libros;
  TLSESocios Socios;
  TLDEPrestamos Prestamos;
  TAGGeneros Generos;
  TColaReservas Reservas;
};

TBiblioteca crearTBiblioteca(){
  TBiblioteca nueva = new rep_biblioteca;
  nueva->Libros = crearTABBLibrosVacio();
  nueva->Socios = crearTLSESociosVacia();
  nueva->Prestamos = crearTLDEPrestamosVacia();
  nueva->Generos = crearTAGGeneros();
  nueva->Reservas = crearTColaReservas();
  return nueva;
}

void agregarLibroTBiblioteca(TBiblioteca biblioteca, TLibro libro){
  insertarLibroTABBLibros(biblioteca->Libros, libro);
}

void agregarSocioTBiblioteca(TBiblioteca biblioteca, TSocio socio){
  insertarTLSESocios(biblioteca->Socios, socio);
}

void prestarLibroTBiblioteca(TBiblioteca biblioteca, int ciSocio, int isbnLibro, TFecha fechaPrestamo){
  TSocio Socio = obtenerSocioTLSESocios(biblioteca->Socios, ciSocio);
  TLibro Libro = obtenerLibroTABBLibros(biblioteca->Libros, isbnLibro);
  if ((Socio!=NULL)&&(Libro!=NULL)){
  TPrestamo Prestamo = crearTPrestamo(Socio, Libro, fechaPrestamo);
  insertarTLDEPrestamos(biblioteca->Prestamos, Prestamo);
  }
}

bool disponibleLibroTBiblioteca(TBiblioteca biblioteca, int isbnLibro){
  bool existe = existeLibroTABBLibros(biblioteca->Libros, isbnLibro);
  if (existe){
    int noRet = 1;
    TLDEPrestamos noDisponibles = filtrarPrestamosTLDEPrestamos(biblioteca->Prestamos, noRet);
    nat cantidadDeNoRetornados = cantidadTLDEPrestamos(noDisponibles);
    bool estaPrestado = false;
    
    for (nat i = 1; i <= cantidadDeNoRetornados && !estaPrestado; i++){
      TPrestamo actual = obtenerNesimoTLDEPrestamos(noDisponibles, i);
      TLibro libro = libroTPrestamo(actual);
      int isbnLActual = isbnTLibro(libro);
      if (isbnLActual == isbnLibro) {
        estaPrestado = true;
      }
    }
    
    for(nat i=1; i <= cantidadDeNoRetornados; i++) {
        TPrestamo prestamo = obtenerNesimoTLDEPrestamos(noDisponibles, i);
        if (prestamo != NULL) { 
            TSocio socioCopia = socioTPrestamo(prestamo);
            TLibro libroCopia = libroTPrestamo(prestamo);
            if (socioCopia != NULL) liberarTSocio(socioCopia);
            if (libroCopia != NULL) liberarTLibro(libroCopia);
        }
    }
    liberarTLDEPrestamos(noDisponibles);
    
    return !estaPrestado;
  } 
  else {
    return false;
  }
}

void reservarLibroTBiblioteca(TBiblioteca biblioteca, int ciSocio, int isbnLibro){
  TSocio Socio = obtenerSocioTLSESocios(biblioteca->Socios, ciSocio);
  TLibro Libro = obtenerLibroTABBLibros(biblioteca->Libros, isbnLibro);
  TReserva reserva = crearTReserva(Socio, Libro);
  encolarTColaReservas(biblioteca->Reservas, reserva);
}

void devolverLibroTBiblioteca(TBiblioteca biblioteca, int ciSocio, int isbnLibro, TFecha fechaPrestamo, TFecha fechaDevolucion){
  int noRet = 1;
  TLDEPrestamos noDisponibles = filtrarPrestamosTLDEPrestamos(biblioteca->Prestamos, noRet);
  nat cantidadDeNoRetornados = cantidadTLDEPrestamos(noDisponibles);
  bool encontrado = false;
  
  nat cantidadOriginal = cantidadTLDEPrestamos(biblioteca->Prestamos);
  
  for (nat i = 1; i <= cantidadOriginal && !encontrado; i++){
    TPrestamo original = obtenerNesimoTLDEPrestamos(biblioteca->Prestamos, i);
    TLibro libroPrestamo = libroTPrestamo(original);
    TSocio socioPrestamo = socioTPrestamo(original);
    int ciPrestamo = ciTSocio(socioPrestamo);
    int isbnLActual = isbnTLibro(libroPrestamo);
    
    if ((isbnLActual == isbnLibro) && (ciSocio == ciPrestamo)) {
      actualizarFechaDevolucionTPrestamo(original, fechaDevolucion);
      encontrado = true;
    }
  }
  
  for(nat i=1; i <= cantidadDeNoRetornados; i++) {
    TPrestamo prestamo = obtenerNesimoTLDEPrestamos(noDisponibles, i);
    if (prestamo != NULL) {
        TSocio socioCopia = socioTPrestamo(prestamo);
        TLibro libroCopia = libroTPrestamo(prestamo);
        if (socioCopia != NULL) liberarTSocio(socioCopia);
        if (libroCopia != NULL) liberarTLibro(libroCopia);
    }
  }
  liberarTLDEPrestamos(noDisponibles);
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
  insertarGeneroTAGGeneros(biblioteca->Generos, idGeneroPadre, idGenero, nombreGenero);
}

TABBLibros obtenerLibrosDeGenero(TBiblioteca biblioteca, int idGenero) {
  TABBLibros Filtrado = crearTABBLibrosVacio();
  int Cant = cantidadTABBLibros(biblioteca->Libros);
  TConjuntoGeneros CG = obtenerConjuntoGeneros(biblioteca->Generos,idGenero);
  for (int i=1;i<=Cant;i++){
    TLibro Libro=obtenerNesimoLibroTABBLibros(biblioteca->Libros,i);
    int id = idGeneroTLibro(Libro);
    if (perteneceTConjuntoGeneros(CG,id)){
      TLibro copia = copiarTLibro(Libro);
      insertarLibroTABBLibros(Filtrado,copia);
    }
  }
  liberarTConjuntoGeneros(CG);
  return Filtrado;
}

void liberarTBiblioteca(TBiblioteca &biblioteca) {
    liberarTABBLibros(biblioteca->Libros);
    liberarTAGGeneros(biblioteca->Generos);
    liberarTColaReservasSoloEstructura(biblioteca->Reservas);
    liberarTLSESocios(biblioteca->Socios);
    liberarTLDEPrestamosSoloEstructura(biblioteca->Prestamos);
    delete biblioteca;
    biblioteca = NULL;
}