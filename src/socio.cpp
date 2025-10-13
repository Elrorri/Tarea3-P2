#include "../include/socio.h"
#include "../include/fecha.h"

struct rep_socio {
    int ci;
    char nombre[MAX_NOMBRE_SOCIO];
    char apellido[MAX_APELLIDO_SOCIO];
    TFecha fechaAlta;
    int generosFavoritos[MAX_GENEROS_FAVORITOS];
    int cantidadGenerosFavoritos; 
};
 
TSocio crearTSocio(int ci, const char nombre[MAX_NOMBRE_SOCIO], const char apellido[MAX_APELLIDO_SOCIO], nat diaAlta, nat mesAlta, nat anioAlta){
    TSocio nuevoSocio = new rep_socio;
    nuevoSocio->ci = ci;
    strncpy(nuevoSocio->nombre, nombre, MAX_NOMBRE_SOCIO);
    strncpy(nuevoSocio->apellido, apellido, MAX_APELLIDO_SOCIO);
    nuevoSocio->fechaAlta=crearTFecha(diaAlta,mesAlta,anioAlta);
    nuevoSocio->cantidadGenerosFavoritos = 0;
    
return nuevoSocio;
}

void imprimirTSocio(TSocio socio){
    printf("Socio %d:", socio->ci);
    printf(" %s ", socio->nombre);
    printf("%s\n", socio->apellido);
    printf("Fecha de alta: ");
    imprimirTFecha(socio->fechaAlta);
    printf("Géneros favoritos: ");
    for (int i = 0; i < socio->cantidadGenerosFavoritos ; i++) {
        printf("%d ", socio->generosFavoritos[i]);
    }
    printf("\n");
}


void liberarTSocio(TSocio &socio){
    liberarTFecha(socio->fechaAlta);
    delete socio;
    socio = NULL;
}

int ciTSocio(TSocio socio){
    int ci = socio->ci;
    return ci;
}

char* nombreTSocio(TSocio socio){
    char* nombre=socio->nombre;
    return nombre;
}

char* apellidoTSocio(TSocio socio){
    char* apellido=socio->apellido;
    return apellido;
}

TFecha fechaAltaTSocio(TSocio socio){
    TFecha alta = socio->fechaAlta;
    return alta;
}

void agregarGeneroFavoritoTSocio(TSocio &socio, int idGenero){
        socio->generosFavoritos[socio->cantidadGenerosFavoritos]=idGenero;
        socio->cantidadGenerosFavoritos++;
}

bool tieneGeneroFavoritoTSocio(TSocio socio, int idGenero){
    int i=0;
    bool esta=false;
    if(socio->cantidadGenerosFavoritos != 0){
        while (i < socio->cantidadGenerosFavoritos && esta != true){
            if (socio->generosFavoritos[i]==idGenero){
                esta=true;
            }    
            i++;
        }
    }
    return esta;
}

int cantidadGenerosFavoritosTSocio(TSocio socio){
    int cuenta=socio->cantidadGenerosFavoritos;
    return cuenta;
}

TFecha obtenerFecha(TSocio socio){
TFecha fecha=socio->fechaAlta;
return fecha;
}

TSocio copiarTSocio(TSocio socio){
    TSocio copia;
    copia=crearTSocio(socio->ci,socio->nombre,socio->apellido,01,01,2000);
    liberarTFecha(copia->fechaAlta); 
    copia->fechaAlta = copiarTFecha(socio->fechaAlta);
    copia->cantidadGenerosFavoritos=socio->cantidadGenerosFavoritos;
    for (int i=0;i<socio->cantidadGenerosFavoritos;i++){
        copia->generosFavoritos[i]=socio->generosFavoritos[i];
    }
    return copia;
}