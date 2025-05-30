// Nombre: Javier, Apellidos: Mora Ortiz-Villajos, Titulación: GIADE
// Email: javier23@correo.ugr.es, DNI: 20619222K

// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Mallas indexadas creadas por revolución de un perfil (implementación). Clase 'MallaRevol' y derivadas.
// ** Copyright (C) 2016-2024 Carlos Ureña
// **
// ** Implementación de las clases 
// **    + MallaRevol: malla indexada de triángulos obtenida por 
// **      revolución de un perfil (derivada de MallaInd)
// **    + MallaRevolPLY: malla indexada de triángulos, obtenida 
// **      por revolución de un perfil leído de un PLY (derivada de MallaRevol)
// **    + algunas clases derivadas de MallaRevol
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

#include "ig-aux.h"
#include "lector-ply.h"
#include "malla-revol.h"

using namespace std ;

// *****************************************************************************




// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaRevol::inicializar
(
   const std::vector<glm::vec3> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias  // número de copias del perfil
)
{
   using namespace glm ;

   //Práctica 4:

   //Cálculo de normales de las aristas
   vector<glm::vec3> nor_ari_per(0);
   for(unsigned int i=0; i<perfil.size()-1; ++i) {
      glm::vec3 nor_ari = perfil[i+1] - perfil[i];
      nor_ari = glm::vec3(nor_ari.y, -nor_ari.x ,nor_ari.z);
      nor_ari = normalize(nor_ari);
      nor_ari_per.push_back(nor_ari);
   }

   //Calcular normales de los vertices

   vector<glm::vec3> nor_vert_per(0);
   nor_vert_per.push_back(nor_ari_per[0]);
   for(unsigned int i=1; i<nor_ari_per.size()-1; ++i){
      glm::vec3 nor_vert = nor_ari_per[i] + nor_ari_per[i-1];
      nor_vert = normalize(nor_ari_per[i] + nor_ari_per[i-1]);
      nor_vert_per.push_back(nor_vert);
   }
   nor_vert_per.push_back(nor_ari_per[nor_ari_per.size()-1]);



   //Calcular coordenadas de textura

   vector<float> d;
   vector<float> t;

   //d:
   for(unsigned int i = 0; i < perfil.size() - 1; ++i)
      d.push_back(length(perfil[i+1] - perfil[i]));

   //normalizador:
   float sum = 0.0f;
   for(uint i = 0; i < d.size(); ++i)
      sum += d[i];

   //Iniciamos t (simplificar algoritmo)
   for(unsigned int i = 0; i < perfil.size(); ++i)
      t.push_back(0.0);

   //t:
   for(unsigned int i = 0; i < perfil.size(); ++i) {
      for(unsigned int j = 0; j < i; ++j)
         t[i] += d[j];

      t[i] = t[i]/sum*1.0f;
   }
   
   // COMPLETAR: práctica 2: implementar algoritmo de creación de malla de revolución
   //
   // Escribir el algoritmo de creación de una malla indexada por revolución de un 
   // perfil, según se describe en el guion de prácticas.
   //
   // ............................... 

// Tabla de vértices
   
   vertices.clear();

   //Tabla de vértices y de normales + las coordenads de textura
   for (unsigned int i=0; i<num_copias; ++i){
      float angulo = (2*M_PI*i)/(num_copias-1);
      for (float j=0; j<perfil.size(); ++j){
         float radio = perfil[j].x;
         float radio_nor = nor_vert_per[j].x;
         vertices.push_back(glm::vec3{radio *cos(angulo), perfil[j].y, -1*radio *sin(angulo)});
         nor_ver.push_back(glm::vec3{radio_nor *cos(angulo), nor_vert_per[j].y, -1*radio_nor *sin(angulo)});
         cc_tt_ver.push_back(glm::vec2{i/(num_copias-1.0),1-t[j]});
      }
   }

   unsigned int k;
   triangulos.clear();
   //Tabla de triángulos
   for(unsigned int i=0 ; i<num_copias-1; i++){
      for(unsigned int j=0 ; j<perfil.size()-1; j++){
         k=i*perfil.size() + j;
         triangulos.push_back({k, k + perfil.size(), k + perfil.size() + 1});
         triangulos.push_back({k, k + perfil.size() + 1, k + 1});
      }
   }



}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY

MallaRevolPLY::MallaRevolPLY
(
   const std::string & nombre_arch,
   const unsigned      nperfiles
)
{
   ponerNombre( std::string("malla por revolución del perfil en '"+ nombre_arch + "'" ));
   // COMPLETAR: práctica 2: crear la malla de revolución
   // Leer los vértice del perfil desde un PLY, después llamar a 'inicializar'
   // ...........................
   std::vector<glm::vec3> aux;
   LeerVerticesPLY(nombre_arch, aux);
   inicializar(aux, nperfiles);

}

//P2:

Cilindro::Cilindro(const int num_verts_per, const unsigned nperfiles){
   
   //ponerNombre("Cilindro");
   vector<glm::vec3> vertices_perfil;
   double distancia = +1.0 / num_verts_per;
   
   vertices_perfil.push_back({+1.0, 0.0, 0.0});
   for(unsigned int i=1; i<=num_verts_per; i++){
      vertices_perfil.push_back({+1.0, vertices_perfil[i-1][Y] + distancia, 0.0});
   }
   inicializar(vertices_perfil,nperfiles);
}


Cono::Cono(const int num_verts_per, const unsigned nperfiles){
   
   //ponerNombre("Cono");
   vector<glm::vec3> vertices_perfil;
   double distancia = +1.0 / num_verts_per;

   vertices_perfil.push_back({0,+1.0,0}); //Primer vértice

   for(unsigned int i=1; i<=num_verts_per;i++){
      vertices_perfil.push_back({vertices_perfil[i-1][X] + distancia, vertices_perfil[i-1][Y] - distancia, 0});
   }

   inicializar(vertices_perfil,nperfiles);
}


Esfera::Esfera(const int num_verts_per, const unsigned nperfiles){
   
   //ponerNombre("Esfera");
   vector<glm::vec3> vertices_perfil;
   float distancia = M_PI/num_verts_per;

   for(unsigned int i=0; i<=num_verts_per;i++){
      vertices_perfil.push_back({ cos(float(-M_PI/2) + i*distancia), sin(float(-M_PI/2)+ i*distancia), 0});
   }

   inicializar(vertices_perfil,nperfiles);

}



