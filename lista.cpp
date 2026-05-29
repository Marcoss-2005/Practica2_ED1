#include <iostream>
#include <string>
#include "lista.h"

using namespace std;

Lista::Lista()
{
    elementos=NULL;
    n=0;

}

Lista::~Lista()
{
    TNodo_Lista *aux;//creamos un puntero auxiliar
    while(elementos!=NULL) //mientras nuestro puntero orig. no sea nulo
    {
        aux=elementos;//seteamos nuestro auxiliar a la direccion de memoria que haya
        elementos=elementos->siguiente;//hacemos que nuestro puntero apunte a la siguiente direccion de memoria
        delete aux;//eliminamos nuestro auxiliar
    }
    n=0;
}
/**
TNodo_Lista* Lista::anterior(int i) //duda
{
    TNodo_Lista *ant=NULL;//declaramos un auxiliar para la direccion anterior y otro ara la siguiente
    TNodo_Lista *act=elementos;
    int v=1;//contador
    while(act!=NULL&&v<i) //mientras el actual tenga alguna direccion y no hayamos encontrado el que nos piden
    {
        ant=act;//el anterior se declara con la direccion del act
        act=act->siguiente;//y el act se va a por la siguiente direccion
        v++//se va sumando
    }
    return ant;
}
*/
void Lista::insertar(Paciente p)
{
    TNodo_Lista *nuevo=new TNodo_Lista;//declaramos un puntero vacio
    nuevo->datos=p;//metemos al pacente en el puntero

    if(elementos==NULL||p.historialClinico<elementos->datos.historialClinico)
    {
        //si no hay elementos o el historial clinico de nuestro paciente es menor que el del ultimo lo añadimos del tiron
        nuevo->siguiente=elementos;//A ver si me explico xd, seteamos el puntero que hay dentro de nuevo a la direccion de memoria que hay en el primer elemento de elmentos
        //despues seteamos elementos a la direccion de memoria que tenia nuestro puntero nuevo y se nos queda la direccion de memoria del nuevo antes que la segunda
        elementos=nuevo;
    }
    else
    {
        //creamos otro auxiliar
        TNodo_Lista *ant=elementos;
        //si no es nulo, hasta que llegemos a uno con un historial mayor
        while (ant->siguiente!=NULL&&ant->siguiente->datos.historialClinico<p.historialClinico)
        {
            ant=ant->siguiente;
        }
        //seteamos igual que antes
        nuevo->siguiente=ant->siguiente;
        ant->siguiente=nuevo;
    }
    n++;

}
void Lista::eliminar(int historial)
{
    TNodo_Lista *act=elementos;//el que vamos a eliminar
    TNodo_Lista *ant=NULL;

    //hacemos un bucle hasta que coincidan los historiales clinicos de los pacientes o haya un nulo
    while(act!=NULL&&act->datos.historialClinico!=historial)
    {
        ant=act;
        act=act->siguiente;
    }
    //si no hay un nulo,eliminamos el que toca
    if(act!=NULL)
    {
        if(ant==NULL)
        {
            elementos=act->siguiente;
        }
        else
        {
            ant->siguiente=act->siguiente;
        }
        delete act;
        n--;
    }

}
// Devuelve el número de pacientes en la lista
int Lista::longitud()
{
    return n;
}

// Comprueba si la lista no tiene nodos
bool Lista::esVacia()
{
    return (elementos == NULL);
}

// Devuelve los datos de un paciente en una posición dada
Paciente Lista::observar(int i)
{
    TNodo_Lista *act = elementos;
    int v = 1;
    while (v < i && act != NULL)
    {
        act = act->siguiente;
        v++;
    }
    return act->datos;
}
