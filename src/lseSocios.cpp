
#include "../include/lseSocios.h"
#include "../include/socio.h"

struct rep_lseSocios {
	TSocio socio;
	TLSESocios sig;
};

TLSESocios crearTLSESociosVacia(){
    return NULL;
}

bool esVaciaTLSESocios(TLSESocios lseSocios){
	if (lseSocios == NULL){
		return true;
	}
	return false;
}

void imprimirTLSESocios(TLSESocios lseSocios){
	printf("Lista de Socios:\n");
	while (lseSocios != NULL){
		imprimirTSocio(lseSocios->socio);
		lseSocios=lseSocios->sig;
	}
}

void liberarTLSESocios(TLSESocios &lseSocios) {
    TLSESocios aBorrar;
    while (lseSocios != NULL) {
        aBorrar = lseSocios; 
        lseSocios = lseSocios->sig; 
        liberarTSocio(aBorrar->socio); 
        delete aBorrar; 
    }
    lseSocios = NULL; 
}
void insertarTLSESocios(TLSESocios &lseSocios, TSocio socio) {
    TLSESocios nuevoNodo = new rep_lseSocios; 
    
    nuevoNodo->socio = socio;
    nuevoNodo->sig = NULL;

    if (lseSocios == NULL || compararTFechas(fechaAltaTSocio(socio), fechaAltaTSocio(lseSocios->socio)) < 0) {
        nuevoNodo->sig = lseSocios;
        lseSocios = nuevoNodo;
    } else {
        TLSESocios actual = lseSocios;
        while (actual->sig != NULL && compararTFechas(fechaAltaTSocio(socio), fechaAltaTSocio(actual->sig->socio)) >= 0) {
            actual = actual->sig;
        }
        nuevoNodo->sig = actual->sig;
        actual->sig = nuevoNodo;
    }
}

bool existeSocioTLSESocios(TLSESocios lseSocios, int ci){
	while (lseSocios != NULL){
		if (ciTSocio(lseSocios->socio)==ci){
			return true;
		}
		lseSocios=lseSocios->sig;
	}
	return false;
}

TSocio obtenerSocioTLSESocios(TLSESocios lseSocios, int ci){
    while (lseSocios != NULL){
		if (ciTSocio(lseSocios->socio)==ci){
			return lseSocios->socio;
		}
		lseSocios=lseSocios->sig;
	}
	return lseSocios->socio;
}

TSocio obtenerNesimoTLSESocios(TLSESocios lseSocios, int n){
	for(int i=1;i<n;i++){
		lseSocios=lseSocios->sig;
	}
	return lseSocios->socio;
}

nat cantidadTLSESocios(TLSESocios lseSocios){
	nat contador=0;
	while (lseSocios!=NULL){
		contador++;
		lseSocios=lseSocios->sig;
	}
	return contador;
}

void removerSocioTLSESocios(TLSESocios &lseSocios, int ci) {

    if (ciTSocio(lseSocios->socio) == ci) {
        TLSESocios aBorrar = lseSocios;
        lseSocios = lseSocios->sig;
        liberarTSocio(aBorrar->socio); 
        delete aBorrar; 
        return;
    }
	TLSESocios anterior = lseSocios;
    TLSESocios actual = lseSocios->sig;
    while (actual != NULL && ciTSocio(actual->socio) != ci) {
        anterior = actual;
        actual = actual->sig;
    }
    if (actual != NULL) {
        anterior->sig = actual->sig;
        liberarTSocio(actual->socio); 
        delete actual; 
    }
}