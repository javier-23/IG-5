// Nombre: Javier, Apellidos: Mora Ortiz-Villajos, Titulación: GIADE
// Email: javier23@correo.ugr.es, DNI: 20619222K

#include "examen-ec-p123.h"

Ejercicio1::Ejercicio1(): MallaInd( "Malla de triangulos" ){

    vertices =
      {  { -1.0, 0.0, -0.5 }, // 0
         { -1.0, 0.0, +0.5 }, // 1
         { -0.5, 0.0, -0.5 }, // 2
         { -0.5, 0.0, +0.5 }, // 3
         { 0.0, +0.5, -0.5 }, // 4
         { 0.0, +0.5, +0.5 }, // 5
         { +0.5, 0.0, -0.5 }, // 6
         { +0.5, 0.0, +0.5 }, // 7
         { +1.0, 0.0, -0.5}, // 8
         { +1.0, 0.0, +0.5} //9
      };

   triangulos =
      {  {0,1,3}, {0,2,3}, 
         {2,4,5}, {2,3,5}, 

         {4,6,7}, {4,5,7}, 
         {6,7,9}, {8,9,6}, 
      };

    //Vertices plano inferior tono gris oscuro, y vértices de arriba blanco
    col_ver =
   {
      { 0.63, 0.63, 0.63 }, // 0
      { 0.63, 0.63, 0.63 }, // 1
      { 0.63, 0.63, 0.63 }, // 2
      { 0.63, 0.63, 0.63 }, // 3
      { +1.0, +1.0, +1.0 }, // 4
      { +1.0, +1.0, +1.0 }, // 5
      { 0.63, 0.63, 0.63 }, // 6
      { 0.63, 0.63, 0.63 }, // 7
      { 0.63, 0.63, 0.63 }, // 8
      { 0.63, 0.63, 0.63 } // 9

   };

}

Ejercicio2::Ejercicio2(unsigned n): MallaInd( "Replicas de mallas de triangulos" ){

    assert(n>0);

    for(unsigned i=0; i<=n; i++){
      vertices.push_back({ -1.0, 0.0, i }); //0
      vertices.push_back({ -0.5, 0.0, i }); //1 
      vertices.push_back({ 0.0, +0.5, i }); //2 
      vertices.push_back({ +0.5, 0.0, i }); //3 
      vertices.push_back({ +1.0, 0.0, i }); //4 
   }

   //Triángulos  

   for(int i=0; i<(8*n)-1; i+=5){
      triangulos.push_back( {i+1, i, i+6} );
      triangulos.push_back( {i, i+5, i+6} );

      triangulos.push_back( {i+2, i+1, i+7} );
      triangulos.push_back( {i+1, i+6, i+7} );

      triangulos.push_back( {i+3, i+2, i+8} );
      triangulos.push_back( {i+2, i+7, i+8} );

      triangulos.push_back( {i+4, i+3, i+9} );
      triangulos.push_back( {i+3, i+8, i+9} );
   }

   
}


Ejercicio3::Ejercicio3(unsigned ancho, unsigned alto){
    
    ponerNombre("Ejercicio3");
    
    Cubo * cubo = new Cubo();

    NodoGrafoEscena *nodo_cubo_inferior = new NodoGrafoEscena();
    unsigned ind2 = nodo_cubo_inferior->agregar(glm::scale(glm::vec3(ancho, alto, ancho)));
    nodo_cubo_inferior->agregar(cubo);
    agregar(nodo_cubo_inferior);

    NodoGrafoEscena *nodo_cubo_superior = new NodoGrafoEscena();
    unsigned ind1 = nodo_cubo_superior->agregar(glm::rotate(glm::radians(0.0f), glm::vec3(0, 0, 1)));
    nodo_cubo_superior->agregar(glm::scale(glm::vec3(ancho, alto, ancho)));
    nodo_cubo_superior->agregar(cubo);
    agregar(glm::translate(glm::vec3(0, alto, 0)));
    agregar(nodo_cubo_superior);

    matriz_1 = nodo_cubo_superior->leerPtrMatriz(ind1);
    matriz_2 = nodo_cubo_inferior->leerPtrMatriz(ind2);
    

}

void Ejercicio3::actualizarEstadoParametro(const unsigned iParam, const float t_sec){
   
   switch (iParam)
   {
   case 0:
        giro(grado_libertad1*sin(2*M_PI*2.5*t_sec));
    break;
    case 1:
        acortar(grado_libertad2*sin(2*M_PI*2*t_sec));
    break;
     
   default:
      break;
   }

}

void Ejercicio3::giro(const float grado){

   *matriz_1 = glm::rotate(glm::radians(grado), glm::vec3(0, 0, 1));

}

void Ejercicio3::acortar(const float grado){

   *matriz_2 = glm::scale(glm::vec3(1, glm::radians(grado), 1));

}

unsigned Ejercicio3::leerNumParametros() const{
   return n_parametros;
}