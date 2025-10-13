#include "../include/ldePrestamos.h"

struct nodoDoble{
     TPrestamo prestamo;
     nodoDoble* siguiente;
     nodoDoble* anterior;
};

struct rep_ldePrestamos {
    nodoDoble* inicio;
    nodoDoble* final;
};

TLDEPrestamos crearTLDEPrestamosVacia(){
    TLDEPrestamos nuevaLista = new rep_ldePrestamos;
    nuevaLista->inicio = NULL;
    nuevaLista->final = NULL;
    return nuevaLista;
}

    void insertarTLDEPrestamos(TLDEPrestamos &ldePrestamos, TPrestamo prestamo) {
    nodoDoble* nuevoNodo = new nodoDoble;
    nuevoNodo->prestamo = prestamo;
    nuevoNodo->siguiente = NULL;
    nuevoNodo->anterior = NULL;

    if (ldePrestamos->inicio == NULL) {
        ldePrestamos->inicio = nuevoNodo;
        ldePrestamos->final = nuevoNodo;
    }
    else if (compararTFechas(fechaRetiroTPrestamo(prestamo), fechaRetiroTPrestamo(ldePrestamos->inicio->prestamo)) < 0){
        nuevoNodo->siguiente = ldePrestamos->inicio;
        ldePrestamos->inicio->anterior = nuevoNodo;
        ldePrestamos->inicio = nuevoNodo;
    } 
    else {
        nodoDoble* actual = ldePrestamos->inicio;
        while (actual->siguiente != NULL && compararTFechas(fechaRetiroTPrestamo(prestamo), fechaRetiroTPrestamo(actual->siguiente->prestamo)) >= 0){
            actual = actual->siguiente;
        }

        nuevoNodo->siguiente = actual->siguiente;
        nuevoNodo->anterior = actual;
        
        if (actual->siguiente != NULL) {
            actual->siguiente->anterior = nuevoNodo;
        } else {
            ldePrestamos->final = nuevoNodo;
        }
        actual->siguiente = nuevoNodo;
    }
}

void liberarTLDEPrestamos(TLDEPrestamos &ldePrestamos){
    nodoDoble* aBorrar;
    while (ldePrestamos->inicio != NULL) {
        aBorrar = ldePrestamos->inicio; 
        ldePrestamos->inicio = ldePrestamos->inicio->siguiente; 
        liberarTPrestamo(aBorrar->prestamo); 
        delete aBorrar; 
    }
    ldePrestamos->final = NULL; 
    delete ldePrestamos;
    ldePrestamos = NULL;
}

void liberarTLDEPrestamosSoloEstructura(TLDEPrestamos &ldePrestamos){
    delete ldePrestamos;
    ldePrestamos = NULL;
}

void imprimirTLDEPrestamos(TLDEPrestamos ldePrestamos){
    printf ("LDE Préstamos:\n");
    nodoDoble* actual;
    actual = ldePrestamos->inicio;
    while (actual != NULL) {
        imprimirTPrestamo(actual->prestamo);
        actual = actual->siguiente;
    }
}

void imprimirInvertidoTLDEPrestamos(TLDEPrestamos ldePrestamos){
    printf ("LDE Préstamos:\n");
    nodoDoble* actual;
    actual = ldePrestamos->final;
    while (actual != NULL) {
        imprimirTPrestamo(actual->prestamo);
        actual = actual->anterior;
    }
}

nat cantidadTLDEPrestamos(TLDEPrestamos ldePrestamos){
    nat contador=0;
    nodoDoble* actual;
    actual = ldePrestamos->inicio;
    while (actual != NULL) {
        contador++;
        actual = actual->siguiente;
    }
    return contador;
}

TPrestamo obtenerPrimeroTLDEPrestamos(TLDEPrestamos ldePrestamos){
    if (ldePrestamos->inicio != NULL) {
        return ldePrestamos->inicio->prestamo;
    }
    return NULL;
}

TPrestamo obtenerUltimoTLDEPrestamos(TLDEPrestamos ldePrestamos){
    if (ldePrestamos->final != NULL) {
        return ldePrestamos->final->prestamo;
    }
    return NULL;  
}

TPrestamo obtenerNesimoTLDEPrestamos(TLDEPrestamos &ldePrestamos, int n){
    nodoDoble* actual = ldePrestamos->inicio;
    for(int i=1; i<n; i++){
        actual = actual->siguiente;
    }
    return actual->prestamo;
}

// criterio = 0 -> prestamos retornados
// criterio = 1 -> prestamos no retornados
TLDEPrestamos filtrarPrestamosTLDEPrestamos(TLDEPrestamos &ldePrestamos, int criterio){
    TLDEPrestamos PrestamosFiltrados = new rep_ldePrestamos;
    PrestamosFiltrados->inicio = NULL;
    PrestamosFiltrados->final = NULL;
    nodoDoble* actual = ldePrestamos->inicio;
    nodoDoble* ultimoFiltrado = NULL;
    bool Retornado;

    if (criterio == 0) {
        Retornado = true;
    } else if (criterio == 1) {
        Retornado = false;
    }

    while (actual != NULL) {
        if (fueRetornadoTPrestamo(actual->prestamo) == Retornado) {
            nodoDoble* nuevoNodo = new nodoDoble;
            nuevoNodo->prestamo = copiarTPrestamo(actual->prestamo);
            nuevoNodo->siguiente = NULL;
            nuevoNodo->anterior = ultimoFiltrado;

            if (ultimoFiltrado == NULL) {
                PrestamosFiltrados->inicio = nuevoNodo;
            } else {
                ultimoFiltrado->siguiente = nuevoNodo;
            }
            PrestamosFiltrados->final = nuevoNodo;
            ultimoFiltrado = nuevoNodo;
        }
        actual = actual->siguiente;
    }
    return PrestamosFiltrados;
}


