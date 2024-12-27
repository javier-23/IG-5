// Nombre: Javier, Apellidos: Mora Ortiz-Villajos, Titulación: GIADE
// Email: javier23@correo.ugr.es, DNI: 20619222K

// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Gestión de grafos de escena (implementación). Clase 'NodoGrafoEscena' y relacionadas.
// ** Copyright (C) 2016-2024 Carlos Ureña
// **
// ** Implementación de: 
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

#include "ig-aux.h"  
#include "grafo-escena.h"
#include "aplicacion-ig.h"
#include "seleccion.h"   // para 'ColorDesdeIdent' 



// *********************************************************************
// Entrada del nodo del Grafo de Escena

// ---------------------------------------------------------------------
// Constructor para entrada de tipo sub-objeto

EntradaNGE::EntradaNGE( Objeto3D * pObjeto )
{
   assert( pObjeto != nullptr );
   tipo   = TipoEntNGE::objeto ;
   objeto = pObjeto ;
}
// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( const glm::mat4 & pMatriz )
{
   tipo    = TipoEntNGE::transformacion ;
   matriz  = new glm::mat4() ; // matriz en el heap, puntero propietario
   *matriz = pMatriz ;
}

// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( Material * pMaterial )
{
   assert( pMaterial != nullptr );
   tipo     = TipoEntNGE::material ;
   material = pMaterial ;
}

// -----------------------------------------------------------------------------
// Destructor de una entrada

EntradaNGE::~EntradaNGE()
{
   /**  no fnciona debido a que se hacen copias (duplicados) de punteros
   if ( tipo == TipoEntNGE::transformacion )
   {
      assert( matriz != NULL );
      delete matriz ;
      matriz = NULL ;
   }
   * **/
}

// *****************************************************************************
// Nodo del grafo de escena: contiene una lista de entradas
// *****************************************************************************

NodoGrafoEscena::NodoGrafoEscena()
{

}

// -----------------------------------------------------------------------------
// Visualiza usando OpenGL

void NodoGrafoEscena::visualizarGL(  )
{
   using namespace std ;
   assert( aplicacionIG != nullptr );

   //cout << "Entra " << __FUNCTION__ << ": " << leerNombre() << endl ;

    // comprobar que hay un cauce y una pila de materiales y recuperarlos.
   Cauce *          cauce           = aplicacionIG->cauce ;           assert( cauce != nullptr );
   PilaMateriales * pila_materiales = aplicacionIG->pila_materiales ; assert( pila_materiales != nullptr );

   if(aplicacionIG->iluminacion)
      pila_materiales->push();
   
   // COMPLETAR: práctica 3: implementar la visualización del nodo
   //
   // Se deben de recorrer las entradas y llamar recursivamente de visualizarGL, pero 
   // teniendo en cuenta que, al igual que el método visualizarGL de las mallas indexadas,
   // si el nodo tiene un color, debemos de cambiar el color del cauce (y hacer push/pop). 
   // Además, hay que hacer push/pop de la pila de modelado. 
   // Así que debemos de dar estos pasos:
   //
   // 1. Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
   //     - hacer push del color actual del cauce (con 'pushColor') y después
   //     - fijar el color en el cauce (con 'fijarColor'), usando el color del objeto (se lee con 'leerColor()')
   if(tieneColor()){
      cauce->pushColor();
      cauce->fijarColor(cauce->leerColorActual());
   }

   // 2. Guardar copia de la matriz de modelado (con 'pushMM'), 
   cauce->pushMM();

   // 3. Para cada entrada del vector de entradas:
   //     - si la entrada es de tipo objeto: llamar recursivamente a 'visualizarGL'
   //     - si la entrada es de tipo transformación: componer la matriz (con 'compMM')
   for(int i=0; i< entradas.size(); i++){

      switch (entradas[i].tipo)
      {
      case TipoEntNGE::objeto:
         entradas[i].objeto->visualizarGL();
         break;
      case TipoEntNGE::transformacion:
         cauce->compMM( *(entradas[i].matriz) );
         break;
      case TipoEntNGE::material:
         if(aplicacionIG->iluminacion)
            pila_materiales->activar(entradas[i].material);
         break;
      case TipoEntNGE::noInicializado:
         break;
      
      }
   }
   
   // 4. Restaurar la copia guardada de la matriz de modelado (con 'popMM')
   cauce->popMM();
   
   // 5. Si el objeto tiene color asignado:
   //     - restaurar el color original a la entrada (con 'popColor')
   if(tieneColor())
      cauce->popColor();

   // COMPLETAR: práctica 4: añadir gestión de los materiales cuando la iluminación está activada    
   //
   // Si 'apl->iluminacion' es 'true', se deben de gestionar los materiales:
   //
   //   1. al inicio, hacer 'push' de la pila de materiales (guarda material actual en la pila)
   //   2. si una entrada es de tipo material, activarlo usando a pila de materiales
   //   3. al finalizar, hacer 'pop' de la pila de materiales (restaura el material activo al inicio)
   if(aplicacionIG->iluminacion)
      pila_materiales->pop();
   // ......


}

// *****************************************************************************
// visualizar pura y simplemente la geometría, sin colores, normales, coord. text. etc...

void NodoGrafoEscena::visualizarGeomGL(  )
{
   using namespace std ;
   // comprobar que hay un cauce 
   assert( aplicacionIG != nullptr );
   Cauce * cauce = aplicacionIG->cauce; assert( cauce != nullptr );
  
   // COMPLETAR: práctica 3: implementar la visualización del nodo (ignorando colores)
   //
   // Este método hace un recorrido de las entradas del nodo, parecido a 'visualizarGL', pero más simple,
   // Se dan estos pasos:
   //
   // 1. Guardar copia de la matriz de modelado (con 'pushMM'), 
   cauce->pushMM();
   
   // 2. Para cada entrada del vector de entradas:
   //         - Si la entrada es de tipo objeto: llamar recursivamente a 'visualizarGeomGL'.
   //         - Si la entrada es de tipo transformación: componer la matriz (con 'compMM').
   for(int i=0; i< entradas.size(); i++){
      if(entradas[i].tipo == TipoEntNGE::objeto)
         entradas[i].objeto->visualizarGeomGL();
      else if(entradas[i].tipo == TipoEntNGE::transformacion)
         cauce->compMM( *(entradas[i].matriz) );
   }
   
   //   3. Restaurar la copia guardada de la matriz de modelado (con 'popMM')
   cauce->popMM();

   // .......

}

// -----------------------------------------------------------------------------
// Visualizar las normales de los objetos del nodo

void NodoGrafoEscena::visualizarNormalesGL(  )
{
   using namespace std ;

   // comprobar que hay un cauce 
   assert( aplicacionIG != nullptr );
   Cauce * cauce = aplicacionIG->cauce; assert( cauce != nullptr );
  

   // COMPLETAR: práctica 4: visualizar las normales del nodo del grafo de escena
   //
   // Este método hace un recorrido de las entradas del nodo, parecido a 'visualizarGL', teniendo 
   // en cuenta estos puntos:
   //
   // - usar push/pop de la matriz de modelado al inicio/fin (al igual que en visualizatGL)
   // - recorrer las entradas, llamando recursivamente a 'visualizarNormalesGL' en los nodos u objetos hijos
   // - ignorar el color o identificador del nodo (se supone que el color ya está prefijado antes de la llamada)
   // - ignorar las entradas de tipo material, y la gestión de materiales (se usa sin iluminación)
   cauce->pushMM();

   for(int i=0; i<entradas.size(); i++){
      if(entradas[i].tipo == TipoEntNGE::objeto){
         entradas[i].objeto->visualizarNormalesGL();
      }
   }

   cauce->popMM();
   // .......

}

// -----------------------------------------------------------------------------
// visualizar el objeto en 'modo seleccion', es decir, sin iluminación y con los colores 
// basados en los identificadores de los objetos
void NodoGrafoEscena::visualizarModoSeleccionGL()
{
   using namespace std ;
   assert( aplicacionIG != nullptr );
   Cauce * cauce = aplicacionIG->cauce ; assert( cauce != nullptr );

   // COMPLETAR: práctica 5: visualizar este nodo en modo selección.
   //
   // Se debe escribir código para dar estos pasos:
   // 
   // 2. Leer identificador (con 'leerIdentificador'), si el identificador no es -1 
   //      + Guardar una copia del color actual del cauce (con 'pushColor')
   //      + Fijar el color del cauce de acuerdo al identificador, (usar 'ColorDesdeIdent'). 
   // 3. Guardar una copia de la matriz de modelado (con 'pushMM')
   // 4. Recorrer la lista de nodos y procesar las entradas transformación o subobjeto:
   //      + Para las entradas subobjeto, invocar recursivamente a 'visualizarModoSeleccionGL'
   //      + Para las entradas transformación, componer la matriz (con 'compMM')
   // 5. Restaurar la matriz de modelado original (con 'popMM')   
   // 6. Si el identificador no es -1, restaurar el color previo del cauce (con 'popColor')
   //
   // ........
   if(leerIdentificador() != -1){
      cauce->pushColor();
      cauce->fijarColor(ColorDesdeIdent(leerIdentificador()));
   }
   cauce->pushMM();


   for(unsigned int i=0; i<entradas.size(); i++){
      if(entradas[i].tipo == TipoEntNGE::objeto)
         entradas[i].objeto->visualizarModoSeleccionGL();
      else if(entradas[i].tipo == TipoEntNGE::transformacion)
         cauce->compMM(*(entradas[i].matriz)); //**
   }

   cauce->popMM();

   if(leerIdentificador() != -1){
      cauce->popColor();
   }

}

// -----------------------------------------------------------------------------
// Añadir una entrada (al final).
// genérica (de cualqiuer tipo de entrada)

unsigned NodoGrafoEscena::agregar( const EntradaNGE & entrada )
{
   // COMPLETAR: práctica 3: agregar la entrada al nodo, devolver índice de la entrada agregada
   entradas.push_back(entrada);
   return (entradas.size()-1) ; // sustituir por lo que corresponda ....

}
// -----------------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// objeto (copia solo puntero)

unsigned NodoGrafoEscena::agregar( Objeto3D * pObjeto )
{
   return agregar( EntradaNGE( pObjeto ) );
}
// ---------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// matriz (copia objeto)

unsigned NodoGrafoEscena::agregar( const glm::mat4 & pMatriz )
{
   return agregar( EntradaNGE( pMatriz ) );
}
// ---------------------------------------------------------------------
// material (copia solo puntero)
unsigned NodoGrafoEscena::agregar( Material * pMaterial )
{
   return agregar( EntradaNGE( pMaterial ) );
}

// devuelve el puntero a la matriz en la i-ésima entrada
glm::mat4 * NodoGrafoEscena::leerPtrMatriz( unsigned indice )
{
   // COMPLETAR: práctica 3: leer un puntero a una matriz en una entrada de un nodo
   //
   // Devolver el puntero a la matriz en la entrada indicada por 'indice'. 
   // Debe de dar error y abortar si: 
   //   - el índice está fuera de rango 
   //   - la entrada no es de tipo transformación
   //   - el puntero a la matriz es nulo 
   assert(indice < entradas.size());
   assert(entradas[indice].tipo == TipoEntNGE::transformacion);
   assert(entradas[indice].matriz != nullptr);
   // Sustituir 'return nullptr' por lo que corresponda.
   //
   return entradas[indice].matriz;


}
// -----------------------------------------------------------------------------
// si 'centro_calculado' es 'false', recalcula el centro usando los centros
// de los hijos (el punto medio de la caja englobante de los centros de hijos)

void NodoGrafoEscena::calcularCentroOC()
{
   using namespace std ;
   using namespace glm ;

   // COMPLETAR: práctica 5: calcular y guardar el centro del nodo
   //    en coordenadas de objeto (hay que hacerlo recursivamente)
   //   (si el centro ya ha sido calculado, no volver a hacerlo)
   // ........
   if(centro_calculado)
      return;

      int num_hijos = 0;
      glm::mat4 mmodelado(1.0f);
      glm::vec3 centro_aux(0.0f, 0.0f, 0.0f);

      for(unsigned int i = 0; i < entradas.size(); i++) {
         if(entradas[i].tipo == TipoEntNGE::transformacion )
            mmodelado = mmodelado * (*entradas[i].matriz);
         if(entradas[i].tipo == TipoEntNGE::objeto ){
            entradas[i].objeto->calcularCentroOC();
            centro_aux+=  glm::vec3((mmodelado * glm::vec4(entradas[i].objeto->leerCentroOC(), 1.0f)));
            num_hijos++;
         }
      }

      ponerCentroOC(centro_aux/float(num_hijos));
      centro_calculado = true;

}
// -----------------------------------------------------------------------------
// método para buscar un objeto con un identificador y devolver un puntero al mismo

bool NodoGrafoEscena::buscarObjeto
(
   const int          ident_busc, // identificador a buscar
   const glm::mat4 &  mmodelado,  // matriz de modelado
   Objeto3D       **  objeto,     // (salida) puntero al puntero al objeto
   glm::vec3 &        centro_wc   // (salida) centro del objeto en coordenadas del mundo
)
{
   using namespace std ;
   using namespace glm ;
   
   assert( 0 < ident_busc );

   // COMPLETAR: práctica 5: buscar un sub-objeto con un identificador
   // Se deben de dar estos pasos:

   // 1. calcula el centro del objeto, (solo la primera vez)
   // ........
   calcularCentroOC();

   // 2. si el identificador del nodo es el que se busca, ya está (terminar)
   // ........
   if(leerIdentificador() == ident_busc){
      *objeto = this;
      centro_wc = glm::vec3(mmodelado* glm::vec4(leerCentroOC(), 1.0f));   //***
      return true;
   }

   // 3. El nodo no es el buscado: buscar recursivamente en los hijos
   //    (si alguna llamada para un sub-árbol lo encuentra, terminar y devolver 'true')
   // ........
   else {
      glm::mat4 modelado_aux = mmodelado;
      for(unsigned int i = 0; i < entradas.size(); i++) {
         if(entradas[i].tipo == TipoEntNGE::transformacion )
            modelado_aux = modelado_aux * (*entradas[i].matriz);
         if(entradas[i].tipo == TipoEntNGE::objeto)
            if(entradas[i].objeto->buscarObjeto(ident_busc, modelado_aux, objeto, centro_wc))
               return true;
      }
   }

   // ni este nodo ni ningún hijo es el buscado: terminar
   return false ;
}


//P3 ejercicios adicionales:

GrafoEstrellaX::GrafoEstrellaX(unsigned n){
   
   assert(n>1);
   ponerNombre("GradoEstrellaX");

   //Estrella:
   EstrellaZ * estrellaZ = new EstrellaZ(n);

   NodoGrafoEscena *estrellaPlana = new NodoGrafoEscena();
   estrellaPlana->agregar(glm::rotate(glm::radians(90.0f), glm::vec3(0, 1, 0)));
   estrellaPlana->agregar(glm::scale(glm::vec3(1.3*2, 1.3*2, 1.3*2)));
   estrellaPlana->agregar(glm::translate(glm::vec3(-0.5, -0.5 ,0))); //Lo contrario al primer vértice del objeto
   estrellaPlana->agregar(estrellaZ);

   //Conos:
   Cono *cono_objeto = new Cono(20,40);

   NodoGrafoEscena *conos = new NodoGrafoEscena();
   conos->agregar(glm::translate(glm::vec3(0, 0, 1.3)));    
   conos->agregar(glm::rotate(glm::radians(90.0f), glm::vec3(1, 0, 0))); //Primer cono empieza en z positivo
   conos->agregar(glm::scale(glm::vec3(0.14, 0.15 , 0.14)));
   conos->agregar(cono_objeto);

   unsigned ind1 = agregar(glm::rotate(glm::radians(0.0f), glm::vec3(1, 0, 0))); //Antes de cualquier agregar general -> Mover todo

   agregar(conos);   //Añade el primer cono
   unsigned rotacion = 360/n;
   for(int i=0; i<n-1; i++){
      agregar(glm::rotate(glm::radians(float(rotacion)), glm::vec3(1, 0, 0)));
      agregar(conos); //Añadir el resto de conos
   }

   agregar(estrellaPlana);

   matriz_1 = leerPtrMatriz(ind1);

}

void GrafoEstrellaX::actualizarEstadoParametro(const unsigned iParam, const float t_sec){
   
   switch (iParam)
   {
   case 0:
      giro(parametro*sin(2*M_PI*2.5*t_sec)); //Oscilante: n=2,5 (oscilaciones por segundo)
      break;
   default:
      break;
   }

}

void GrafoEstrellaX::giro(const float grado){

   *matriz_1 = glm::rotate(glm::radians(grado), glm::vec3(1, 0, 0)); //Rotar repecto al eje x

}

unsigned GrafoEstrellaX::leerNumParametros() const{
   return n_parametros;
}

GrafoCubos::GrafoCubos(){

   ponerNombre("GrafoCubos");

   RejillaY *rejilla = new RejillaY(7,7); //Objeto

   NodoGrafoEscena *nodo_rejillas = new NodoGrafoEscena();
   nodo_rejillas->agregar(glm::translate(glm::vec3(-0.5, -0.5, -0.5))); //Cara inferior
   nodo_rejillas->agregar(rejilla);
   agregar(nodo_rejillas);    //Agregar nodo de la cara inferior

   Cubo *cubo = new Cubo(); //Objeto

   NodoGrafoEscena *nodo_cubos = new NodoGrafoEscena();
   unsigned ind1 = nodo_cubos->agregar(glm::rotate(glm::radians(0.0f), glm::vec3(0, 1, 0))); // Para rotar cada cubo
   nodo_cubos->agregar(glm::translate(glm::vec3(0, -0.9, 0)));
   nodo_cubos->agregar(glm::scale(glm::vec3(0.2, 0.4 , 0.2)));
   nodo_cubos->agregar(cubo); //Cubo inferior
   agregar(nodo_cubos);

   for(int i=0; i<3; i++){
         agregar(glm::rotate(glm::radians(90.0f), glm::vec3(1, 0, 0)));
         agregar(nodo_rejillas);
         agregar(nodo_cubos);
   }

   //Añadir las dos ultimas caras
   agregar(glm::rotate(glm::radians(90.0f), glm::vec3(0, 0, 1)));
   agregar(nodo_rejillas);
   agregar(nodo_cubos);
   agregar(glm::rotate(glm::radians(180.0f), glm::vec3(0, 0, 1))); //Añade a la rotación que ya tienes, otra rotación sobre esa
   agregar(nodo_rejillas);
   agregar(nodo_cubos);

   matriz_1 = nodo_cubos->leerPtrMatriz(ind1);  //Mover solo los cubos

}


void GrafoCubos::actualizarEstadoParametro(const unsigned iParam, const float t_sec){
   
   switch (iParam)
   {
   case 0:
      giro(parametro*sin(2*M_PI*2.5*t_sec));
      break;
   default:
      break;
   }

}

void GrafoCubos::giro(const float grado){

   *matriz_1 = glm::rotate(glm::radians(grado), glm::vec3(0, 1, 0));

}


unsigned GrafoCubos::leerNumParametros() const{
   return n_parametros;
}

//P4:

NodoCubo24::NodoCubo24() {

   ponerNombre( std::string("NodoCubo24") );

   agregar(new Material(new Textura("window-icon.jpg"), 1.0, 1.0, 1.0, 1.0));
   agregar(new Cubo24());
}

//Ejercicio adicional 1 P4:

NodoDiscoP4::NodoDiscoP4(int ejerc){
   
   ponerNombre(std::string("Nodo ejercicio adicional práctica 4, examen 27 enero"));
   agregar(new Material(new Textura("cuadricula.jpg"), 1.0, 1.0, 1.0, 1.0));
   agregar( new MallaDiscoP4(ejerc) );

}

// Práctica 5:

GrafoEsferasP5::GrafoEsferasP5(){
   const unsigned
      n_filas_esferas = 8,
      n_esferas_x_fila = 5 ;
   const float 
      e = 0.4/n_esferas_x_fila ;

      agregar( glm::scale(glm::vec3(e,e,e)));
      for( unsigned i = 0 ; i < n_filas_esferas ; i++ ){
         NodoGrafoEscena * fila_esferas = new NodoGrafoEscena() ;
         
         for( unsigned j = 0 ; j < n_esferas_x_fila ; j++ ){
            MiEsferaE1 * esfera = new MiEsferaE1(i,j) ;
            esfera->ponerIdentificador(j + (i*n_filas_esferas) + 1);
            fila_esferas->agregar( glm::translate( glm::vec3( 2.2, 0.0, 0.0)));
            fila_esferas->agregar( esfera );
         }
         
         agregar( fila_esferas );
         agregar( glm::translate( glm::vec3(0.0, 0.0, 5.0)));
      }
}

MiEsferaE1::MiEsferaE1(unsigned n_fila, unsigned num_esfera){
   
   fila = n_fila +1;
   n_esfera = num_esfera +1;
   agregar(new Esfera(30, 50));
   
}

bool MiEsferaE1::cuandoClick(const glm::vec3 &centro_wc){
   
   using namespace std ;
   assert( aplicacionIG != nullptr );
   
   Escena * escena = aplicacionIG->escenas[aplicacionIG->ind_escena_act] ;
   assert( escena != nullptr );

   cout << "Ejecutando método 'cuandoClick' de MiEsfera1." << endl ;
   cout <<  "Se ha seleccionado la esfera numero " << n_esfera << " de la fila numero " << fila  << endl ;

   escena->camaraActual()->mirarHacia(centro_wc);

   return true;
}


GrafoEsferasP5_2::GrafoEsferasP5_2(){

   const unsigned
      n_filas_esferas = 8,
      n_esferas_x_fila = 5;
      
   const float e = 2.5/n_esferas_x_fila;

      agregar( glm::scale(glm::vec3( e, e, e )));
      for( unsigned i = 0 ; i < n_filas_esferas ; i++ )
      {
         NodoGrafoEscena * fila_esferas = new NodoGrafoEscena() ;
         fila_esferas->agregar( glm::translate( glm::vec3( 3.0, 0.0, 0.0 )));
         for( unsigned j = 0 ; j < n_esferas_x_fila ; j++ )
         {
            MiEsferaE2 * esfera = new MiEsferaE2() ;
            esfera->ponerIdentificador(j + (i*n_filas_esferas) + 1);
            fila_esferas->agregar( glm::translate( glm::vec3( 2.5, 0.0, 0.0 )));
            fila_esferas->agregar( esfera );
         }
      agregar( fila_esferas );
      agregar( glm::rotate(glm::radians(360.0f/n_filas_esferas), glm::vec3( 0.0, 1.0, 0.0 )));
   }
}

MiEsferaE2::MiEsferaE2(){
   
   agregar(new Esfera(30,50));
   
}

bool MiEsferaE2::cuandoClick(const glm::vec3 &centro_wc){

   using namespace std;
   assert( aplicacionIG != nullptr );
   Escena * escena = aplicacionIG->escenas[aplicacionIG->ind_escena_act] ; 
   assert( escena != nullptr );

   cout << "Ejecutando método 'cuandoClick' de MiEsfera2." << endl ;

   if(tieneColor()){
      if(leerColor() == glm::vec3(1.0, 0.0, 0.0)){ //Si es rojo
         cout << "Se ha quitado el color" << endl;
         ponerColor(glm::vec3(1.0, 1.0, 1.0));
      }
      else {
         cout << "Se ha puesto el color rojo" << endl;
         ponerColor(glm::vec3(1.0, 0.0, 0.0));
      }
   }
   else{
      cout << "Se ha puesto el color rojo" << endl;
      ponerColor(glm::vec3(1.0, 0.0, 0.0));
   }
   
   return true ;

}






