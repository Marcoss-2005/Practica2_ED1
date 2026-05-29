#include <iostream>
#include <string>
#include <cstring>
#include "hospital.h"
#include "cola.h"
#include "lista.h"

using namespace std;
typedef char cadena[50];

Hospital::Hospital(cadena nom, int id, int mC, int cP, cadena tH)
{
    //Constructor de la clase
    //Aqui seteamos las variables que hacen falta
    // 'maxCamas' y 'codigoPostal', con, respectivamente, 'nom', 'id', 'mC', 'cP' y 'tH'.
    strcpy(this->nombreHospital,nom);
    this->idHospital=id;
    this->maxCamas=mC;
    this->codigoPostal=cP;
    strcpy(this->tipoHospital,tH);
    strcpy(this->estado,"INACTIVO");
    this->siguienteHospital=NULL;
}
Hospital::~Hospital()
{
    //Aqui tenemos el destructor, no hace mucho, solo limpiar todo cuando el usuario lo pida
    while(!this->pacientesIngresados.esVacia())
    {
        int id = this->pacientesIngresados.observar(0).historialClinico;
        this->pacientesIngresados.eliminar(id);
    }
    while(!this->pacientesEnEspera.esVacia())
    {
        this->pacientesEnEspera.desencolar();
    }
    this->siguienteHospital = NULL;
}
//Ahora vienen unos pocos de getters, lo que hacen es permitirte acceder a variables privadas
void Hospital::getNombreHospital(cadena &nH)
{
    strcpy(nH,nombreHospital);
}
int Hospital::getIdHospital()
{
    return this->idHospital;
}
int Hospital::getMaxCamas()
{
    return this->maxCamas;
}
int Hospital::getNumPacientesIngresados()
{
    return this->pacientesIngresados.longitud();
}
int Hospital::getNumPacientesEnEspera()
{
    return this->pacientesEnEspera.longitud();
}
Hospital* Hospital::getSiguienteHospital()
{
    return this->siguienteHospital;
}
//Aqui vienen los setters, estos hacen que cambie un atributo privado dado un parametro que le envias tu
void Hospital::setSiguienteHospital(Hospital* hospi)
{
    this->siguienteHospital=hospi;
}
bool Hospital::setMaxCamas(int camas)
{
    //cumplimos con lo que nos pide el enunciado y devolvemos lo que toque
    if((strcmp(this->estado,"INACTIVO")==0)&&camas<5)
    {
        this->maxCamas=camas;
        return true;
    }
    else
    {
        return false;
    }
}
bool Hospital::buscarPaciente(int idPaciente)
{
    //Metodo para buscar paciente
    //Declaramos una cola auxiliar, 2 enteros, uno para el pacientes espera, y otro para saber donde se encontraba el paciente en el caso en el que se encuentre
    Cola aux=this->pacientesEnEspera;
    bool encontrado=false;
    int a=0;
    int acabarEspera=0;

    //esta cola la recorro con un while
    while(pacientesEnEspera.longitud()>acabarEspera)
    {
        //Declaramos un paciente que sea el primero
        //y despues vamos comprando hasta que llegemos al final, si se encuentra, cambian las
        //2 variables que me dan informacion
        Paciente Manolo=this->pacientesEnEspera.primero();

        if(Manolo.historialClinico==idPaciente)
        {
            a=1;
            encontrado=true;
        }
        acabarEspera++;
        this->pacientesEnEspera.desencolar();
        this->pacientesEnEspera.encolar(Manolo);
    }
    if(encontrado!=true)
    {
        //Y esta lista la recorro con un for para variar un poco
        for(int i=0; i<this->pacientesIngresados.longitud(); i++)
        {
            if(pacientesIngresados.observar(i).historialClinico==idPaciente)
            {
                a=2;
                encontrado=true;
            }
        }

    }
    //esto para decirle algo al usuario
    if(a==1)
    {
        cout<<"Su paciente ha sido encontrado en los pacientes en espera"<<endl;
    }
    else if(a==2)
    {
        cout<<"Su paciente ha sido encontrado en los pacientes ingresados"<<endl;
    }
    return encontrado;

}
bool Hospital::ingresarPaciente(Paciente p)
{
    //declaro el booleano que devolveremos y un entero para dar un mensaje u otro
    bool podido=false;
    int a=0;

    //Primero hay que comprobar si hay gente esperando para ser ingresada
    if(this->pacientesEnEspera.esVacia())
    {
        if((this->getMaxCamas()>this->getNumPacientesIngresados()))
        {
            podido=true;
            this->pacientesIngresados.insertar(p);
            a=1;
        }
    }
    else
    {
        //como la gravedad la comprobamos en el metodo encolar, solo tenemos que llamar al metodo y pasarle el paciente por parametros
        this->pacientesEnEspera.encolar(p);
        a=2;
        podido=true;
    }
    //El mensaje de siempre
    if(a==1)
    {
        cout<<"Paciente igresado en el hospital"<<endl;

    }
    else if(a==2)
    {
        cout<<"Paciente ingresado en espera"<<endl;
    }
    return podido;
}
bool Hospital::bajaPaciente(int idPaciente)
{
    //lo de siempre
    bool baja=false;
    int a=0;
    int acabarEspera=0;

    //para encontrarle
    while(this->pacientesEnEspera.longitud()>acabarEspera)
    {
        //Igual que antes pero aqui lo quito de la lista y ya esta
        Paciente Manolo=this->pacientesEnEspera.primero();

        this->pacientesEnEspera.desencolar();
        if(Manolo.historialClinico==idPaciente)
        {
            a=1;
            baja=true;
        }
        else
        {
            this->pacientesEnEspera.encolar(Manolo);
        }
        acabarEspera++;
    }
    //Este es mas facil, para eliminar de la lista
    if(!baja)
    {
        Paciente nuevo=pacientesIngresados.observar(idPaciente);
        if(nuevo.historialClinico>0)
        {
            pacientesIngresados.eliminar(nuevo.historialClinico);
            baja=true;
        }

    }
    if(a==2)
    {

        cout<<"El paciente ha sido quitado de la lista de espera"<<endl;
    }
    else if (a==1)
    {
        cout<<"El paciente ha sido quitado del hospital"<<endl;

    }
    else
    {
        cout<<"No hemos encontrado a el paciente"<<endl;
    }
    return baja;
}
void Hospital::exportarPacientesIngresados(Paciente *ingresados)
{
    //Este metodo lo usaremos cuando querramos quitar un hospital y haga falta transladar pacientes
    int a=this->pacientesIngresados.longitud();
    for(int i=0; i<a; i++)
    {
        ingresados[i]=this->pacientesIngresados.observar(i);

    }

}
void Hospital::exportarPacientesEnEspera(Paciente *espera)
{
    //Lo mismo que el anterior pero con la cola
    int a=this->pacientesEnEspera.longitud();
    for(int i=0; i<a; i++)
    {
        Paciente Manolo=this->pacientesEnEspera.primero();
        espera[i]=this->pacientesEnEspera.primero();
        this->pacientesEnEspera.desencolar();
        this->pacientesEnEspera.encolar(Manolo);
    }

}
//booleano para saber si el hospital esta activo
bool Hospital::estaActivo()
{
    return (strcmp("ACTIVO",this->estado)==0);

}
//Para saber si esta incactivo
bool Hospital::estaInactivo()
{
    return (strcmp("INACTIVO",this->estado)==0);
}
//Activar el hospital si es posible
bool Hospital::activar()
{
    bool activado=false;
    if(this->estaInactivo())
    {
        activado=true;
    }
    else if(strcmp(this->estado,"SIN SANGRE")==0)
    {
        activado=true;
    }

    if(activado)
    {
        strcpy(this->estado, "ACTIVO");
    }
    return activado;
}
//Lo mismo pero al reves
bool Hospital::desactivar()
{
    bool desactivado=false;

    if(this->estaActivo())
    {
        desactivado=true;
    }
    if(desactivado)
    {
        strcpy(this->estado, "INACTIVO");
        while (!this->pacientesIngresados.esVacia())
        {
            this->pacientesIngresados.eliminar(1);
        }
        while (!this->pacientesEnEspera.esVacia())
        {
            this->pacientesEnEspera.desencolar();
        }
    }
    return desactivado;
}
//metodo para declarar hosptal falto de sangre
bool Hospital::faltaSangre()
{
    //declaramos el booleano y miramos si esta ya sin sangre
    bool sangre=true;
    if (this->estaActivo() && strcmp(this->estado, "SIN SANGRE") != 0)
    {
        strcpy(this->estado, "SIN SANGRE");

        while (!this->pacientesEnEspera.esVacia())
        {
            this->pacientesEnEspera.desencolar();
        }
    }
    else
    {
        sangre=false;

    }
    return sangre;
}

void Hospital::mostrarPacientesIngresados()
{
    //recorremos la lista de los pacientes ingresados y los mostramos todos
    int contador=0;
    int total=this->getNumPacientesIngresados();

    if(total==0)
    {
        cout<<"No hay pacientes ingresados"<<endl;
    }
    else
    {
        while(contador<total)
        {
            Paciente pac = this->pacientesIngresados.observar(contador);
            cout << "Paciente " << contador << ": " << pac.nombreCompleto<< " | Patologia: " << pac.patologia <<" | Gravedad: "<<pac.gravedad<<" | Tipo de sangre: "<<pac.tipoSangre<< endl;
            contador++;
        }
    }
}
void Hospital::mostrarPacientesEnEspera()
{
    //Lo mismo que antes
    int total=this->getNumPacientesEnEspera();

    if(total==0)
    {
        cout<<"No hay pacientes en espera"<<endl;
    }
    else
    {
        for(int i=0; i<total; i++)
        {
            Paciente pac=this->pacientesEnEspera.primero();
            cout << "Paciente " << i << ": " << pac.nombreCompleto<< " | Patologia: " << pac.patologia <<" | Gravedad: "<<pac.gravedad<<" | Tipo de sangre: "<<pac.tipoSangre<< endl;
            this->pacientesEnEspera.desencolar();
            this->pacientesEnEspera.encolar(pac);
        }
    }
}
void Hospital::mostrarInformacion()
{
    //Este esta bonito xd, na tonteria de metodo
    cout << "================================================" << endl;
    cout << "           INVENTARIO DE HOSPITAL               " << endl;
    cout << "================================================" << endl;
    cout << "Nombre:    " << this->nombreHospital << endl;
    cout << "ID:        " << this->idHospital << endl;
    cout << "Direccion: CP " << this->codigoPostal << endl;
    cout << "Tipo:      " << this->tipoHospital << endl;
    cout << "Estado:    " << this->estado << endl;
    cout << "Capacidad: " << this->maxCamas << " camas totales." << endl;
    cout << "------------------------------------------------" << endl;

    this->mostrarPacientesIngresados();

    cout << "------------------------------------------------" << endl;

    this->mostrarPacientesEnEspera();

    cout << "================================================" << endl;
}
float Hospital::gravedadMedia()
{
    float grav=0;
    int pac=this->getNumPacientesIngresados();

    if(pac>0)
    {
        for(int i=0; i<pac; i++)
        {
            grav=grav+this->pacientesIngresados.observar(i).gravedad;
        }
        grav=grav/pac;
    }
    return grav;

}
