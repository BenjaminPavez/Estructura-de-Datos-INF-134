#include<iostream>
#include<string>
#include <cmath>
#define M 128
typedef int tipoClave;
using namespace std;


//Estructura Diccionario
struct Diccionario {
    string palabra;
    string definicion;
    int vistas = 0;
};


//Estructura Diccionario
struct ranura {
    tipoClave clave;
    Diccionario info;
};


//Ranura
ranura HT[M];



//TDA del diccionario
class CacheDiccionario{
    private:
        string termino, significado;
        int total, conocidos, desconocidos;
        int accesses = 0, hits = 0, misses = 0, cleanups = 0;

    public:
        CacheDiccionario();
        bool query(string, string&);
        void insert(string, string);
        void querystats(int&, int&, int&);
        void perfstats(int&, int&, int&, int&);
};



//Se definen variables "globales"
int aumento = -1;
int max_visitas = -1;
int min_visitas = 100000;
int del = 0, accesos = 0, count1 = 0, count2 = 0, pos = 0;
int total_search = 0, conocidos_search = 0, desconocidos_search = 0;



/*****
* int p()
******
* La funcion hace parte de las politicas de colisiones, ya que esta salta casillas de la ranura si dicha ranura esta ocupada.
******
* Input:
* int k : La funcion recibe un entero con el largo de la palabra.
* int i : La funcion recibe un entero con la cantidad de colisiones.
******
* Returns:
* La funcion retorna un entero con la suma de los dos valores.
*****/
int p(int k, int i) {
    return k+i;
}



/*****
* int h()
******
* La funcion calcula el largo de una palabra.
******
* Input:
* string x : La funcion recibe un string con la palabra a insertar.
******
* Returns:
* La funcion retorna un entero con la suma de la cantidad del letras de la palabra.
*****/
int h(string x) {
    int i, sum;
    for (sum = 0, i = 0; x[i] != '\0'; i++)
        sum += 1;
    return sum;
}



/*****
* int hashInsert()
******
* La funcion inserta en la posicion señalada la palabra con su correspondiente significado.
******
* Input:
* ranura HT[] : La funcion recibe un ranura con la informacion previamente insertada.
* tipoClave k : La funcion recibe un entero tipoclave el cual representa la clave a insertar.
* Diccionario I : La funcion recibe una estructura tipo diccionario con la informacion de la palabra y su definicion.
******
* Returns:
* La funcion retorna un entero con la posicion la la cual se inserto, si retorna -1, la informacion no se inserto.
*****/
int hashInsert(ranura HT[], tipoClave k, Diccionario I) {
    int inicio, i;
    int pos = inicio = h(I.palabra);
    for (i = 0; i<M; i++){
        if(HT[i].clave == h(I.palabra)){
            pos = (h(I.palabra) + p(h(I.palabra), i)) % M; // próxima ranura en la secuencia
        }
    }
    if (HT[pos].clave == h(I.palabra)){
        return -1; // inserción no exitosa: clave repetida
    }else {
        HT[pos].clave = h(I.palabra);
        HT[pos].info = I;
        return pos; // inserción exitosa
    }
}



/*****
* string hashSearch()
******
* La funcion recorre la tabla de hashing en busca de la palabra señalada.
******
* Input:
* ranura HT[] : La funcion recibe un ranura con la informacion previamente insertada.
* Diccionario I : La funcion recibe una estructura tipo diccionario con la informacion de la palabra y su definicion.
******
* Returns:
* La funcion retorna string "vacio" si es que la palabra no fue encontrada o la definicion de la palabra.
*****/
string hashSearch(ranura HT[], Diccionario I){
    string vacio = "vacio";
    for(int j=0; j<M; j++){
        if(HT[j].info.palabra == I.palabra){
            cout<<"Palabra Encontrada: "<<HT[j].info.palabra<<endl;
            count2++;
            HT[j].info.vistas++;
            if(HT[j].info.vistas>max_visitas){
                max_visitas = HT[j].info.vistas;
            }
            if(HT[j].info.vistas<min_visitas){
                min_visitas = HT[j].info.vistas;
            }
            
            cout<<"Visitas: "<<HT[j].info.vistas<<endl;
            return HT[j].info.definicion;
        }
        accesos++;

    }
    return vacio;
}



// Constructor
CacheDiccionario::CacheDiccionario(){
};



/*****
* bool CacheDiccionario::query()
******
* La funcion realiza una consulta a hashSearch con el fin de verificar si el termino se encuentra en el diccionario.
******
* Input:
* string termino : La funcion recibe un string con el nombre del termino a buscar.
* string& significado : La funcion recibe un string por refencia el cual posteriormente tendra la definicion de la palabra si fue encontrada.
******
* Returns:
* La funcion retorna true si la palabra se encontro y false si no.
*****/
bool CacheDiccionario::query(string termino, string& significado){
    bool flag = NULL;
    Diccionario datos;
    datos.palabra = termino;
    significado = hashSearch(&HT[0], datos);
    cout<<"Definicion: "<<significado<<endl;
    if(significado != "vacio"){
        if(significado == ""){
            desconocidos_search++;
        }else{
            conocidos_search++;
        }
        flag = true;
    }else if(significado == "vacio"){
        cout<<"No se encontro"<<endl;
        flag = false;
        count1++;
    }
    total_search++;
    return flag;
}



/*****
* void CacheDiccionario::insert()
******
* La funcion se encarga de llamar a hashInsert para insertar en una determinada posicion la palabra y su definicion.
******
* Input:
* string termino : La funcion recibe un string con el nombre del termino a insertar.
* string& significado : La funcion recibe un string con la definicion de la palabra.
******
* Returns:
* Al ser una funcion tipo void, no retorna nada.
*****/
void CacheDiccionario::insert(string termino, string significado){
    int cla = h(termino), verificador;
    Diccionario valores_insert;
    valores_insert.palabra = termino;
    valores_insert.definicion = significado;
    verificador = hashInsert(&HT[0], cla, valores_insert);
    if(verificador != -1){
        cout<<"Insercion exitosa"<<endl;
        cout<<termino<<" = "<<significado<<endl;
        aumento++;
        cout<<"Clave insercion: "<<verificador<<endl;
    }else{
        cout<<"Insercion no exitosa: clave repetida"<<endl;
    }
    //Cuando la tabla se hash se llena. entra al if
    if(aumento == M){
        cout<<"Se llego al tope"<<endl;
        del++;
        int con2=0;
        int prom = (max_visitas + min_visitas)/2;
        while(con2 <= (round(M/2)) && con2 < M){
            if(HT[con2].info.vistas <= prom){
                HT[con2].info.definicion.erase();
                HT[con2].info.palabra.erase();
                HT[con2].info.vistas = 0;
                //Los valores posteriores se trasladan 1 casilla
                for(int n = 0;n<M; n++){
                    HT[con2].info.definicion = HT[con2+1].info.definicion;
                    HT[con2].info.palabra = HT[con2+1].info.palabra;
                    HT[con2].info.vistas = HT[con2+1].info.vistas;
                }
            }
            con2++; 
        }
        aumento--;
    }
    cout<<"--------------------------------"<<endl;

}



/*****
* void CacheDiccionario::querystats()
******
* La funcion retorna estadisticas que se dieron a medida de la insercion y busqueda en el diccionario.
******
* Input:
* int& total : La funcion recibe un entero por referencia el cual posteriormente mostrara la cantidad total de consultas realizadas.
* int& conocidos : La funcion recibe un entero por referencia el cual posteriormente mostrara la cantidad total de consultas realizadas a términos con significado no vacío.
* int& desconocidos : La funcion recibe un entero por referencia el cual posteriormente mostrara la cantidad total de consultas realizadas a términos con significado vacío.
******
* Returns:
* Al ser una funcion tipo void, no retorna nada.
*****/
void CacheDiccionario::querystats(int& total, int& conocidos, int& desconocidos){
    total = total_search;
    conocidos = conocidos_search;
    desconocidos = desconocidos_search;
}



/*****
* void CacheDiccionario::perfstats()
******
* La funcion calcula las estadisticas acerca del TDA.
******
* Input:
* int& accesses : La funcion recibe un entero por referencia el cual posteriormente mostrara la  la cantidad de accesos realizadas a todas las ranuras de la tabla de hashing base del
  TDA.
* int& hits : La funcion recibe un entero por referencia el cual posteriormente mostrara la cantidad de veces que se encontró un término consultado.
* int& misses : La funcion recibe un entero por referencia el cual posteriormente mostrara la cantidad de veces que no se encontró un término consultado.
* int& cleanups : La funcion recibe un entero por referencia el cual posteriormente mostrara la cantidad de veces que se realizó una limpieza.
******
* Returns:
* Al ser una funcion tipo void, no retorna nada.
*****/
void CacheDiccionario::perfstats(int& accesses, int& hits, int& misses, int& cleanups){
   accesses = accesos;
   misses = count1;
   hits = count2;
   cleanups = del;
}




//Para probar nuestro caso de prueba, dejamos en el README una version de prueba que usamos para ver el funcionamiento.
//Para que el resultado sea igual a la del README, favor de quitar los comentarios a los cout, gracias.

int main(){
    CacheDiccionario obj1;
    string defi_palabra;
    int var1 = 0, var2 = 0, var3 = 0;
    int v1 = 0, v2 = 0, v3 = 0, v4 = 0;
    obj1.insert("Palabra1", "Definicion1");
    obj1.insert("Palabra2", "Definicion2");
    obj1.insert("Palabra3", "Definicion3");
    obj1.insert("Palabra4", "Definicion4");
    obj1.insert("Palabra5", "Definicion5");
    obj1.insert("Palabra6", "Definicion6");
    obj1.insert("Palabra1", "Definicion1");

    obj1.query("Palabra1", defi_palabra);
    obj1.query("Palabra1", defi_palabra);
    obj1.query("Palabra1", defi_palabra);
    obj1.query("Palabra1", defi_palabra);
    obj1.query("Palabra1", defi_palabra);
    obj1.query("Palabra1", defi_palabra);

    string otro;
    cout<<"_____________________________________"<<endl;
    obj1.query("Palabra10", otro);
    cout<<"_____________________________________"<<endl;

    obj1.query("Palabra2", defi_palabra);
    obj1.query("Palabra3", defi_palabra);
    obj1.query("Palabra4", defi_palabra);
    obj1.query("Palabra5", defi_palabra);
    obj1.query("Palabra6", defi_palabra);

    obj1.querystats(var1, var2, var3);
    cout<<"Total: "<<var1<<endl;
    cout<<"Conocidos: "<<var2<<endl;
    cout<<"Desconocidos: "<<var3<<endl;

    obj1.perfstats(v1, v2, v3, v4);
}