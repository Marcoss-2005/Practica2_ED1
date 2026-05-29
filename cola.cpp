#include "Cola.h"
#include <iostream>

using namespace std;

Cola::Cola()
{
    inicio=NULL;
    fin=NULL;
    ne=0;
}
Cola::~Cola()
{
    //Creamos la cola auxiliar
    TNodo_Cola *aux;
    //Mientras haya algo en el inicio
    while(inicio!=NULL)
    {
        //metemos en la auxiliar la direccion que hay en el inicio
        aux=inicio;
        //el siguiente del inicio lo seteamos al inicio antes de eliminar la direccion
        inicio=inicio->siguiente;
        delete aux;
    }
    fin=NULL;
    ne=0;

}
void Cola::encolar(Paciente p)
{
    //Declaramo un puntero nuevo para el paciente
    TNodo_Cola *nuevo=new TNodo_Cola;
    //le metemos el paciente y seteamoos el puntero de dentro como nulo
    nuevo->datos=p;
    nuevo->siguiente=NULL;

    //Cuando la cola esta vacia o el nuevo tiene mas gravedad que el primero
    if(inicio==NULL||p.gravedad>inicio->datos.gravedad)
    {
        //metemos en el puntero del nuevo la direccion que hay en el inicio
        nuevo->siguiente=inicio;
        //en el inicio metemos la direccion que hay en el nuevo
        inicio=nuevo;
        //si no hay mas elementos, seteamos el fin como el nuevo tambien
        if(fin==NULL)
        {
            fin=nuevo;
        }
        //Cuando tienes que buscar una posicion intermedia
    }
    else
    {
        //creamos un puntero
        TNodo_Cola *ant=inicio;
        //lo meteremos dependiendo la gravedad asi que hacemos un while hasta llegar a la  posicion que vamos a cambiar
        while(ant->siguiente!=NULL&&ant->siguiente->datos.gravedad>=p.gravedad)
        {
            ant=ant->siguiente;
        }
        //ordenamos el puntero de manera que el siguiente del nuevo se agarre al que estaba seteado en el siguiente del anterior
        //y el siguiente del anterior se setea al nuevo, me explico raro pero yo me entiendo
        nuevo->siguiente=ant->siguiente;
        ant->siguiente=nuevo;
        //esto es para el fin
        if(nuevo->siguiente==NULL)
        {
            fin=nuevo;
        }
    }
    ne++;
}
void Cola::desencolar()
{
    //este es corto
    if(inicio!=NULL)
    {
        //si el inicio no esta vacio, declaramos un auxiliar y metemos en el inicio el siguiente, eliminamos la direccion que metimos en el auxiliar y listo
        TNodo_Cola *aux=inicio;
        inicio=inicio->siguiente;
        delete aux;
        ne--;
        if(inicio==NULL)
        {
            fin==NULL;
        }
    }
}
// Observar el primero de la cola [cite: 39]
Paciente Cola::primero()
{
    return inicio->datos;
}

bool Cola::esVacia()
{
    return (inicio == NULL);
}

int Cola::longitud()
{
    return ne;
}

