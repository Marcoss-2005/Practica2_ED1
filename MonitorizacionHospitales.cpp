#include <iostream>
#include <cstring>
#include "MonitorizacionHospitales.h"
#include "hospital.h"

using namespace std;
bool MonitorizacionHospitales::existeHospital(int idHospital)
{
    //Metodo para comprobar si el hospital estas, declaramos un auxiliar y el booleano
    bool existe=false;
    Hospital *aux=this->primerHospital;
    //Con un while, recorremos los hospitales hasta que encontremos el que el usuario nos pide
    while(!existe)
    {
        //Ningun misterio vaya
        if(aux->getIdHospital()==idHospital)
        {
            existe=true;
        }
        else
        {
            aux=aux->getSiguienteHospital();
        }
    }
    return existe;
}
//Ahora vamos a comprobar si existe el paciente que nos piden y ver donde carajo esta
bool MonitorizacionHospitales::existePaciente(int idPaciente,cadena& lugar)
{
    //auxiliar y booleano
    bool encontrado=false;
    Hospital *aux=this->primerHospital;

    //con un while lo buscamos
    while(aux!=NULL&&!encontrado)
    {
        if(aux->buscarPaciente(idPaciente))
        {
            //Si lo encontrammos se lo decimos a nuestra variable
            encontrado=true;
            aux->getNombreHospital(lugar);
        }
        else
        {
            aux=aux->getSiguienteHospital();
        }
    }
    if(!encontrado)
    {
        //Si la op a no ha valido
        //Recorremos la cola global a ver si esta
        int totalGlobal=this->colaGlobal.longitud();
        for(int i=0; i<totalGlobal; i++)
        {
            Paciente Manolo=this->colaGlobal.primero();
            if(Manolo.historialClinico==idPaciente)
            {
                encontrado=true;
                strcpy(lugar,"COLA GLOBAL");
            }
            //Este bucle no puede terminar hasta que todo este como estaba antes
            this->colaGlobal.desencolar();
            this->colaGlobal.encolar(Manolo);
        }
    }
    return encontrado;

}
//Buscamos el hosptal solicitado
Hospital* MonitorizacionHospitales::buscarHospital(int idHospital)
{
    //Lo mismo que antes solo que ahora en vez de un booleano devolvemos un hospital
    Hospital *aux=this->primerHospital;
    Hospital *aDevolver;
    int enteroBoll=3;

    while(aux!=NULL&&enteroBoll==3)
    {
        if(aux->getIdHospital()==idHospital)
        {
            enteroBoll=2;
            aDevolver=aux;
        }
        aux=aux->getSiguienteHospital();

    }
    if(enteroBoll==3)
    {
        return NULL;
    }
    else
    {
        return aDevolver;
    }

}
Hospital* MonitorizacionHospitales::buscarHospitalConMasCamasLibres()
{
    Hospital *aux=this->primerHospital;
    Hospital *masCamas=NULL;

    //Lo mismo que antes pero una logica diferente
    while(aux!=NULL)
    {
        //Si la resta de los pacientes ingresados con las camas es mayor que el que tenemos se setea
        if(aux->getMaxCamas()-aux->getNumPacientesIngresados()>masCamas->getMaxCamas()-masCamas->getNumPacientesIngresados())
        {
            masCamas=aux;

        }
        aux=aux->getSiguienteHospital();

    }
    return masCamas;


}
//Este es para ver los huecos en la cola de espera(mas facil todavia que el de antes)
Hospital* MonitorizacionHospitales::buscarHospitalParaEspera()
{
    Hospital *aux=this->primerHospital;
    Hospital *menosEspera=NULL;

    while(aux!=NULL)
    {
        //Se setea cuando hay menos pacientes en espera en el hosptal que estamos comparando
        if(aux->getNumPacientesEnEspera()<menosEspera->getNumPacientesEnEspera())
        {
            menosEspera=aux;

        }
        aux=aux->getSiguienteHospital();

    }
    return menosEspera;


}
//Constructor y destructor de la clase
MonitorizacionHospitales::MonitorizacionHospitales()
{
    this->primerHospital=NULL;
    this->numHospitales=0;
}
MonitorizacionHospitales::~MonitorizacionHospitales()
{
    Hospital *aux;
    while (this->primerHospital != NULL)
    {
        aux = this->primerHospital;
        this->primerHospital = this->primerHospital->getSiguienteHospital();
        delete aux;
    }
}

//Para ver los hospitales que hay en el sistema
int MonitorizacionHospitales::getNumHospitales()
{
    return this->numHospitales;

}
//Vamo con el crear hospital
//sistema.crearHospital((char*)"Hospital Juan Ramón Jiménez", 1, 10, 21005, (char*)"PUBLICO");
bool MonitorizacionHospitales::crearHospital(cadena nombre, int idHospital,int maxCamas, int codPostal, cadena tipo)
{
    //Declaramos un entero como si fuera un booleano pero para que me haga mas cosas, junto a un auxiliar y el booleano que devolveremos
    bool podido =false;
    Hospital *aux=this->primerHospital;
    int enteroValidador=0;
    while(enteroValidador==0&&aux!=NULL)
    {
        //hasta que se encuentre no no queden hospitales
        if(aux->getSiguienteHospital()==NULL)
        {
            enteroValidador=2;
        }
        else if(aux->getSiguienteHospital()->getIdHospital()==idHospital)
        {
            enteroValidador++;

        }
        else
        {
            aux=aux->getSiguienteHospital();

        }


    }
    if(enteroValidador==2||aux==NULL)
    {
        //si no esta repe, lo metemos y lo ponemos el primero junto con los datos que nos llegan por parametros
        podido=true;

        Hospital* nuevo=new Hospital(nombre,idHospital,maxCamas,codPostal,tipo);
        if (this->primerHospital == NULL)
        {
            this->primerHospital = nuevo;
        }
        else
        {
            nuevo->setSiguienteHospital(this->primerHospital);
            this->primerHospital = nuevo;
        }

        this->numHospitales++;


    }

    return podido;

}
//Este es muy parecido, casi lo mismo solo que ahora lo eliminamos en vez de añadirlo
bool MonitorizacionHospitales::eliminarHospital(int idHospital)
{
    //Metemos un segundo auxiliar
    bool hospitalEliminado=false;
    Hospital *aux=this->primerHospital;
    Hospital *aux2=NULL;

    //Este lo he hecho con la logica de que salga del bucle si encuentra unhospital con el mismo id que el que le hemos pasado por parametros
    while(aux->getIdHospital()!=idHospital&&aux!=NULL)
    {
        aux=aux->getSiguienteHospital();

    }
    //Cuando salgamos del bucle podremos saber si lo podemos eliminar o no
    if(aux==NULL)
    {
        cout<<"Ese hospital que dices no esta"<<endl;
    }
    else if(aux->estaActivo())
    {
        cout<<"El hospital que has dicho esta activo"<<endl;
    }
    else
    {
        //El segundo auxiliar nos sirve para que cuando queramos eliminar el hospital no se pierda el siguiente a el
        aux2=aux;
        aux=aux->getSiguienteHospital();
        delete aux2;
        //importante actualizar el numero de hospitales
        this->numHospitales--;
        hospitalEliminado=true;
        cout<<"Ese hospital con id "<<idHospital<<" ha sido eliminado"<<endl;
    }
    return hospitalEliminado;
}
//Este metodo activara el hospital solicitado si es posible
bool MonitorizacionHospitales::activarHospital(int idHospital)
{
    //Metemos un entero booleano para los diferentes casos
    int enteroActivador=0;
    bool todoCorecto=false;
    if(this->primerHospital==NULL)
    {
        enteroActivador=4;
    }
    else
    {
        //Declaramos un auxiliar y buscamos el hospital
        Hospital *aux=this->primerHospital;


        while(aux!=NULL&&enteroActivador==0)
        {
            if(aux->getIdHospital()==idHospital )
            {
                enteroActivador=2;
            }
            else
            {
                aux=aux->getSiguienteHospital();
            }
        }
        //Si se ha encontrado el hospital y no estaba activo
        if(enteroActivador==2)
        {
            if(!aux->estaActivo())
            {
                aux->activar();
                todoCorecto=true;
                if(this->colaGlobal.esVacia())
                {
                    enteroActivador=5;
                }
                else
                {
                    //Si la cola global no esta vaciea, vamos metiendo pacientes en el hospital recien activado
                    while(aux->getNumPacientesIngresados()<aux->getMaxCamas()&&!this->colaGlobal.esVacia()&&enteroActivador==2)
                    {
                        Paciente Manolo=this->colaGlobal.primero();
                        if(aux->ingresarPaciente(Manolo))
                        {
                            this->colaGlobal.desencolar();
                        }
                        else
                        {
                            enteroActivador++;
                        }
                    }
                }

            }

        }


    }
    if(todoCorecto)
    {
        cout<<"Hospital activado con exito"<<endl;
    }
    else if(enteroActivador==4)
    {
        cout<<"No hay hospitales"<<endl;

    }
    else if(enteroActivador==2&&!todoCorecto)
    {
        cout<<"Ese hospital ya estaba activo"<<endl;
    }
    else if(enteroActivador==5)
    {
        cout<<"Nadie en la cola global"<<endl;
    }
    else if(enteroActivador==3)
    {
        cout<<"Ha habido un error ingresando los pacientes de la cola en el nuevo hospital activo"<<endl;
    }
    else
    {
        cout<<"Hospital no encontrado"<<endl;
    }
    return todoCorecto;
}
bool MonitorizacionHospitales::declararSinSangre(int idHospital)
{
    //Metodo para declarar un hospital sin sangre, lo primero es lo de siempre, comprobar que existe
    bool sinSangre=false;
    Hospital *aux=this->primerHospital;
    int encontrarHospital=0;
    if(aux==NULL)
    {
        encontrarHospital=1;
    }
    else
    {
        while(aux!=NULL&&encontrarHospital==0)
        {
            if(aux->getIdHospital()==idHospital)
            {
                encontrarHospital=2;
            }
            else
            {
                aux=aux->getSiguienteHospital();
            }

        }
        //Si lo encontramos miramos si estaba activo y si lo esta lo declaramos y nos ponemos modo true
        if(encontrarHospital==2)
        {
            if(aux->estaActivo())
            {
                aux->faltaSangre();
                sinSangre=true;
            }
            else
            {
                encontrarHospital=3;
            }
        }
    }
    if(encontrarHospital == 1)
    {
        cout << "No hay hospitales registrados." << endl;

    }
    else if(encontrarHospital == 3)
    {
        cout << "El hospital existe pero no esta ACTIVO." << endl;

    }
    else if(encontrarHospital == 0)
    {
        cout << "Hospital no encontrado." << endl;

    }
    return sinSangre;
}

bool MonitorizacionHospitales::desactivarHospital(int idHospital)
{
    //Metodo para desactivar hospital, lo mismo que antes solo que cambiamos a desactivado y hacemos que la gente no se nos pierda
    bool desactivado=false;
    Hospital *aux=this->primerHospital;
    int encontrarHospital=0;
    if(aux==NULL)
    {
        encontrarHospital=1;
    }
    else
    {
        while(aux!=NULL&&encontrarHospital==0)
        {
            if(aux->getIdHospital()==idHospital)
            {
                encontrarHospital=2;
            }
            else
            {
                aux=aux->getSiguienteHospital();
            }

        }
        if(encontrarHospital==2)
        {
            if(aux->estaActivo())
            {
                desactivado=true;
                //Si llegamos aqui es porque ha salido correcto, vamos a crear un puntero del tamaño de
                //el numero de pacientes que haya
                aux->desactivar();
                int totalIngresados=aux->getNumPacientesIngresados();
                int totalEnEspera=aux->getNumPacientesEnEspera();

                if(totalIngresados>0)
                {
                    //Creamos el puntero, exportamos los pacientes y los metemos en nuestro puntero
                    Paciente* nuevaCola=new Paciente[totalIngresados];
                    aux->exportarPacientesEnEspera(nuevaCola);
                    //los encolamos en la cola global hasta nuevo aviso
                    for(int i=0; i<totalEnEspera; i++)
                    {
                        this->colaGlobal.encolar(nuevaCola[i]);
                    }
                    //borramos nuestra variable ya que los pacientes ya estan guardados en la cola global
                    delete[] nuevaCola;
                }
                //
                if(totalEnEspera>0)
                {
                    //Este es igual que el otro solo que primero intentamos meterlo en el sistema y si no ya pues a la cola global
                    Paciente* nuevaLista=new Paciente[totalEnEspera];
                    aux->exportarPacientesIngresados(nuevaLista);
                    cadena lugar;
                    bool enEspera;
                    for (int i = 0; i < totalIngresados; i++)
                    {
                        if (!this->ingresarPacienteSistema(nuevaLista[i],lugar,enEspera))
                        {
                            this->colaGlobal.encolar(nuevaLista[i]);
                        }
                    }
                    delete[] nuevaLista;
                }
            }
            else
            {
                encontrarHospital=3;
            }
        }

    }
    if(encontrarHospital == 1)
    {
        cout << "No hay hospitales registrados." << endl;

    }
    else if(encontrarHospital == 3)
    {
        cout << "El hospital existe pero no esta ACTIVO." << endl;

    }
    else if(encontrarHospital == 0)
    {
        cout << "Hospital no encontrado." << endl;

    }
    else if(desactivado)
    {
        cout<<"Hospital desactivado con exito"<<endl;
    }
    return desactivado;

}
bool MonitorizacionHospitales::modificarCamasHospital(int idHospital, int maxCamas)
{
    //Esto es lo mismo que siempre pero para meter mas camas, primero buscamos el hospital
    bool camasModif=false;
    Hospital *aux=this->primerHospital;
    int encontrarHospital=0;
    if(aux==NULL&&maxCamas>=5)
    {
        encontrarHospital=1;
    }
    else
    {
        while(aux!=NULL&&encontrarHospital==0)
        {
            if(aux->getIdHospital()==idHospital)
            {
                encontrarHospital=2;
            }
            else
            {
                aux=aux->getSiguienteHospital();
            }

        }
        //Si lo encontramos cambiamos las camas
        if(encontrarHospital==2)
        {
            if(aux->estaInactivo())
            {
                aux->setMaxCamas(maxCamas);
                camasModif=true;

            }
            else
            {
                encontrarHospital=3;
            }
        }
    }
    if(encontrarHospital == 1)
    {
        cout << "No hay hospitales registrados o no son camas suficientes" << endl;

    }
    else if(encontrarHospital == 3)
    {
        cout << "El hospital existe pero no esta INACTIVO." << endl;

    }
    else if(encontrarHospital == 0)
    {
        cout << "Hospital no encontrado." << endl;

    }
    return camasModif;


}
bool MonitorizacionHospitales::ingresarPacienteSistema(Paciente p, cadena &lugarDestino, bool &enEspera)
{
    //Este es para meter un paciente en el sistama, intentamos encontrarlo para que no se duplique
    bool conseguido=false;
    int nHospitales=this->numHospitales;
    int masCamasLibres=0;
    int booleanoNum=0;

    Hospital *adecuado=NULL;

    for(int i=0; i<nHospitales&&booleanoNum!=3; i++)
    {
        Hospital* hActual=this->buscarHospital(i);
        if(hActual!=NULL&&hActual->estaActivo())
        {
            if(hActual->buscarPaciente(p.historialClinico))
            {
                booleanoNum=3;
            }
            else
            {
                //si no vamos cogiendo el hospital con mas camas libres
                if((this->buscarHospital(i)->getMaxCamas()-this->buscarHospital(i)->getNumPacientesIngresados())>masCamasLibres)
                {
                    adecuado=this->buscarHospital(i);
                    masCamasLibres=this->buscarHospital(i)->getMaxCamas()-this->buscarHospital(i)->getNumPacientesIngresados();
                    booleanoNum=1;
                    conseguido=true;
                }
            }
        }

    }
    if(!conseguido&&booleanoNum!=3&&this->primerHospital!=NULL)
    {
        //Si no tenemos hospital donde mandarlo aun, lo metemos en una lista de espera de alguno
        int menosPacientesEspera=this->primerHospital->getNumPacientesEnEspera();
        for(int i=0; i<nHospitales; i++)
        {
            //Si encontramos hueco se lo hacemos saber a nuestra variable
            Hospital* lulu=this->buscarHospital(i);
            if((lulu!=NULL&&lulu->getNumPacientesEnEspera())<menosPacientesEspera&&lulu->estaActivo())
            {
                adecuado=lulu;
                menosPacientesEspera=lulu->getNumPacientesEnEspera();
                booleanoNum=2;
                conseguido=true;
            }
        }
    }
    if(conseguido&&adecuado!=NULL)
    {
        adecuado->ingresarPaciente(p);
        if(booleanoNum==1)
        {
            adecuado->getNombreHospital(lugarDestino);
            enEspera=false;
        }
        else
        {
            strcpy(lugarDestino, "COLA GLOBAL");
            enEspera=true;
            this->colaGlobal.encolar(p);
        }
    }
    else
    {
        cout<<"El paciente ya existe"<<endl;
    }
    if(booleanoNum==3)
    {
        cout<<"El paciente ya existe"<<endl;
    }
    return conseguido;
}
//Este es igual pero para quitarlo de la lista de pacientes
bool MonitorizacionHospitales::bajaPacienteSistema(int idPaciente, cadena &lugarOrigen)
{
    bool conseguido=false;
    int nHospitales=this->numHospitales;
    Hospital *aux=NULL;

    //Buscamos el paciente en cada hospital
    for(int i=0; i<nHospitales; i++)
    {
        if(this->buscarHospital(i)->buscarPaciente(idPaciente))
        {
            conseguido=true;
            aux=this->buscarHospital(i);
        }

    }
    //Si no lo hemos encontrado buscamos en la cola global
    if(!conseguido)
    {
        int totGlobal=this->colaGlobal.longitud();
        Paciente Manolo;

        for(int i=0; i<totGlobal; i++)
        {
            Manolo=this->colaGlobal.primero();
            this->colaGlobal.desencolar();

            if(Manolo.historialClinico==idPaciente)
            {
                conseguido=true;
                strcpy(lugarOrigen,"COLA GLOBAL");

            }
            else
            {
                this->colaGlobal.encolar(Manolo);
            }
        }
    }
    else
    {
        //Si lo encontramos en el hospital lo damos de baja y metemos el primero de la cola global en el hospital
        aux->getNombreHospital(lugarOrigen);
        aux->bajaPaciente(idPaciente);
        if(aux->getNumPacientesIngresados() < aux->getMaxCamas() && !this->colaGlobal.esVacia())
        {
            Paciente pGlobal = this->colaGlobal.primero();
            this->colaGlobal.desencolar();
            aux->ingresarPaciente(pGlobal);
        }

    }
    return conseguido;

}


void MonitorizacionHospitales::mostrarInformacionHospitales(int n)
{
    //esto es para mostrar la info de los hospitales
    if(n==-1)
    {
        Hospital *aux=this->primerHospital;
        int a=0;
        if (aux == NULL)
        {
            a=3;
        }
        else
        {
            while(aux!=NULL)
            {
                cadena nombre;
                aux->getNombreHospital(nombre);

                //Queremos saber las camas disponibles y los huecos en la cola
                int camasDisponibles = aux->getMaxCamas() - aux->getNumPacientesIngresados();
                int huecosColaDisponibles = 10 - aux->getNumPacientesEnEspera(); // Pongo 10 por poner
                float gravedadMedia = aux->gravedadMedia(); // este metodo lo voy a crear nuevo para cumplir con el enuncdo

                cout << "------------------------------------------" << endl;
                cout << "ID: " << aux->getIdHospital() << endl;
                cout << "Nombre: " << nombre << endl;
                cout << "Estado: " << (aux->estaActivo() ? "Activo" : "Inactivo") << endl;

                cout << "Camas disponibles: " << camasDisponibles << endl;
                cout << "Huecos libres en cola: " << huecosColaDisponibles << endl;
                cout << "Gravedad media de ingresados: " << gravedadMedia << endl;

                aux = aux->getSiguienteHospital();
            }
        }

    }
    else
    {
        Hospital *aux=this->primerHospital;
        int a=0;
        if (aux == NULL)
        {
            a=3;
        }
        else
        {
            while(a==0)
            {
                if(aux->getIdHospital()==n)
                {
                    cadena nombre;
                    aux->getNombreHospital(nombre);
                    cout << "------------------------------------------" << endl;
                    cout << "ID: " << aux->getIdHospital() << endl;
                    cout << "Nombre: " << nombre << endl;
                    if(aux->estaActivo())
                    {
                        cout << "Estado: Activo"<< endl;
                    }
                    else
                    {
                        cout << "Estado: Inactivo"<< endl;

                    }
                    a++;
                }
                else if(aux->getSiguienteHospital()==NULL)
                {
                    a+2;
                }
                else
                {
                    aux=aux->getSiguienteHospital();

                }
            }
        }
        if(a==2)
        {
            cout<<"No se ha encontrado el hospital solicitado"<<endl;
        }
        else if(a==3)
        {
            cout << "La lista de hospitales esta vacia." << endl;

        }
    }
    //Metodo no terminado ya que ni lo he repasado ni doy todo lo que tengo que dar
}

int MonitorizacionHospitales::getPosicionHospital(int idHospital)
{
    //Esto es para saber donde esta el hospital que necesitamos saber
    int a=-1;
    Hospital *aux=this->primerHospital;
    bool encontrado=false;

    while(aux!=NULL&&!encontrado)
    {
        if(aux->getIdHospital()==idHospital)
        {
            encontrado=true;
            a++;

        }
        else if(aux->getSiguienteHospital()!=NULL)
        {
            a++;
            aux=aux->getSiguienteHospital();
        }
        else
        {
            aux=NULL;
        }
    }
    if(a>-1&&aux!=NULL)
    {
        a=aux->getIdHospital();
        Hospital *villanueva=buscarHospital(idHospital);
        cout<<"Info del hospital: "<<endl;
        cout << "ID: " << aux->getIdHospital() << endl;
        cout << "PACIENTES INGRESADOS: " << endl;
        villanueva->mostrarPacientesIngresados();
        cout << "PACIENTES EN ESPERA: " << endl;
        villanueva->mostrarPacientesEnEspera();

    }
    else
    {
        cout<<"No tenemos es hospital"<<endl;
    }
    return a;

}
void MonitorizacionHospitales::mostrarInformacionColaGlobal()
{
    // 1. Obtenemos el número total de personas esperando en el sistema
    int total = this->colaGlobal.longitud();

    cout << "================================================" << endl;
    cout << "      PACIENTES EN LA COLA GLOBAL DEL SISTEMA    " << endl;
    cout << "================================================" << endl;

    if (total == 0)
    {
        cout << "La cola global esta vacia actualmente." << endl;
    }
    else
    {
        cout << "Total de pacientes: " << total << endl;
        cout << "------------------------------------------------" << endl;

        for (int i = 0; i < total; i++)
        {
            Paciente pac = this->colaGlobal.primero();

            cout << "Paciente " << i << ": " << pac.nombreCompleto<< " | Patologia: " << pac.patologia <<" | Gravedad: "<<pac.gravedad<<" | Tipo de sangre: "<<pac.tipoSangre<< endl;

            this->colaGlobal.desencolar();
            this->colaGlobal.encolar(pac);
        }
    }
    cout << "================================================" << endl << endl;
}
