#include "../include/libro.h"
#include "../include/fecha.h"

struct rep_libro {
    int isbn;
    char titulo[MAX_TITULO];
    char nombreAutor[MAX_NOMBRE_AUTOR];
    char apellidoAutor[MAX_APELLIDO_AUTOR];
    char descripcion[MAX_DESCRIPCION];
    int idGeneroLibro;
    TFecha fechaEdicion;
};

// Crea y retorna un elemento de tipo TLibro con los valores dados
TLibro crearTLibro(int isbn, const char titulo[MAX_TITULO], const char nombreAutor[MAX_NOMBRE_AUTOR], const char apellidoAutor[MAX_APELLIDO_AUTOR], const char descripcion[MAX_DESCRIPCION], int idGeneroLibro, TFecha fechaEdicion){
    TLibro nuevoLibro = new rep_libro;
    nuevoLibro->isbn = isbn;
    strncpy(nuevoLibro->titulo, titulo, MAX_TITULO);
    strncpy(nuevoLibro->nombreAutor, nombreAutor, MAX_NOMBRE_AUTOR); 
    strncpy(nuevoLibro->apellidoAutor, apellidoAutor, MAX_APELLIDO_AUTOR);
    strncpy(nuevoLibro->descripcion, descripcion, MAX_DESCRIPCION);
    nuevoLibro->idGeneroLibro = idGeneroLibro;
    nuevoLibro->fechaEdicion = fechaEdicion;
    return nuevoLibro;
}

// Libera la memoria asignada para el libro 'l'
// Debe liberar también la memoria de la fecha asociada
void liberarTLibro(TLibro &l){
    liberarTFecha(l->fechaEdicion);
    delete l;
    l = NULL;
}

// Retorna el isbn del libro 'l'
int isbnTLibro(TLibro l){
    int isbn = l->isbn;
    return isbn;
}

// Retorna el titulo del libro 'l'
// El titulo retornado comparte memoria con el parámetro. 
char* tituloTLibro(TLibro l){
    char* titulo = l->titulo;
    return titulo;
}

// Retorna la descripción del libro 'l'
// La descripción retornada comparte memoria con el parámetro. 
char* descripcionTLibro(TLibro l){
    char* descripcion = l->descripcion;
    return descripcion;
}

// Retorna el nombre del autor del libro 'l'
// El nombre retornado comparte memoria con el parámetro. 
char* nombreAutorTLibro(TLibro l){
    char* nombreAutor = l->nombreAutor;
    return nombreAutor;
}

// Retorna el apellido del autor del libro 'l'
// El apellido retornado comparte memoria con el parámetro. 
char* apellidoAutorTLibro(TLibro l){
    char* apellidoAutor = l->apellidoAutor;
    return apellidoAutor;
}

// Retorna el id del género del libro 'l'
int idGeneroTLibro(TLibro l){
    int idGenero = l->idGeneroLibro;
    return idGenero;
}

// Retorna la fecha de edición del libro 'l'.
// La fecha retornada comparte memoria con el parámetro. 
TFecha fechaEdicionTLibro(TLibro l){
    return l->fechaEdicion;
}

// Imprime la información del libro 'l' en el siguiente formato:
// Libro <isbn> 
// Título: <título>
// Autor: <nombre autor> <apellido autor>
// Descripción: <descripcion>
// Género: <id género>
// Fecha de edición: <fecha de edición>
void imprimirTLibro(TLibro l){
    printf("Libro %d\n", l->isbn);
    printf("Título: %s\n", l->titulo);
    printf("Autor: %s %s\n", l->nombreAutor, l->apellidoAutor);
    printf("Descripción: %s\n", l->descripcion);
    printf("Género: %d\n", l->idGeneroLibro);
    printf("Fecha de edición: ");
    imprimirTFecha(l->fechaEdicion);
}

// Retorna una copia del libro 'l' que no comparte memoria con el parámetro.
TLibro copiarTLibro(TLibro l){
    TLibro copia = new rep_libro;
    copia->isbn = l->isbn;
    strncpy(copia->titulo, l->titulo, MAX_TITULO);
    strncpy(copia->nombreAutor, l->nombreAutor, MAX_NOMBRE_AUTOR);
    strncpy(copia->apellidoAutor, l->apellidoAutor, MAX_APELLIDO_AUTOR);
    strncpy(copia->descripcion, l->descripcion, MAX_DESCRIPCION);
    copia->idGeneroLibro = l->idGeneroLibro;
    copia->fechaEdicion = copiarTFecha(l->fechaEdicion);
    return copia;
}
