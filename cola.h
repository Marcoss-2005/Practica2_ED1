#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED
#include "paciente.h"

class Cola
{
private:
    struct TNodo_Cola
    {
        Paciente datos;
        TNodo_Cola *siguiente;
    };

    TNodo_Cola *inicio;
    TNodo_Cola *fin;
    int ne;//Contador de elementos
public:
    Cola();
    ~Cola();

    void encolar(Paciente p);
    void desencolar();
    Paciente primero();

    bool esVacia();
    int longitud();

};


#endif // COLA_H_INCLUDED
