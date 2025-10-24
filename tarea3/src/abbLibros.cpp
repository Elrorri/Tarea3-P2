#include "../include/abbLibros.h"
#include <stddef.h>

struct rep_abbLibros {
    TLibro libro;
    TABBLibros Izquierdo;
    TABBLibros Derecho;
};

TABBLibros crearTABBLibrosVacio(){
    return NULL;
}
void insertarLibroTABBLibros(TABBLibros &abbLibros, TLibro libro) {
    if (abbLibros == NULL) {
        abbLibros = new rep_abbLibros;
        abbLibros->libro = libro;
        abbLibros->Izquierdo = NULL;
        abbLibros->Derecho = NULL;
    } else if (isbnTLibro(libro) < isbnTLibro(abbLibros->libro)) {
        insertarLibroTABBLibros(abbLibros->Izquierdo, libro);
    } else {
        insertarLibroTABBLibros(abbLibros->Derecho, libro);
    }
}
void imprimirTABBLibros(TABBLibros abbLibros) {
    if (abbLibros != NULL) {
        imprimirTABBLibros(abbLibros->Izquierdo);
        imprimirTLibro(abbLibros->libro);
        imprimirTABBLibros(abbLibros->Derecho);
    }
}

void liberarTABBLibros(TABBLibros &abbLibros) {
    if (abbLibros != NULL) {
        liberarTABBLibros(abbLibros->Izquierdo);
        liberarTABBLibros(abbLibros->Derecho);
        liberarTLibro(abbLibros->libro); 
        delete abbLibros;
        abbLibros = NULL; 
    }
}

bool existeLibroTABBLibros(TABBLibros abbLibros, int isbn) {
    if (abbLibros == NULL) {
        return false;
    }
    if (isbn < isbnTLibro(abbLibros->libro)) {
        return existeLibroTABBLibros(abbLibros->Izquierdo, isbn);
    } else if (isbn > isbnTLibro(abbLibros->libro)) {
        return existeLibroTABBLibros(abbLibros->Derecho, isbn);
    } else {
        return true;
    }
}

TLibro obtenerLibroTABBLibros(TABBLibros abbLibros, int isbn){
    if (abbLibros == NULL) {
        return NULL;
    }
    if (isbn < isbnTLibro(abbLibros->libro)) {
        return obtenerLibroTABBLibros(abbLibros->Izquierdo, isbn);
    } else if (isbn > isbnTLibro(abbLibros->libro)) {
        return obtenerLibroTABBLibros(abbLibros->Derecho, isbn);
    } else {
        return abbLibros->libro;
    }
}

nat alturaTABBLibros(TABBLibros abbLibros){
    if (abbLibros == NULL){
        return 0;
    } else {    
        nat alturaIzquierda = alturaTABBLibros(abbLibros->Izquierdo);
        nat alturaDerecha = alturaTABBLibros(abbLibros->Derecho);
        if (alturaIzquierda > alturaDerecha) {
            return alturaIzquierda + 1;
        } else {
            return alturaDerecha + 1;   
        }}
}

TLibro maxISBNLibroTABBLibros(TABBLibros abbLibros){
    if (abbLibros == NULL) {
        return NULL;
    }
    if (abbLibros->Derecho != NULL) {
        return maxISBNLibroTABBLibros(abbLibros->Derecho);
    } else {
        return abbLibros->libro;
    }   
}

void removerLibroTABBLibros(TABBLibros &abbLibros, int isbn) {
    if (abbLibros == NULL) {
        return;
    }

    if (isbn < isbnTLibro(abbLibros->libro)) {
        removerLibroTABBLibros(abbLibros->Izquierdo, isbn);
    } else if (isbn > isbnTLibro(abbLibros->libro)) {
        removerLibroTABBLibros(abbLibros->Derecho, isbn);
    } else {
        if (abbLibros->Izquierdo == NULL) {
            TABBLibros aRemover = abbLibros;
            abbLibros = abbLibros->Derecho;
            liberarTLibro(aRemover->libro);
            delete aRemover;
        } else if (abbLibros->Derecho == NULL) {
            TABBLibros aRemover = abbLibros;
            abbLibros = abbLibros->Izquierdo;
            liberarTLibro(aRemover->libro);
            delete aRemover;
        } else {
            TABBLibros maxIzquierdo = abbLibros->Izquierdo;
            while (maxIzquierdo->Derecho != NULL) {
                maxIzquierdo = maxIzquierdo->Derecho;
            }
            
            TLibro tempLibro = abbLibros->libro;
            abbLibros->libro = maxIzquierdo->libro;
            maxIzquierdo->libro = tempLibro;

            removerLibroTABBLibros(abbLibros->Izquierdo, isbnTLibro(maxIzquierdo->libro));
        }
    }
}

int cantidadTABBLibros(TABBLibros abbLibros){
    if (abbLibros == NULL) {
        return 0;
    }
    return 1 + cantidadTABBLibros(abbLibros->Izquierdo) + cantidadTABBLibros(abbLibros->Derecho);
}

void obtenerNesimoLibroTABBLibrosAux(TABBLibros abbLibros, int n, int &k, TLibro &res){
    if (abbLibros == NULL){
        return;
    }
    obtenerNesimoLibroTABBLibrosAux(abbLibros->Izquierdo,n,k,res);
    k++;
    if (n == k){
        res=abbLibros->libro;
        return;
    } 
    obtenerNesimoLibroTABBLibrosAux(abbLibros->Derecho,n,k,res);
}

TLibro obtenerNesimoLibroTABBLibros(TABBLibros abbLibros, int n){
    int k=0;
    TLibro res = NULL;
    obtenerNesimoLibroTABBLibrosAux(abbLibros,n,k,res);
    return res;
}

void filtradoPGTAux(TABBLibros abbLibros, TABBLibros &filtrado, int genero) {
    if (abbLibros == NULL) {
        return;
    }
    filtradoPGTAux(abbLibros->Izquierdo, filtrado, genero);
    if (idGeneroTLibro(abbLibros->libro) == genero) {
        TLibro copiaLibro = copiarTLibro(abbLibros->libro);
        insertarLibroTABBLibros(filtrado, copiaLibro);
    }
    filtradoPGTAux(abbLibros->Derecho, filtrado, genero);
}

TABBLibros filtradoPorGeneroTABBLibros(TABBLibros abbLibros, int genero) {
    TABBLibros filtrado = crearTABBLibrosVacio();
    filtradoPGTAux(abbLibros, filtrado, genero);
    return filtrado;
}