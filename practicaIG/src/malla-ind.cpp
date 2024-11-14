// Nombre: Javier, Apellidos: Mora Ortiz-Villajos, Titulación: GIADE
// Email: javier23@correo.ugr.es, DNI: 20619222K

// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Mallas indexadas (implementación). Clase 'MallaInd' y derivadas.
// ** Copyright (C) 2016-2024 Carlos Ureña
// **
// ** Implementación de las clases 
// **        + MallaInd: malla indexada de triángulos (derivada de Objeto3D)
// **        + MallaPLY: malla indexada de triángulos, leída de un PLY (derivada de MallaInd)
// **        + algunas clases derivadas de MallaInd.
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
#include "aplicacion-ig.h"
#include "malla-ind.h"   // declaración de 'ContextoVis'
#include "lector-ply.h"
#include "seleccion.h"   // para 'ColorDesdeIdent' 


// *****************************************************************************
// funciones auxiliares

// *****************************************************************************
// métodos de la clase MallaInd.

MallaInd::MallaInd()
{
   // nombre por defecto
   ponerNombre("malla indexada, anónima");
}
// -----------------------------------------------------------------------------

MallaInd::MallaInd( const std::string & nombreIni )
{
   // 'identificador' puesto a 0 por defecto, 'centro_oc' puesto a (0,0,0)
   ponerNombre(nombreIni) ;
}

//-----------------------------------------------------------------------------
// calcula la tabla de normales de triángulos una sola vez, si no estaba calculada

void MallaInd::calcularNormalesTriangulos()
{

   
   // si ya está creada la tabla de normales de triángulos, no es necesario volver a crearla
   const unsigned nt = triangulos.size() ;
   assert( 1 <= nt );
   if ( 0 < nor_tri.size() )
   {
      assert( nt == nor_tri.size() );
      return ;
   }

   // COMPLETAR: Práctica 4: creación de la tabla de normales de triángulos
   // ....

}


// -----------------------------------------------------------------------------
// calcula las dos tablas de normales

void MallaInd::calcularNormales()
{
   using namespace glm ;
   // COMPLETAR: en la práctica 4: calculo de las normales de la malla
   // se debe invocar en primer lugar 'calcularNormalesTriangulos'
   // .......


}


// --------------------------------------------------------------------------------------------

void MallaInd::visualizarGL( )
{
   // comprobar algunas precondiciones básicas
   using namespace std ;
   assert( aplicacionIG != nullptr );
   Cauce * cauce = aplicacionIG->cauce ; assert( cauce != nullptr );
   CError();

   // si la malla no vértices o no tiene triángulos, imprimir advertencia y salir.
   if ( triangulos.size() == 0 || vertices.size() == 0 )
   {  cout << "advertencia: intentando dibujar malla vacía '" << leerNombre() << "'" << endl << flush ;
      return ;
   }

   // COMPLETAR: práctica 1: cambiar color del cauce
   //
   // Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
   //    - hacer push del color actual del cauce
   //    - fijar el color en el cauce usando el color del objeto (se lee con 'leerColor()')
   if(tieneColor()){
         cauce->pushColor();
         cauce->fijarColor(leerColor());
   }

   // COMPLETAR: práctica 1: crear el descriptor de VAO, si no está creado
   //  Si el puntero 'dvao' es nulo, crear el descriptor de VAO
   //   * en primer lugar se crea el descriptor de VAO, con su constructor 
   //     (se le pasa como parámetro la tabla de posiciones y el número de atributos del cauce). 
   //   * se añade el descriptor de VBO con la tabla de índices (la tabla de triángulos),
   //   * finalmente se añaden al VAO los descriptores VBOs con tablas de atributos 
   //     que no estén vacías
   //  Si el VAO ya está creado, (dvao no nulo), no hay que hacer nada.
   if(dvao == nullptr){
      
      DescrVBOAtribs *descr_VBO_pos = new DescrVBOAtribs(ind_atrib_posiciones, refVertices()); 

      dvao = new DescrVAO(numero_atributos_cauce, descr_VBO_pos);

      DescrVBOInds *dvbo_ind = new DescrVBOInds(refTriangulos());
      dvao->agregar(dvbo_ind);
      
      if(col_ver.size() > 0){
         DescrVBOAtribs *dvbo_col_vert = new DescrVBOAtribs(ind_atrib_colores, col_ver);
         dvao->agregar(dvbo_col_vert);
      }
      if(nor_ver.size() > 0){
         DescrVBOAtribs *dvbo_nor_ver = new DescrVBOAtribs(ind_atrib_normales, nor_ver);
         dvao->agregar(dvbo_nor_ver);
      }
      if(cc_tt_ver.size() > 0){
         DescrVBOAtribs *dvbo_cc_tt_ver = new DescrVBOAtribs(ind_atrib_coord_text, cc_tt_ver);
         dvao->agregar(dvbo_cc_tt_ver);
      }
   }


   // COMPLETAR: práctica 1: visualizar el VAO usando el método 'draw' de 'DescrVAO'
   dvao->draw(GL_TRIANGLES);

   // COMPLETAR: práctica 1: restaurar color anterior del cauce 
   //
   // Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
   //    - hacer 'pop' del color actual del cauce
   if(tieneColor())
      cauce->popColor();

}


// -----------------------------------------------------------------------------
// Visualizar el objeto con OpenGL
// usa las tablas de normales, colores y coordenadas de textura, si no están vacías.
      
void MallaInd::visualizarGeomGL( )
{
   // Comprobar que el descriptor de VAO ya está creado
   // (es decir, este método únicamente se podrá invocar después de que 
   // se haya llamado a 'visualizaGL')
   
   assert( dvao != nullptr );

   // COMPLETAR: práctica 1: visualizar únicamente la geometría del objeto 
   // 
   //    1. Desactivar todas las tablas de atributos del VAO (que no estén vacías)
         if(col_ver.size() > 0)
            dvao->habilitarAtrib(ind_atrib_colores ,false);
         if(nor_ver.size() > 0)
            dvao->habilitarAtrib(ind_atrib_normales, false);
         if(nor_tri.size() > 0)
            dvao->habilitarAtrib(ind_atrib_normales, false);
         if(cc_tt_ver.size() > 0)
            dvao->habilitarAtrib(ind_atrib_coord_text, false);
   //    2. Dibujar la malla (únicamente visualizará los triángulos), se usa el método 'draw' del VAO (dvao)
         dvao->draw(GL_TRIANGLES);

   //    3. Volver a activar todos los atributos para los cuales la tabla no esté vacía
         if(col_ver.size() > 0)
            dvao->habilitarAtrib(ind_atrib_colores ,true);
         if(nor_ver.size() > 0)
            dvao->habilitarAtrib(ind_atrib_normales, true);
         if(nor_tri.size() > 0)
            dvao->habilitarAtrib(ind_atrib_normales, true);
         if(cc_tt_ver.size() > 0)
            dvao->habilitarAtrib(ind_atrib_coord_text, true);
   
   // ....

}

// -----------------------------------------------------------------------------
// Visualizar las normales del objeto, si no tiene tabla de normales imprime 
// advertencia y no hace nada.

void MallaInd::visualizarNormalesGL(  )
{
   using namespace std ;
   assert( aplicacionIG != nullptr );
   Cauce * cauce = aplicacionIG->cauce ; assert( cauce != nullptr );

   if ( nor_ver.size() == 0 )
   {
      cout << "Advertencia: intentando dibujar normales de una malla que no tiene tabla (" << leerNombre() << ")." << endl ;
      return ;
   }  

   if( nor_ver.size() != vertices.size() )
   {
      cout << "Error visu. normales: tabla de normales no vacía y de tamaño distinto a la de vértices." << endl ;
      cout << "Nombre del objeto        : " << leerNombre() << endl ;
      cout << "Tamaño tabla vértices    : " << vertices.size() << endl ;
      cout << "Tamaño tabla de normales : " << nor_ver.size() << endl ;
      exit(1);
   }
   CError();

   // COMPLETAR: práctica 4: visualizar las normales del objeto MallaInd
   // 
   // *1* Si el puntero al descriptor de VAO de normales ('dvao_normales') es nulo, 
   //    debemos de crear dicho descriptor, con estos pasos:
   //
   //       * Para cada posición 'v_i' de un vértice en el vector 'vertices':
   //             - Leer la correspondiente normal 'n_i' del vector de normales ('nor_ver').
   //             - Añadir 'v_i' al vector 'segmentos_normales'.
   //             - Añadir 'v_i+a*n_i' al vector 'segmentos_normales'.
   //
   //       * Crear el objeto descriptor del VAO de normales, para ello se usa el vector 
   //          'segmentos_normales' y se tiene en cuenta que esa descriptor únicamente gestiona 
   //          una tabla de atributos de vértices (la de posiciones, ya que las otras no se 
   //          necesitan).
   // 
   // *2* Visualizar el VAO de normales, usando el método 'draw' del descriptor, con el 
   //       tipo de primitiva 'GL_LINES'.

   //  ..........

}

// -----------------------------------------------------------------------------
// visualizar el objeto en 'modo seleccion', es decir, sin iluminación y con los colores 
// basados en los identificadores de los objetos
void MallaInd::visualizarModoSeleccionGL() 
{

   using namespace std ;
   assert( aplicacionIG != nullptr );
   Cauce * cauce = aplicacionIG->cauce ; assert( cauce != nullptr );

   // COMPLETAR: práctica 5: visualizar la malla en modo selección 
   //
   // Se debe escribir código para visualizar únicamente la geometría, pero usando el color 
   // obtenido a partir del identificador. El código da estos pasos:
   // 
   // 1. Leer el identificador del objeto (con 'leerIdentificador'). Si el objeto tiene 
   //    identificador (es decir, si su identificador no es -1)
   //       + Hacer push del color del cauce, con 'pushColor'.
   //       + Fijar el color del cauce (con 'fijarColor') usando un color obtenido a 
   //         partir del identificador (con 'ColorDesdeIdent'). 
   // 2. Invocar 'visualizarGeomGL' para visualizar la geometría.
   // 3. Si tiene identificador: hacer pop del color, con 'popColor'.
   //

}


// ****************************************************************************
// Clase 'MallaPLY'

MallaPLY::MallaPLY( const std::string & nombre_arch )
{
   ponerNombre( std::string("malla leída del archivo '") + nombre_arch + "'" );

   // COMPLETAR: práctica 2: leer archivo PLY e inicializar la malla
   // ..........................
   LeerPLY(nombre_arch, vertices, triangulos);

   // COMPLETAR: práctica 4: invocar  a 'calcularNormales' para el cálculo de normales
   // .................

}

// ****************************************************************************
// Clase 'Cubo

Cubo::Cubo()
:  MallaInd( "cubo 8 vértices" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
      } ;



   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

}

//P1:

Tetraedro::Tetraedro() : MallaInd(" Tetraedro 4 vértices "){
   vertices =
      {
         { -0.5, -0.5, +0.2 }, // 0
         { +0.5, -0.5, +0.5 }, // 1
         { -0.0, -0.5, -0.5 }, // 2
         { -0.3, +1.0, -0.0 } // 3
      };

   triangulos = 
      {
         {0,2,3}, 
         {0,3,1}, 
         {0,1,2}, 
         {1,2,3}
      };

   //ponerColor();
   calcularNormales();
}

CuboColores::CuboColores(): MallaInd( "Cubo con colores" ){

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 } // 7
      } ;

   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      };

   col_ver =
   {
      { 0, 0, 0 }, // 0
      { 0, 0, +1.0 }, // 1
      { 0, +1.0, 0 }, // 2
      { 0, +1.0, +1.0 }, // 3
      { +1.0, 0, 0 }, // 4
      { +1.0, 0, +1.0 }, // 5
      { +1.0, +1.0, 0 }, // 6
      { +1.0, +1.0, +1.0 } // 7
   };
}

EstrellaZ::EstrellaZ(unsigned n): MallaInd( " EstrellaZ " ){

   assert(n>1);

   //Vértices:
   vertices.push_back({0.5, 0.5 , 0});
   for(unsigned int i = 0; i < 2*n; i += 2) { 
      vertices.push_back( {cos(i*M_PI/n)/2 + 0.5, sin(i*M_PI/n)/2 + 0.5, 0} );
      vertices.push_back( {cos((i+1)*M_PI/n)/4 + 0.5, sin((i+1)*M_PI/n)/4 + 0.5, 0} );
   }

   //Triángulos:
   for(unsigned int i = 0; i < 2*n; i++) {
      triangulos.push_back( {0, i, i+1} );
   }

   triangulos.push_back( {0, 2*n, 1} );

   //Colores:
   col_ver.push_back( {1, 1, 1} ); //Centro blanco
   for(unsigned int i = 0; i < 2*n; i += 2) {   
      col_ver.push_back( {float(cos(i*M_PI/n)/2 + 0.5), float(sin(i*M_PI/n)/2 + 0.5), 0} );
      col_ver.push_back( {float(cos((i+1)*M_PI/n)/4 + 0.5), float(sin((i+1)*M_PI/n)/4 + 0.5), 0} );
   }

}

CasaX::CasaX(): MallaInd( " CasaX " ){
   
   vertices = {
      {0, 0, 0},
      {1.0, 0, 0},
      {1.0, 0, 0.5},
      {0, 0, 0.5},
      {0, 0.5, 0},
      {1.0, 0.5, 0},
      {1.0, 0.5, 0.5},
      {0, 0.5, 0.5},
      {0, 0.75, 0.25},
      {1.0, 0.75, 0.25}
   };

   triangulos = {
      {0,1,5}, {0,4,5},
      {1,2,6}, {1,6,5},
      {2,3,6}, {6,3,7},
      {0,3,7}, {7,0,4},
      {5,6,9}, {4,7,8},
      {7,6,9}, {7,8,9},
      {8,9,4}, {9,5,4}
   };

   col_ver = {
      {0, 0, 0},
      {1.0, 0, 0},
      {1.0, 0, 0.5},
      {0, 0, 0.5},
      {0, 0.5, 0},
      {1.0, 0.5, 0},
      {1.0, 0.5, 0.5},
      {0, 0.5, 0.5},
      {0, 0.75, 0.25},
      {1.0, 0.75, 0.25}
   };
}

MallaTriangulo::MallaTriangulo(): MallaInd( " MallaTriangulo " ){
   vertices =
      {  {-0.5, 0, 0 },
         {0.5, 0, 0 },  
         {0, sqrt(2), 0 }
      } ;

   triangulos =
      {  
         {0,1,2}
      };
}

MallaCuadrado::MallaCuadrado(): MallaInd( " MallaCuadrado " ){

   vertices =
      {  {-1.0, -1.0, 0}, 
         {-1.0, +1.0, 0},
         {+1.0, -1.0, 0},
         {+1.0, +1.0, 0}
      };

   triangulos =
      {  
         {0,1,2}, {1,2,3}
      };
}

MallaPiramideL::MallaPiramideL(): MallaInd( " MallaPiramideL " ){

      vertices = {
         {0, 0, 0},
         {1, 0, 0},
         {1, 0, 0.5},
         {0.5, 0, 0.5},
         {0.5, 0, 1},
         {0, 0, 1},
         {0.5, 1, 0.5}
      };

      triangulos = {
         {0,1,6}, {1,2,6}, {2,3,6}, {3,4,6}, {4,5,6}, {0,5,6},
         {0,1,5}, {5,4,3}, {3,2,1} //Base
      };
}

// -----------------------------------------------------------------------------------------------

//Ejercicios adicionales P2:

PiramideEstrellaZ::PiramideEstrellaZ(unsigned n): MallaInd( " Piramide Estrella Z" ){

   //Vértices:
   vertices.push_back({0.5, 0.5 , 0}); // base 
   
   for(unsigned int i = 0; i < 2*n; i += 2) {   // Creamos todos los vértices de la estrella de 2 en 2
      vertices.push_back( {float(cos(i*M_PI/n)/2 + 0.5), float(sin(i*M_PI/n)/2 + 0.5), 0} );
      vertices.push_back( {float(cos((i+1)*M_PI/n)/4 + 0.5), float(sin((i+1)*M_PI/n)/4 + 0.5), 0} );
   }

   vertices.push_back({0.5, 0.5 , 0.5 }); //ápice de la pirámide

   //Triángulos:
   for (unsigned int i=0 ; i< 2*n; i++){
      triangulos.push_back( {0, i, i+1}); //Base
   }

   triangulos.push_back( {0, 2*n, 1} );

   for(unsigned int i = 0; i < 2*n; i++) {
      triangulos.push_back( {2*n+1, i, i+1} ); //laterales
   }

   triangulos.push_back( {2*n+1, 2*n, 1} );

   //Colores:
   col_ver.push_back({1, 1, 1});     //(R,G,B) -> (x,y,z)

   for(unsigned int i = 0; i < 2*n; i += 2) {   // Colores de los vértices de la base de la pirámide
      col_ver.push_back( {float(std::cos(i*M_PI/n)/2 + 0.5), float(std::sin(i*M_PI/n)/2 + 0.5), 0} );
      col_ver.push_back( {float(std::cos((i+1)*M_PI/n)/4 + 0.5), float(std::sin((i+1)*M_PI/n)/4 + 0.5), 0} );
   }

   col_ver.push_back( {1, 1, 1} );  // Color de la punta de la pirámide

}


RejillaY::RejillaY(unsigned n, unsigned m): MallaInd( " Rejilla Y " ){
    
   
    //Vértices:
   float distancia_x = 1.0/(n-1);
   float distancia_z = 1.0/(m-1);
   
   for(unsigned i=0; i<n; i++){
      for(unsigned j=0; j<m; j++){
         vertices.push_back({ i*distancia_x, 0, j*distancia_z });
      }
   }

    //Triángulos:
   int total = (n-1)*(m-1);
   for(int i=0; i< n-1; i++){
       for(int j=0; j< m-1; j++){
         triangulos.push_back( {m*i+j, m*i+(j+1), m*(i+1)+j} );
         triangulos.push_back( { m*i+(j+1), m*(i+1)+j, m*(i+1)+(j+1)} );
       }
   }

    //Colores:

   for(unsigned i=0; i<n; i++){
      for(unsigned j=0; j<m; j++){
         col_ver.push_back({ i*distancia_x, 0, j*distancia_z });
      }
   }
   
}


MallaTorre::MallaTorre(unsigned n): MallaInd( " Malla Torre " ){

   //4(n+1) vértices
   //8n triangulos
   //n secciones (plantas)

   //Vértices
   for(unsigned i=0; i<=n; i++){
      vertices.push_back({0, i, 0});
      vertices.push_back({1.0, i, 0});
      vertices.push_back({1.0, i, 1.0});
      vertices.push_back({0, i, 1.0});
   }

   //Triángulos
   triangulos.push_back({0,3,4});    

   for(int i=0; i<4*n-1; i++){
      triangulos.push_back( {i, i+1, i+4} );
      triangulos.push_back( {i+1, i+4, i+5} );
   }

   triangulos.push_back({4*n-1, 4*n, 4*n+3});

}

// -----------------------------------------------------------------------------------------------

