#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include "paciente.h"
struct TNodo_Lista
{
    Paciente datos;
    TNodo_Lista *siguiente;
};

class Lista
{
    TNodo_Lista *elementos;
    int n;//Numero de pacientes ingresados

public:
    Lista();
    ~Lista();

    void insertar(Paciente p);
    void eliminar(int historial);
    Paciente observar(int i);
    int longitud();
    bool esVacia();

};
#endif // LISTA_H_INCLUDED

