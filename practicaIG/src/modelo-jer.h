#ifndef MODELO_JER_HPP
#define MODELO_JER_HPP
#include "grafo-escena.h"

using namespace std;

class Caza: public NodoGrafoEscena{
    private:
        const unsigned n_parametros = 3; //grados de libertad
        glm::mat4 * matriz_1 = nullptr;
        glm::mat4 * matriz_2 = nullptr;
        glm::mat4 * matriz_3 = nullptr;
        glm::mat4 * matriz_4 = nullptr;
        glm::mat4 * matriz_5 = nullptr;
        const float grado1 = 0+10;
        const float grado2 = 180+180;
        const float grado3 = 45+45; 


    public:
        Caza();
        unsigned leerNumParametros() const;
        void actualizarEstadoParametro(const unsigned iParam, const float tSec);
        void traslacion(float x, float y, float z);
        void rotacion(float x);
        void rotacion2(float x);

};

class Ala: public NodoGrafoEscena{
    public:
        Ala();
};

class Cuerpo: public NodoGrafoEscena{
    public:
        Cuerpo();
};

class Misil : public NodoGrafoEscena{
    public:
        Misil();
};

class TrianguloObtusangulo : public MallaInd{
    public:
        TrianguloObtusangulo();
};

class TrianguloRectangulo : public MallaInd{
    public:
        TrianguloRectangulo();
};

class Esqueleto : public NodoGrafoEscena{
    public:
        Esqueleto();

};

class Morro : public NodoGrafoEscena{
    public:
        Morro();

};

class Cabina : public NodoGrafoEscena{
    public:
        Cabina();

};

class Motor : public NodoGrafoEscena{
    public:
        Motor();

};

class Minialas : public NodoGrafoEscena{
    public:
        Minialas();

};

class Fuego : public NodoGrafoEscena{
    public:
        Fuego();

};


#endif