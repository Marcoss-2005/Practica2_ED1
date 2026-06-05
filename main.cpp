#include <iostream>
#include <string>
#include <cstring>
#include "MonitorizacionHospitales.h"
#include "hospital.h"
#include "paciente.h"

using namespace std;
void generarDatos(MonitorizacionHospitales &gestor);

int main()
{
    MonitorizacionHospitales gestor;
    generarDatos(gestor);

    int op=-1;
    do
    {
        cout<<"--------------------------------"<<endl;
        cout<<"Sistema de monitorizacion medica"<<endl;
        cout<<"--------------------------------"<<endl;
        cout<<"1.-Consultar hospital"<<endl;
        cout<<"2.-Listar todos los hospitales"<<endl;
        cout<<"3.-Dar de alta un nuevo hospital"<<endl;
        cout<<"4.-Eliminar hospital"<<endl;
        cout<<"5.-Activar hospital"<<endl;
        cout<<"6.-Desactivar hospital"<<endl;
        cout<<"7.-Declarar hospital 'SIN SANGRE'"<<endl;
        cout<<"8.-Modificar capacidad de camas'"<<endl;
        cout<<"9.-Ingresar paciente"<<endl;
        cout<<"10.-Dar de baja paciente"<<endl;
        cout<<"11.-Mostrar cola global"<<endl;
        cout<<"0.-Salir"<<endl;

        cin>>op;
        //Esto es para que no falle el programa si le meto una letra por la cara
        while (cin.fail() || op < 0 || op > 11)
        {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "[ERROR] Por favor, introduzca un numero valido entre 0 y 11: ";
            cin >> op;
        }
        switch(op)
        {
        case 1:
        {
            int i;
            cout<<"Por favor, introduzca el identificador del hospital que desea consultar"<<endl;
            cin>>i;
            gestor.getPosicionHospital(i);
            break;

        }
        case 2:
        {
            gestor.mostrarInformacionHospitales(-1);
            break;


        }
        case 3:
        {
            string nombre;
            int id;
            int n_camas;
            int codigo_postal;
            char tipo[20];

            cout<<"Introduzca el nombre del hospital"<<endl;
            cin>>nombre;
            do
            {
                cout<<"Introduzca el identificador del hospital(Por favor introduzca un numero)"<<endl;
                cin>>id;
                //Lo mismo, para que no falle si le meto una letra, basicamente resetea el cin
                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000,'\n');
                    id=-1;
                }
            }
            while(id<=0);
            do
            {
                cout<<"Introduzca el numero de camas del hopital(Por favor introduzca un numero, mayor o igual q 5)"<<endl;
                cin>>n_camas;
                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000,'\n');
                    n_camas=-1;
                }
            }
            while(n_camas<5);
            do
            {
                cout<<"Introduzca el codigo postal"<<endl;
                cin>>codigo_postal;
                //Esto es del chati pero vamos que se entiende(me falto iq)
            }
            while(codigo_postal < 10000 || codigo_postal > 99999);
            do
            {
                cout<<"Introduzca el tipo de hospital(publico o privado)"<<endl;
                cin>>tipo;
                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000,'\n');
                    codigo_postal=-1;
                }
            }
            while(strcmp(tipo,"publico")!=0&&strcmp(tipo,"privado")!=0);

            if(gestor.crearHospital((char*)nombre.c_str(), id, n_camas, codigo_postal, tipo))
            {
                cout<<"Hospital creado con exito"<<endl;
            }
            else
            {
                cout<<"Ha habido algun problema"<<endl;
            }
            break;

        }
        case 4:
        {
            int id=-1;
            do
            {
                cout<<"Introduzca el identificador del hospital que desea eliminar"<<endl;
                cin>>id;
                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000,'\n');
                    id=-1;
                }
            }
            while(id<=0);
            if(gestor.eliminarHospital(id))
            {
                cout<<"Hospital eliminado con exito"<<endl;
            }

            break;

        }
        case 5:
        {
            int id;
            while(id<=0)
            {
                cout<<"Introduzca el identificador del hospital el cual desea activar"<<endl;
                cin>>id;
                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000,'\n');
                    id=-1;
                }
            }
            gestor.activarHospital(id);
            break;

        }
        case 6:
        {
            int id=-1;
            do
            {
                cout<<"Introduzca el identificador del hospital el cual desea desactivar"<<endl;
                cin>>id;
                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000,'\n');
                    id=-1;
                }
            }
            while(id<=0);
            gestor.desactivarHospital(id);
            break;
        }
        case 7:
        {
            int id;
            do
            {
                cout<<"Introduzca el identificador del hospital el cual desea declarar 'SIN SANGRE'"<<endl;
                cin>>id;
                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000,'\n');
                    id=-1;
                }
            }
            while(id<=0);
            gestor.declararSinSangre(id);
            break;
        }
        case 8:
        {
            int id=-1;
            int camasN;
            do
            {
                cout<<"Introduzca el identificador del hospital"<<endl;
                cin>>id;
                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000,'\n');
                    id=-1;
                }
            }
            while(id<=0);
            do
            {
                cout<<"Introduzca el nuevo numero de camas(mas de 5)"<<endl;
                cin>>camasN;
                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000,'\n');
                    camasN=-1;
                }
            }
            while(camasN<=5);
            gestor.modificarCamasHospital(id,camasN);
            break;

        }
        case 9:
        {
            string nombre;
            int numClinico;
            string tipoSangre;
            int gradoGravedad;
            string patologia;
            cout<<"Digame su nombre"<<endl;
            cin>>nombre;
            do
            {
                cout<<"Digame su numClinico"<<endl;
                cin>>numClinico;
                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000,'\n');
                    numClinico=-1;
                }
            }
            while(numClinico<=0);
            cout<<"Digame su tipo de sangre"<<endl;
            cin>>tipoSangre;

            do
            {
                cout<<"Digame su estado(Numero del 1 al 5 siendo 1 poco grave)"<<endl;
                cin>>gradoGravedad;
                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000,'\n');
                    gradoGravedad=-1;
                }
            }
            while(gradoGravedad<1||gradoGravedad>5);
            cout<<"Cual es su patologia"<<endl;
            cin>>patologia;
            Paciente p;

            //Como no tenemos ningun constructor, pues le metemos por parametros las cosas al paciente
            strcpy(p.nombreCompleto, nombre.c_str());
            p.historialClinico = numClinico;
            strcpy(p.tipoSangre, tipoSangre.c_str());
            p.gravedad = gradoGravedad;
            strcpy(p.patologia, patologia.c_str());
            cadena lugarDestino;
            bool enEspera = false;
            if(gestor.ingresarPacienteSistema(p,lugarDestino,enEspera))
            {
                cout<<"Paciente ingresado con exito"<<endl;
            }
            break;

        }
        case 10:
        {
            int numHistorialClinico;
            do
            {
                cout<<"Digame su numero de historial Clinico"<<endl;
                cin>>numHistorialClinico;
                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000,'\n');
                    numHistorialClinico=-1;
                }
            }while(numHistorialClinico<=0);
            cadena lugarOrigen;

            if(!gestor.bajaPacienteSistema(numHistorialClinico,lugarOrigen)){
                cout<<"Paciente no encontrado"<<endl;
            };
            break;

        }
        case 11:
        {
            gestor.mostrarInformacionColaGlobal();
            break;
        }
        }
    }
    while(op!=0);

}


