#include<iostream>
#include<sstream>
#include<string.h>
#include<fstream>
#include<stdlib.h>
using namespace std;



//Estructura Ticket
struct Ticket {
    char rut_funcionario[10];
    int day_of_month;
    char time[6];
};



//Estructura Validos
struct Validos{
    string nservicio;
    string funcionario;
    int faltas;
    int totales;

};



//Arreglo de struct Validos con size de 150 debido a segmentation fault
Validos Personal[150];



/*****
*   bool Rango
******
*   La funcion verifica si una hora esta dentro de un rango horario dado
******
*   Input:
*   string min : String que representa la hora de inicio de la comida
*   string max : String que representa la hora de termino de la comida
*   string comparar : String que representa la hora a comparar
******
*   Returns:
*   bool flag2, Booleano que representa si la hora esta dentro de un rango, retorna true si esta dentro de la hora y false si no
*****/
bool Rango(string min, string max, string comparar){
    string hora1, minuto1;                              
    bool flag2 = NULL;        
    stringstream acomparar(min);

    getline(acomparar, hora1, ':');
    getline(acomparar, minuto1, ':');
    

    if(stoi(hora1) == 23){
        if(min < comparar || comparar < max){
            flag2 = true;
        }else{
            flag2 = false;
        }
    }else{
        if(min < comparar && comparar < max){
            flag2 = true;
        }else{
            flag2 = false;
        }
    }
    return flag2;
     
}



//Contador global 1
int contador = 0;



/*****
*   void Condicion
******
*   La funcion verifica si la comida esta en alguna hora permitida
******
*   Input:
*   string identificacion : String que representa el rut del funcionario
*   string nombre : String que representa el nombre de la comida
******
*   Returns:
*   void, Al ser tipo void no retorna nada
*****/
void Condicion(string identificacion, string nombre){
    Personal[contador].nservicio = nombre;
    Personal[contador].funcionario = identificacion;
    if(nombre == ""){
        Personal[contador].faltas++;

    }else{
        Personal[contador].faltas;
        Personal[contador].totales++;
    }
    contador++;
}



/*****
*   void Revision
******
*   La funcion revisa si cumple los requisitos para haber utilizado el Menu
******
*   Input:
*   string nombreArchivo : String que representa el nombre del archivo que contiene las comidas
*   Ticket user : Objeto tipo Ticket que representa un usuario
******
*   Returns:
*   void, Al ser tipo void no retorna nada
*****/
void Revision(string nombreArchivo, Ticket user){
    int valor = 0;
    bool flag = NULL;
    ifstream archivo(nombreArchivo.c_str());
    string line;
    getline(archivo, line); //Cantidad de comidas
    while (getline(archivo, line)){
        stringstream input_stringstream(line);
        string nombre, diario, mensual, inicio, fin;
        //Se extrae la informacion
        getline(input_stringstream, nombre, ' ');
        getline(input_stringstream, diario, ' ');
        getline(input_stringstream, mensual, ' ');
        getline(input_stringstream, inicio, ' ');
        getline(input_stringstream, fin, ' ');
        
        flag = Rango(inicio,fin,user.time);
        if(flag){
            Condicion(user.rut_funcionario, nombre);
            valor++;
        }
    }
    if(valor == 0){
        Condicion(user.rut_funcionario, "");

    }
    valor = 0;

}



//Inicio de funciones para eliminar repeticiones



//Contdaor global 2
int cont_glob = 0;



/*****
*   void buscar
******
*   La funcion comprueba si existe la palabra, es una Funcion Auxiliar
******
*   Input:
*   string pal : String que representa la palabra a buscar
*   string lista[] : Array de string que almacena todos los rut de los usuarios
*   int tam : Entero que representa el largo del array Lista[]
******
*   Returns:
*   void, Al ser tipo void no retorna nada
*****/
void buscar(string pal, string lista[], int tam){
   int i = 0;
   char band;
   while(pal != lista[i] && i<tam){
       i++;
   }
   if(pal == lista[i])
       cout<<"";
   else
       lista[cont_glob] = pal;
       cont_glob++;
}



/*****
*   string* DelRepetidos
******
*   La funcion almacena en otra lista los repetidos sin usuarios en blanco
******
*   Input:
*   string rut_fin[] : Array de string que almacena todos los rut de los usuarios sin repetir y sin espacios entremedio
*   int la : Entero que representa el largo del array rut_fin[]
*   int tam : Entero que representa el largo del array rut_sinrep[]
******
*   Returns:
*   string* rut_fin, Array de string que almacena todos los rut de los usuarios sin repetir
*****/
string* DelRepetidos(string rut_fin[], string rut_sinrep[], int la, int tam){
    int con = 0;
    for(int j = 0; j<tam; j++){
        if(rut_sinrep[j] != ""){
            rut_fin[con] = rut_sinrep[j];
            con++;
        }
    }
    return rut_fin;
}



/*****
*   void repetidos
******
*   La funcion almacena en otra lista los repetidos con usuarios en blanco y muestra los resultados finales
******
*   Input:
*   string arreglo[] : Array de string que representa
*   int largo : Entero que representa el numero de rut que tiene el archivo
******
*   Returns:
*   void, Al ser tipo void no retorna nada
*****/
void repetidos(string arreglo[], int largo){
    string rut_sinrep[largo];
    int contgen = 0;
    for(int h = 0; h<largo; h++){
        buscar(arreglo[h], rut_sinrep, largo);
    }

    for(int j = 0; j<largo; j++){
        if(rut_sinrep[j] != ""){
            contgen++;
        }
    }
    

    string run_id[contgen];
    string *val = DelRepetidos(run_id, rut_sinrep, contgen, largo);

    for(int h = 0; h<contgen; h++){
        int faltas_v = 0;
        int totales_v = 0;
        for(int f = 0; f<largo; f++){
            if(val[h] == Personal[f].funcionario){
                faltas_v += Personal[f].faltas;
                totales_v += Personal[f].totales;
            }
        }
        cout<<val[h]<<" "<<faltas_v<<"/"<<totales_v<<endl;
        
    }


}



//Final de funciones para eliminar repeticiones



/*****
*   void maquina_tickets
******
*   La funcion se encarga de leer el archivo binario y buscar las personar repetidas en la lista
******
*   Input:
*   string nom_arch : String que corresponde al nombre del archivo del binario con la informacion
******
*   Returns:
*   void, Al ser tipo void no retorna nada
*****/
void maquina_tickets(string nom_arch){
    int e;
    ifstream arch(nom_arch, ios::binary);
    arch.read((char *)&e, sizeof(int));
    Ticket *p = new Ticket[e];
    string *rut = new string[e];
    for(int k=0; k<e; k++){
        arch.read((char *)&p[k], sizeof(Ticket));
    }
    arch.close();

    //Array de string que almacena los rut
    string rut_conrep[e];
    for(int y = 0; y<e; y++){
        rut_conrep[y] = p[y].rut_funcionario;
        for(int u = 0; u<e; u++){
            if(strcmp(p[y].rut_funcionario, p[u].rut_funcionario) == 0){
                Revision("servicios.txt",p[u]);
            }
        }
        rut[y] = p[y].rut_funcionario;
        
    }

    repetidos(rut_conrep,e);
}



//Funcion main
int main(){
    maquina_tickets("tickets.dat");
    return 0;
}