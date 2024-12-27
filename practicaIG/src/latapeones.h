// Nombre: Javier, Apellidos: Mora Ortiz-Villajos, Titulación:  GIADE.
// email: javier23@correo.ugr.es, DNI o pasaporte: 20619222K

#ifndef LATAPEONES_H
#define LATAPEONES_H

#include "grafo-escena.h"

using namespace std;

class Lata : public NodoGrafoEscena {
    public:
        Lata(string textura);
};

class LataPeones : public NodoGrafoEscena {
    public:
        LataPeones();
};

class VariasLatasPeones : public NodoGrafoEscena {
    public:
        VariasLatasPeones();
};

#endif // LATAPEONES_H