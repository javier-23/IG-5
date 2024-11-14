// Nombre: Javier, Apellidos: Mora Ortiz-Villajos, Titulación: GIADE
// Email: javier23@correo.ugr.es, DNI: 20619222K

#include "modelo-jer.h"

using namespace std;

TrianguloObtusangulo::TrianguloObtusangulo():MallaInd(" Triangulo Obtusangulo "){
    vertices.push_back({0,0,0 });
    vertices.push_back({1,0,0 });
    vertices.push_back({-0.5,1.1,0 });

    triangulos.push_back( {0, 1, 2} );
}

TrianguloRectangulo::TrianguloRectangulo():MallaInd(" Triangulo Rectangulo "){

    vertices.push_back({0,-0.06,0 });
    vertices.push_back({1,-0.06,0 });
    vertices.push_back({0, 0.5,0 });

    triangulos.push_back( {0, 1, 2} );

    cc_tt_ver.push_back({0, 0});
    cc_tt_ver.push_back({1, 0});
    cc_tt_ver.push_back({0, 1});
    
}

Ala::Ala(){

    //Identificador:
    int id_alas = 1;

    //Textura:
    Textura * gris = new Textura("gris.jpg");
    Material * material_ala = new Material( gris, 0.7, 1.0, 0.0, 1.0);

    Esfera * esfera = new Esfera(20,50);
    esfera->ponerColor( {0.6313, 0.6313, 0.6313} );

    TrianguloRectangulo * triangulo_rectangulo = new TrianguloRectangulo();
    triangulo_rectangulo->ponerColor({0.6313, 0.6313, 0.6313});

    NodoGrafoEscena * ala = new NodoGrafoEscena();
    ala->agregar(glm::translate(glm::vec3(1.0, 2.0 ,3.0)));
    ala->agregar(glm::rotate(glm::radians(90.0f), glm::vec3(0, 0, 1)));
    ala->agregar(glm::rotate(glm::radians(90.0f), glm::vec3(0, 1, 0)));
    ala->agregar( glm::scale(glm::vec3(3.0, 4.0 , 0)));
    ala->agregar(material_ala);
    ala->agregar(triangulo_rectangulo);
        
    NodoGrafoEscena *misil = new NodoGrafoEscena();
    misil->agregar(glm::translate(glm::vec3(-1.0, 2.0 ,3.0)));
    misil->agregar(glm::rotate(glm::radians(90.0f), glm::vec3(0, 1, 0)));
    misil->agregar(glm::scale(glm::vec3(0.25, 0.05 ,0.025)));
    misil->agregar(esfera);

    ponerNombre("Alas principales");
    ponerIdentificador(id_alas);
    agregar(ala);
    agregar(misil);

}

Esqueleto::Esqueleto(){

    //Identificador:
    int id_esqueleto = 2;

    //Material:
    Material * material_esqueleto = new Material(0.6, 1.0, 0.0, 1.0); //Material difuso

    Esfera* esfera_cuerpo= new Esfera(20,50);
    esfera_cuerpo->ponerColor({0.5568, 0.5568, 0.5568});

    NodoGrafoEscena * cuerpo1 = new NodoGrafoEscena();
    cuerpo1->agregar(glm::translate(glm::vec3(1.5, 2.0, 0.9)));
    cuerpo1->agregar(glm::scale(glm::vec3(0.45, 0.4, 2.5)));
    cuerpo1->ponerIdentificador(id_esqueleto);
    cuerpo1->agregar(material_esqueleto);
    cuerpo1->ponerNombre("Parte central del avión");
    cuerpo1->agregar(esfera_cuerpo);

    agregar(cuerpo1);

}

Morro::Morro(){

    //Identificador:
    int id_morro = 3;

    //Material
    Material * material_morro = new Material(0.6, 0.6, 0.8, 10.0);

    Cono * cono = new Cono(20,40);
    cono->ponerColor({0.7373, 0.7373, 0.7373});

    NodoGrafoEscena * morro1 = new NodoGrafoEscena();
    morro1->agregar(glm::translate(glm::vec3(1.5, 2.0, -1.1)));
    morro1->agregar(glm::rotate(glm::radians(270.0f), glm::vec3(1, 0, 0)));
    morro1->agregar(glm::scale(glm::vec3(0.275, 0.9, 0.25)));
    morro1->ponerIdentificador(id_morro);
    morro1->ponerNombre("Morro del avion");
    morro1->agregar(material_morro);
    morro1->agregar(cono);

    agregar(morro1);

}

Cabina::Cabina(){

    //Identificador:
    int id_cabina = 4;

    //Material:
    Material * material_cabina = new Material( 0.9, 0.0, 1.0, 20.0); //Material pseudo-especular

    Esfera * esfera = new Esfera(32,64); 
    esfera->ponerColor({0.6235, 0.8353, 0.8196});

    NodoGrafoEscena * cabina1 = new NodoGrafoEscena();
    cabina1->agregar(glm::translate(glm::vec3(1.5, 2.22, -0.35)));
    cabina1->agregar(glm::rotate(glm::radians(90.0f), glm::vec3(0, 1, 0)));
    cabina1->agregar(glm::rotate(glm::radians(350.0f), glm::vec3(0, 0, 1)));
    cabina1->agregar(glm::scale(glm::vec3(0.8, 0.25 ,0.3)));
    cabina1->ponerIdentificador(id_cabina);
    cabina1->ponerNombre("Cabina");
    cabina1->agregar(material_cabina);
    cabina1->agregar(esfera);

    agregar(cabina1);

}

Motor::Motor(){

    //Identificador:
    int id_motores = 5;

    Cilindro * cilindro_motor= new Cilindro(20,50);
    cilindro_motor->ponerColor({0,0,0});

    NodoGrafoEscena * motor = new NodoGrafoEscena();
    motor->agregar(glm::rotate(glm::radians(90.0f), glm::vec3(1, 0, 0)));
    motor->agregar(glm::scale(glm::vec3(0.08, 0.3, 0.08)));
    motor->agregar(cilindro_motor);

    ponerNombre("Motores del avion");
    ponerIdentificador(id_motores);
    agregar(motor);
}

Minialas::Minialas(){

    //Identificador:
    int id_minialas = 6;

    TrianguloObtusangulo * triangulo = new TrianguloObtusangulo();
    triangulo->ponerColor({0.6313, 0.6313, 0.6313});

    NodoGrafoEscena * miniala = new NodoGrafoEscena();
    miniala->agregar(glm::rotate(glm::radians(90.0f), glm::vec3(0, 1, 0)));
    miniala->agregar(glm::scale(glm::vec3(0.8, 0.8, 0.8)));
    miniala->agregar(triangulo);

    ponerNombre("Minialas");
    ponerIdentificador(id_minialas);
    agregar(miniala);

}

Fuego::Fuego(){

    //Identificador:
    int id_fuegos = 7;

    //Textura :
    Textura * fuego_text = new TexturaXY("fuego.jpg");
    Material * material_fuego = new Material( fuego_text, 1.0, 1.0, 1.0, 1.0);

    Esfera* esfera_fuego= new Esfera(20,50);
    esfera_fuego->ponerColor({0.99607, 0, 0.019607});

    NodoGrafoEscena * fuego = new NodoGrafoEscena();
    fuego->agregar(glm::scale(glm::vec3(0.078, 0.078, 0.001)));
    fuego-agregar(material_fuego);
    fuego->agregar(esfera_fuego);

    ponerNombre("Combustion del motor");
    ponerIdentificador(id_fuegos);
    agregar(fuego);
}


Cuerpo::Cuerpo(){

    //int id_morro = 3;

    //Textura y Material del Ala Superior:
    Textura * textura_alasuperior = new TexturaXY("spain.jpg");
    Material * material_alasuperior = new Material( textura_alasuperior, 1.0, 1.0, 1.0, 1.0);

    //Material alas pequeñas laterales:
    Material * material_gris = new Material(0.6, 1.0, 0.0, 1.0);

    NodoGrafoEscena * base = new NodoGrafoEscena();
    base->agregar(new Esqueleto());
    
    NodoGrafoEscena * morro = new NodoGrafoEscena();
    //morro->ponerIdentificador(id_morro);
    morro->agregar(new Morro());

    NodoGrafoEscena * motor1 = new NodoGrafoEscena();
    motor1->agregar(glm::translate(glm::vec3(1.415, 2.0, 3.16)));
    motor1->agregar(new Motor());

    NodoGrafoEscena * motor2 = new NodoGrafoEscena();
    motor2->agregar(glm::translate(glm::vec3(1.585, 2.0, 3.16)));
    motor2->agregar(new Motor());

    NodoGrafoEscena * cabina = new NodoGrafoEscena();
    cabina->agregar(new Cabina());

    NodoGrafoEscena * ala_superior = new NodoGrafoEscena();
    ala_superior->agregar(glm::translate(glm::vec3(1.5, 2.1, 3.3)));
    ala_superior->agregar(material_alasuperior);
    ala_superior->agregar(new Minialas());

    NodoGrafoEscena * fuego_dcho = new NodoGrafoEscena();
    fuego_dcho->agregar(glm::translate(glm::vec3(1.585, 2.0, 3.4)));
    fuego_dcho->agregar(new Fuego());

    NodoGrafoEscena * fuego_izq = new NodoGrafoEscena();
    fuego_izq->agregar(glm::translate(glm::vec3(1.415, 2.0, 3.4)));
    fuego_izq->agregar(new Fuego());

    NodoGrafoEscena * ala_peque_izq = new NodoGrafoEscena();
    ala_peque_izq->agregar(glm::translate(glm::vec3(1.3, 2.0, -0.3)));
    ala_peque_izq->agregar(glm::rotate(glm::radians(90.0f), glm::vec3(0, 0, 1)));
    ala_peque_izq->agregar(material_gris);
    ala_peque_izq->agregar(new Minialas());

    NodoGrafoEscena * ala_peque_dcha = new NodoGrafoEscena();
    ala_peque_dcha->agregar(glm::translate(glm::vec3(1.7, 2.0, -0.3)));
    ala_peque_dcha->agregar(glm::rotate(glm::radians(270.0f), glm::vec3(0, 0, 1)));
    ala_peque_dcha->agregar(material_gris);
    ala_peque_dcha->agregar(new Minialas());

    agregar(base);
    agregar(morro);
    agregar(motor1);
    agregar(motor2);
    agregar(cabina);
    agregar(ala_superior);
    agregar(fuego_dcho);
    agregar(fuego_izq);
    agregar(ala_peque_izq);
    agregar(ala_peque_dcha);

}

Misil::Misil(){

    //Identificador:
    int id_misiles = 8;

    Esfera * esfera = new Esfera(20,50);
    esfera->ponerColor( {0.3019, 0.3019, 0.3019} );

    NodoGrafoEscena *misil_grande = new NodoGrafoEscena();
    misil_grande->agregar(glm::rotate(glm::radians(90.0f), glm::vec3(0, 1, 0)));
    misil_grande->agregar(glm::scale(glm::vec3(1, 0.2 ,0.2)));
    misil_grande->agregar(esfera);

    ponerNombre("Misiles grandes");
    ponerIdentificador(id_misiles);
    agregar(misil_grande);

}


Caza::Caza(){
    
    ponerNombre( std::string( " Caza ") );

    
 //Cuerpo
    NodoGrafoEscena *cuerpo = new NodoGrafoEscena();
    cuerpo->agregar(new Cuerpo());

 //Alas
    NodoGrafoEscena * ala_izq = new NodoGrafoEscena();
    ala_izq->agregar(new Ala());

    NodoGrafoEscena * ala_dcha = new NodoGrafoEscena();
    ala_dcha->agregar(glm::translate(glm::vec3(3.0, 4, 0)));
    ala_dcha->agregar(glm::rotate(glm::radians(180.0f), glm::vec3(0, 0, 1)));
    ala_dcha->agregar(new Ala());

 //Misiles grandes
    NodoGrafoEscena *misil_izq = new NodoGrafoEscena();
    misil_izq->agregar(glm::translate(glm::vec3(0, 1.8 ,2.2)));
    misil_izq->agregar(new Misil());

    NodoGrafoEscena *misil_dcho = new NodoGrafoEscena();
    misil_dcho->agregar(glm::translate(glm::vec3(3, 1.8 ,2.2)));
    misil_dcho->agregar(new Misil());

    unsigned ind1 = agregar(glm::translate(glm::vec3(2,2,0)));
    unsigned ind2 = agregar(glm::rotate(glm::radians(0.0f), glm::vec3(0, 1, 0)));
    unsigned ind3 = agregar(glm::rotate(glm::radians(0.0f), glm::vec3(0, 0, 1)));

    agregar(cuerpo);
    agregar(ala_dcha);
    agregar(ala_izq);
    agregar(misil_dcho);
    agregar(misil_izq);

    matriz_1 = leerPtrMatriz(ind1);
    matriz_2 = leerPtrMatriz(ind2);
    matriz_3 = leerPtrMatriz(ind3);

}

unsigned Caza::leerNumParametros() const {
    return n_parametros;
}

void Caza::actualizarEstadoParametro(const unsigned iParam, const float t_sec) {

    assert(0<=iParam<=n_parametros);
    switch (iParam)
    {
    case 0:
        traslacion(2, 2, grado1*sin(M_PI*t_sec));
        break;
    case 1:
        rotacion(grado2*sin(M_PI*t_sec));
        break;
    case 2:
        rotacion2(grado3*sin(M_PI*t_sec));
        break;
    }
}

void Caza::traslacion(float x, float y, float z){

    *matriz_1 = glm::translate(glm::vec3(x,y,z));

}

void Caza::rotacion(float x){

    *matriz_2 = glm::rotate(glm::radians(x), glm::vec3(0, 1, 0));

}

void Caza::rotacion2(float x){

    *matriz_3 = glm::rotate(glm::radians(x), glm::vec3(0, 0, 1));

}