// Nombre: Javier, Apellidos: Mora Ortiz-Villajos, Titulación: GIADE
// Email: javier23@correo.ugr.es, DNI: 20619222K

#ifndef EXAMEN_EC_P123_HPP
#define EXAMEN_EC_P123_HPP
#include "malla-ind.h"
#include "grafo-escena.h"

//Ejercicio 1: malla indexada de etriangulos

class Ejercicio1 : public MallaInd{
   public:
      Ejercicio1();
};

//Ejercicio 2: n réplicas del ejercicio anterior n>=1
class Ejercicio2 : public MallaInd{
   public:
      Ejercicio2(unsigned n);
};


//Ejercicio 3: dos cubos con ancho y altura dados, el superior rota, y el inferior se acorta y alarga en Y (manteniendo el ancho)
class Ejercicio3 : public NodoGrafoEscena{
    private:
        const float grado_libertad1 = 90;
        const float grado_libertad2 = 4;
        const unsigned n_parametros = 2;
        glm::mat4 * matriz_1 = nullptr;
        glm::mat4 * matriz_2 = nullptr;
    public:
        Ejercicio3(unsigned ancho, unsigned altura);
        void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
        unsigned leerNumParametros() const;
        void giro(const float grado);
        void acortar(const float grado);
};

#endif
