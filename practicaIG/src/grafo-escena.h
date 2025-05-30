// Nombre: Javier, Apellidos: Mora Ortiz-Villajos, Titulación: GIADE
// Email: javier23@correo.ugr.es, DNI: 20619222K

// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Gestión de grafos de escena (declaraciones).  Clase 'NodoGrafoEscena' y relacionadas.
// ** Copyright (C) 2016-2024 Carlos Ureña
// **
// ** Declaraciones de: 
// **     + Clase 'NodoGrafoEscena' (derivada de 'Objeto3D')
// **     + Clase 'EntradaNGE' (una entrada de un nodo del grafo de escena)
// **     + Tipo enumerado 'TipoEntNGE' (tipo de entradas del nodo del grafo de escena)
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************

#ifndef GRAFO_ESCENA_HPP
#define GRAFO_ESCENA_HPP

//#include <tup_mat.h>   

#include "objeto3d.h"
#include "malla-ind.h" // para poder usar clase MallaInd
#include "materiales-luces.h"
#include "malla-revol.h"
#include "camara.h"

//using namespace tup_mat ;

// *********************************************************************
// declaración adelantada de estructura para un nodo del grafo de escena

class NodoGrafoEscena ;

// *********************************************************************
// tipo enumerado con los tipos de entradas del nodo del grafo de escena

enum class TipoEntNGE { objeto, transformacion, material, noInicializado } ;

// *********************************************************************
// Entrada del nodo del Grafo de Escena

struct EntradaNGE
{
   TipoEntNGE tipo = TipoEntNGE::noInicializado ;   // objeto, transformacion, material
   union
   {  Objeto3D  * objeto = nullptr ;  // ptr. a un objeto (no propietario)
      glm::mat4 * matriz   ;  // ptr. a matriz 4x4 transf. (propietario)
      Material  * material ; // ptr. a material (no propietario)
   } ;
   // constructores (uno por tipo)
   EntradaNGE() = delete ; // prohibe constructor sin parámetros
   EntradaNGE( Objeto3D        * pObjeto   );      // (copia solo puntero)
   EntradaNGE( const glm::mat4 & pMatriz   ); // (crea copia en el heap)
   EntradaNGE( Material        * pMaterial );    // (copia solo puntero)
   ~EntradaNGE() ;
} ;

// *********************************************************************
// Nodo del grafo de escena: es un objeto 3D parametrizado, que contiene una lista de entradas

class NodoGrafoEscena : public Objeto3D
{
   protected:
   // COMPLETAR: práctica 3: definir variables y métodos privados del nodo
   // .......
   std::vector<EntradaNGE> entradas;
   bool centro_calculado = false;
   int fila,  n_esfera;

   public:

   NodoGrafoEscena() ;

   // visualiza usando OpenGL
   virtual void visualizarGL(  ) ;

   // visualizar pura y simplemente la geometría, sin colores, normales, coord. text. etc...
   // (se supone que el estado de OpenGL está fijado antes de esta llamada de alguna forma adecuada)
   virtual void visualizarGeomGL(  ) ;

   // visualizar las normales de los objetos del nodo
   virtual void visualizarNormalesGL () ;

   // visualizar el objeto en 'modo seleccion', es decir, sin iluminación y con los colores 
   // basados en los identificadores de los objetos
   virtual void visualizarModoSeleccionGL()  ;

   // añadir una entrada al final, hace copia de la entrada
   // devuelve indice de la entrada dentro del vector de entradas
   unsigned agregar( const EntradaNGE & entrada );

   // construir una entrada y añadirla (al final)
   unsigned agregar( Objeto3D *        pObjeto ); // objeto (copia solo puntero)
   unsigned agregar( const glm::mat4 & pMatriz ); // matriz (copia objeto)
   unsigned agregar( Material *        pMaterial ); // material (copia solo puntero)

   // devuelve el puntero a la matriz en la i-ésima entrada
   glm::mat4 * leerPtrMatriz( unsigned iEnt );

   // método para buscar un objeto con un identificador
   virtual bool buscarObjeto( const int ident_busc, const glm::mat4 & mmodelado,
                    Objeto3D ** objeto, glm::vec3 & centro_wc )  ;

   // si 'centro_calculado' es 'false', recalcula el centro usando los centros
   // de los hijos (el punto medio de la caja englobante de los centros de hijos)
   virtual void calcularCentroOC() ;


} ;

// *********************************************************************


//P3 ejercicios adicionales:

class GrafoEstrellaX : public NodoGrafoEscena{

   private:
      const unsigned n_parametros = 1;
      const float parametro = 180+180; // a + b  = (Vmin+Vmax)/2 + (Vmax-Vmin)/2, oscila entre Vmax y Vmin
      glm::mat4 * matriz_1 = nullptr; 

   public:
      GrafoEstrellaX(unsigned n);
      void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
      void giro(const float grado);
      unsigned leerNumParametros() const;

};

class GrafoCubos : public NodoGrafoEscena{
   
   private:
      const float parametro = 360;
      const unsigned n_parametros = 1;
      glm::mat4 * matriz_1 = nullptr;

   public:
      GrafoCubos();
      void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
      unsigned leerNumParametros() const;
      void giro(const float grado);

};

//P4:

class NodoCubo24: public NodoGrafoEscena{
   public:
      NodoCubo24();
};


class NodoDiscoP4: public NodoGrafoEscena{
   public:
      NodoDiscoP4(int ejerc);
};

//Ejercicios adicionales P5

class GrafoEsferasP5: public NodoGrafoEscena{
   public:
      GrafoEsferasP5();
};

class MiEsferaE1: public NodoGrafoEscena{
   public:
      MiEsferaE1(unsigned n_esfera_fila, unsigned num_fila);
      bool cuandoClick(const glm::vec3 &centro_wc);
};

class GrafoEsferasP5_2: public NodoGrafoEscena{
   public:
      GrafoEsferasP5_2();
};

class MiEsferaE2: public NodoGrafoEscena{
   public:
      MiEsferaE2();
      bool cuandoClick(const glm::vec3 &centro_wc);
};

#endif // GRAFO_ESCENA_HPP


